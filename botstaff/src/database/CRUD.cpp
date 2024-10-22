#include "botstaff/database/CRUD.hpp"

#include <tgbot/tgbot.h>
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <chrono>
#include <format>
#include <chrono>
#include <memory>

#include "botstaff/database/PSQL.hpp"
#include "botstaff/Utils.hpp"


std::shared_ptr<BotUser> construct_user(const pqxx::row& res)
{
    std::shared_ptr<BotUser> user(new BotUser());
    if (res.empty())
        return user;
    if (res.at(9).as<std::string>() == "pupil")
    {
        user->teacher = res.at(1).as<long>();
        user->cls = res.at(7).as<std::string>();
    }
    user->chat_id = res.at(0).as<long>();
    user->tgusername = res.at(2).as<std::string>();
    user->first_name = res.at(3).as<std::string>();
    user->last_name = res.at(4).as<std::string>();
    user->phone = res.at(5).as<std::string>();
    user->email = res.at(6).as<std::string>();
    user->comment = res.at(8).as<std::string>();
    user->role = res.at(9).as<std::string>();
    user->is_active = res.at(10).as<bool>();
    return user;
}


std::shared_ptr<UserLesson> construct_user_lesson(const pqxx::row& res)
{
    std::shared_ptr<UserLesson> user_lesson(new UserLesson());
    if (res.empty())
        return user_lesson;
    user_lesson->id = res.at(0).as<int>();
    user_lesson->date = split_date(res.at(1).as<std::string>(), '-');
    user_lesson->teacher = res.at(2).as<long>();
    user_lesson->pupil = res.at(3).as<long>();
    user_lesson->time = res.at(4).as<std::string>();
    user_lesson->objectives = res.at(5).as<std::string>();
    user_lesson->comment_for_pupil = res.at(6).as<std::string>();
    user_lesson->comment_for_teacher = res.at(7).as<std::string>();
    user_lesson->is_paid = res.at(8).as<bool>();
    return user_lesson;
}

std::shared_ptr<BotUser> BotUser::get(long id)
{   
    std::string query = std::format(
        "SELECT * FROM bot_user WHERE chat_id={}", 
        id
    );
    pqxx::result R = SQL::select_from_table(query);
    std::shared_ptr<BotUser> user(new BotUser());
    if (!R.empty())
    {
        auto row = *R.begin();
        user = construct_user(row);
    }
    printf("HERE2\n");
    return user;
    
}

bool BotUser::exists(long id)
{
    std::string query = std::format(
        "SELECT EXISTS(SELECT 1 FROM bot_user WHERE chat_id={})", 
        id
    );
    pqxx::result R = SQL::select_from_table(query);
    
    return R.at(0).at(0).as<bool>();
}

std::vector<std::shared_ptr<BotUser>> BotUser::get_all(std::string& query)
{
    pqxx::result R = SQL::select_from_table(query);
    std::vector<std::shared_ptr<BotUser>> users;
    for (auto it{R.begin()}; it != R.end(); ++it)
    {
        users.push_back(construct_user(*it));
    }
    return users;
}

void BotUser::update()
{
        
    std::string query = std::format("UPDATE bot_user SET teacher = {}, \
    tgusername = '{}', first_name = '{}', last_name = '{}', phone = '{}', \
    email = '{}', class = '{}', comment = '{}', user_role = '{}',\
    is_active = {} WHERE chat_id = {}",
    teacher ? std::to_string(teacher) : "null", 
    tgusername, 
    first_name, 
    last_name, 
    phone, 
    email, 
    cls, 
    comment, 
    role, 
    is_active, 
    chat_id);
    SQL::update(query);
}


void BotUser::destroy()
{
    std::string query = std::format(
        "DELETE FROM bot_user WHERE chat_id={}", 
        chat_id
    );
    SQL::destroy(query);
}

void BotUser::create()
{
    std::string query;
    if (role == "teacher")
        query = std::format(
            "INSERT INTO bot_user VALUES \
            ({}, null, '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', {})", 
            chat_id, 
            tgusername, 
            first_name, 
            last_name, 
            phone, 
            email, 
            cls, 
            comment, 
            role, 
            is_active);
    else
        query = std::format(
            "INSERT INTO bot_user VALUES \
            ({}, {}, '{}', '{}', '{}', '{}', '{}', '{}', '{}', '{}', {})", 
            chat_id, 
            teacher, 
            tgusername, 
            first_name, 
            last_name, 
            phone, 
            email, 
            cls, 
            comment, 
            role, 
            is_active);
    SQL::insert_into_table(query);
}

std::shared_ptr<UserLesson> UserLesson::get(int id)
{   
    std::string query = std::format(
        "SELECT * FROM user_lesson WHERE id={}", 
        id
    );
    pqxx::result R = SQL::select_from_table(query);
    auto row = *R.begin();
    return construct_user_lesson(row);
}

 bool UserLesson::exists(long id)
 {
    std::string query = std::format(
        "SELECT EXISTS(SELECT 1 FROM user_lesson WHERE chat_id={})", 
        id
    );
    pqxx::result R = SQL::select_from_table(query);
    return R.at(0).at(0).as<bool>();
 }

std::vector<std::shared_ptr<UserLesson>> UserLesson::get_all(std::string& query)
{
    pqxx::result R = SQL::select_from_table(query);
    std::vector<std::shared_ptr<UserLesson>> user_lessons;
    for (auto it{R.begin()}; it != R.end(); ++it)
    {
        user_lessons.push_back(construct_user_lesson(*it));
    }
    return user_lessons;
}

void UserLesson::update()
{
    std::string query = std::format("UPDATE user_lesson SET id=DEFAULT, \
    date='{}', time='{}', teacher={}, pupil = {}, objectives = '{}', \
    comment_for_pupil = '{}', comment_for_teacher = '{}', is_paid = {} \
    WHERE id = {}", 
    date, 
    time, 
    teacher, 
    pupil, 
    objectives, 
    comment_for_pupil, 
    comment_for_teacher, 
    is_paid, 
    id);
    SQL::update(query);
}


void UserLesson::destroy()
{
    std::string query = std::format("DELETE FROM user_lesson WHERE id={}", id);
    SQL::destroy(query);
}

int UserLesson::create()
{
    std::string query = std::format("INSERT INTO user_lesson VALUES \
    (DEFAULT, '{}', {}, {}, '{}', '{}', '{}', '{}', {}) RETURNING id",
    date, 
    teacher, 
    pupil, 
    time, 
    objectives, 
    comment_for_pupil, 
    comment_for_teacher, 
    is_paid);
    return SQL::insert_into_table(query).begin()->at(0).as<int>();
}
