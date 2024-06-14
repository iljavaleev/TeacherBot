#include "botstaff/utils.hpp"
#include <boost/locale/encoding_utf.hpp>
#include "botstaff/database/psql.hpp"
#include "botstaff/database/CRUD.hpp"
#include "botstaff/handlers/handlers.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <utility>
#include <format>
#include <unordered_set>
#include <pqxx/pqxx>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <sstream>
#include <chrono>

using namespace TgBot;

int dayNumber(int year, int month, int day) 
{ 
    static std::vector<int> t = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
    year -= month < 3; 
    int num = ( year + year/4 - year/100 + year/400 + t[month-1] + 1) % 7; 
    if (num == 0)
        return 6;
    else
        return num - 1;  
} 

int num_days(int month, int year)
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 11 || month == 12)
        return 31;
    if (month == 4 || month == 6 || month == 9 || month == 10)
        return 30;
    return (!(year % 4) && (year % 100)) || !(year % 400) ? 29 : 28;
}

std::vector<int> get_curent_ymd()
{
    const std::chrono::time_point now{std::chrono::system_clock::now()};
    const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};
    
    return {
        static_cast<int>(ymd.year()), 
        (int) static_cast<unsigned>(ymd.month()),
        (int) static_cast<unsigned>(ymd.day())
        };

}

void create_first_row(InlineKeyboardMarkup::Ptr& keyboard)
{
    std::vector<std::string> days = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    InlineKeyboardButton::Ptr btn(new InlineKeyboardButton);
    std::vector<InlineKeyboardButton::Ptr> week_days(7, btn);
    for (int i{}; i < 7; ++i)
    {
        InlineKeyboardButton::Ptr btn(new InlineKeyboardButton);
        btn->text = days.at(i);
        btn->callbackData = days.at(i);
        week_days.at(i) = btn;
    }
    keyboard->inlineKeyboard.push_back(week_days);  
}

void create_last_row(InlineKeyboardMarkup::Ptr& keyboard, int year, int month, const std::string& role, bool update)
{
    auto ymd = get_curent_ymd();
    std::vector<InlineKeyboardButton::Ptr> row;

    InlineKeyboardButton::Ptr prev_month_btn(new InlineKeyboardButton);
    prev_month_btn->text = "<<";
    prev_month_btn->callbackData = std::format("change_month << {} {} {} {}", year, month, update, role);
    row.push_back(prev_month_btn);

    InlineKeyboardButton::Ptr current_btn(new InlineKeyboardButton);
    current_btn->text = std::format("Сегодня {}/{}/{}", ymd[2], ymd[1], ymd[0]);
    current_btn->callbackData = " ";
    row.push_back(current_btn);
    
    InlineKeyboardButton::Ptr next_month_btn(new InlineKeyboardButton);
    next_month_btn->text = ">>";
    next_month_btn->callbackData = std::format("change_month >> {} {} {} {}", year, month, update, role);
    row.push_back(next_month_btn);

    keyboard->inlineKeyboard.push_back(row);
}

bool is_admin(long chat_id)
{   
    std::string s_chat_id(std::getenv("ADMIN_CHAT_ID"));
    return std::stol(s_chat_id) == chat_id;
}

bool is_teacher(const botUser& user)
{
    return is_admin(user.chat_id) || (!user.empty() && user.is_active && (user.role == "teacher"));
}

bool is_teacher(long chat_id)
{   
    if (is_admin(chat_id))
        return true;
    
    botUser user = botUser::get(chat_id);
    return  !user.empty() && user.is_active && (user.role == "teacher");
}

std::unordered_set<int> get_lesson_days(int year, int month, long chat_id, const std::string& role)
{
    std::unordered_set<int> dates;
    std::string query;
    
    query = std::format(
        "SELECT EXTRACT('day' from date) FROM user_lesson WHERE \
            EXTRACT('year' from date)={} AND \
            EXTRACT('month' from date)={} AND \
            {}={}", year, month, role, chat_id
        );
   
    pqxx::result res = SQL::select_from_table(query);
    for (auto it{res.begin()}; it != res.end(); ++it)
    {
        dates.insert(it->at(0).as<int>());
    }
        
    
    return dates;
}

std::wstring utf8_to_wstring(const std::string& str)
{
    return boost::locale::conv::utf_to_utf<wchar_t>(str.c_str(), str.c_str() + str.size());
}

std::string wstring_to_utf8(const std::wstring& str)
{
    return boost::locale::conv::utf_to_utf<char>(str.c_str(), str.c_str() + str.size());
}  

std::string string_to_upper(const std::string& s)
{
    std::locale ru{"ru_RU.UTF-8"};
    auto& facet = std::use_facet<std::ctype<wchar_t>>(ru);
    std::wstring input{utf8_to_wstring(s)};
    facet.toupper(input.data(), input.data() + input.size());
    
    return wstring_to_utf8(input);
}

botUser get_user(long chat_id)
{
    return botUser::get(chat_id);
}

std::string get_pupil_info(const botUser& u)
{
    return std::format(
        "<b>{} {}. Класс: {}</b>\n<b>Юзернэйм</b>: @{}\n"
        "<b>Указан телефон</b>: {}\n<b>Адрес электронной почты</b>: {}\n"
        "<b>Комментарий:</b> {}", 
        u.first_name, u.last_name, u.cls, u.tgusername, u.phone, u.email, u.comment
        );
}

std::string get_teacher_info(const botUser& u)
{
    return std::format(
        "<b>{} {}</b>\n<b>Юзернэйм</b>: {}\n"
        "<b>Указан телефон</b>: {}\n"
        "<b>Адрес электронной почты</b>: {}\n"
        "<b>Комментарий:</b> {}", 
        u.first_name, u.last_name,u.tgusername, u.phone, u.email, u.comment
        );
}


std::string get_comment_text(int id)
{
    std::string query = std::format(
        "SELECT u.first_name, u.last_name, TO_CHAR(l.date, 'dd/mm/yyyy'), l.comment_for_teacher\
        FROM user_lesson as l \
        JOIN bot_user as u ON l.pupil=u.chat_id \
        WHERE l.id={}", id); 
    
    pqxx::result R = SQL::select_from_table(query);
    auto it{R.begin()};
    std::string date{it->at(0).as<std::string>()};
    std::string first_name{it->at(1).as<std::string>()};
    std::string last_name{it->at(2).as<std::string>()};
    std::string comment_for_teacher{it->at(3).as<std::string>()};
    
    return std::format(
        "<b>Ученик: {} {}</b>\n<b>Дата: {}</b>\n\n<b>Ваш комментарий</b>: {}\n", 
        date, first_name, last_name, comment_for_teacher);
}

std::string get_pupil_info(const Message::Ptr& message)
{
    auto u = get_user(message->chat->id);
    return std::format(
        "<b>{} {} {}</b>\n\
        <b>Юзернэйм</b>: {}\n\
        <b>Указан телефон</b>: {}\n\
        <b>Адрес электронной почты</b>:{}\n\
        <b>Комментарий:</b>{}", u.first_name, u.last_name, u.cls, u.tgusername, u.phone, u.email, u.comment);
}

void activate_this_user(long chat_id)
{
    std::string query =  std::format("UPDATE bot_user SET is_active=true WHERE chat_id = {}", chat_id);
    SQL::update(query);
}

void delete_this_user(long chat_id)
{
    std::string query = std::format("DELETE FROM bot_user WHERE chat_id={}", chat_id);
    SQL::destroy(query);
}

void delete_lesson(int lesson_id)
{
    std::string query = std::format("DELETE FROM user_lesson WHERE id={}", lesson_id);
    SQL::destroy(query);
}

std::string get_user_lesson_info(long chat_id, int user_lesson_id, std::string role)
{   
    UserLesson user_lesson = UserLesson::get(user_lesson_id);
    if (!user_lesson.id)
        return "Произошла ошибка, повторите позднее";
    botUser user;
    if (role == "teacher")
    {
        user = botUser::get(user_lesson.pupil);
        return std::format(
            "<b>Ученик: {} {}</b>\n"
            "<b>Время начачла занятия: {}</b>\n"
            "<b>Тема урока</b>: {}\n"
            "<b>Информация для преподователя</b>: {}", 
            user.first_name, user.last_name, user_lesson.time, user_lesson.objectives, user_lesson.comment_for_teacher
            );
    }
    
    user =  botUser::get(user_lesson.teacher);
    return std::format(
        "<b>Преподователь {} {}</b>\n"
        "<b>Время начачла занятия: {}</b>\n"
        "<b>Тема урока</b>: {}\n"
        "<b>Информация для ученика</b>: {}", 
        user.first_name, user.last_name, user_lesson.time, user_lesson.objectives, user_lesson.comment_for_pupil
        );
}

std::vector<std::vector<std::string>> get_lessons_by_day(long chat_id, std::string role,  int year, int month, int day)
{
    std::string date = std::format("{}-{}-{}", year, month, day);
    std::string qrole{"teacher"};
    
    if (role == "teacher")
        qrole = "pupil";

    std::string query = std::format(
        "SELECT u.first_name, u.last_name, l.id, l.time \
        FROM bot_user as u \
        JOIN (SELECT {}, id, time FROM user_lesson WHERE {}={} AND date='{}') as l \
        ON u.chat_id=l.{}", qrole, role, chat_id, date, qrole); 
    
    pqxx::result R = SQL::select_from_table(query);
    std::vector<std::vector<std::string>> result;
    
    for (auto it{R.begin()}; it != R.end(); ++it)
    {
        std::vector<std::string> v = {
            it->at(0).as<std::string>(),
            it->at(1).as<std::string>(),
            it->at(2).as<std::string>(),
            it->at(3).as<std::string>()
        };
        result.push_back(v);
    }

    return result;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) 
    {
        result.push_back (item);
    }

    return result;
}

std::chrono::year_month_day split_date(const std::string &s, char delim) {
    std::vector<int> date;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim)) 
    {
        date.push_back(stoi(item));
    }  

    return std::chrono::year_month_day(
        std::chrono::year(date.at(0)),
        std::chrono::month(date.at(1)),
        std::chrono::day(date.at(2))
        );
}

std::string lesson_delete_request_message(long lesson_id, long* teacher_id)
{
    std::string query = std::format(
        "SELECT l.teacher, u.first_name, u.last_name, l.date, l.time \
        FROM bot_user as u \
        JOIN (SELECT pupil, teacher, date, time FROM user_lesson WHERE id={}) as l \
        ON u.chat_id=l.pupil", lesson_id); 
    
    pqxx::result R = SQL::select_from_table(query); 
    auto it = R.begin();
    *teacher_id = it->at(0).as<long>();
    return std::format("Ученик {} {} сделал запрос на отмену занятия {} в {}", 
        it->at(1).as<std::string>(),
        it->at(2).as<std::string>(),
        it->at(3).as<std::string>(),
        it->at(4).as<std::string>()
    );
}

std::vector<std::string> get_last_10_comments(long teacher_id)
{
    std::string query = std::format(
        "SELECT l.date, l.time, u.first_name, u.last_name, l.c \
        FROM bot_user as u \
        JOIN (SELECT pupil, date, time, comment_for_pupil as c FROM user_lesson WHERE teacher={} ORDER BY date LIMIT 10 DESC) as l \
        ON u.chat_id=l.pupil", teacher_id);
    
    pqxx::result R = SQL::select_from_table(query);
    std::vector<std::string> result;
    int count{};
    for (auto it{R.begin()}; it != R.end(); ++it)
    {
        
        result.push_back(
            std::format("{}. <b>Занятие {} в {}</b>\n\
                <b>Ученик {} {}</b>\n\
                <b>Комментарий {}\n\n",
                ++count,
                it->at(0).as<std::string>(),
                it->at(1).as<std::string>(),
                it->at(2).as<std::string>(),
                it->at(3).as<std::string>(),
                it->at(4).as<std::string>()
            )
        );
    }

    return result;
    
}