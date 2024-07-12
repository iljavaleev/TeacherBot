#ifndef CRUD_hpp
#define CRUD_hpp

#include <tgbot/tgbot.h>
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <chrono>
#include <memory>


struct BotUser{
    BotUser(){}
    BotUser(long chat_id):chat_id(chat_id){}
    BotUser(const BotUser& other)
    {
        chat_id = other.chat_id;
        teacher = other.teacher;
        tgusername = other.tgusername;
        first_name = other.first_name;
        last_name = other.last_name;
        phone = other.phone;
        email = other.email;
        cls = other.cls;
        comment = other.comment;
        role = other.role;
        is_active = other.is_active;

    }
    static std::shared_ptr<BotUser> get(long);
    static std::vector<std::shared_ptr<BotUser>> get_all(std::string&);
    static bool exists(long id);
    void update();
    void destroy();
    void create();   
    
    long chat_id{};
    long teacher{};
    std::string tgusername{};
    std::string first_name{};
    std::string last_name{};
    std::string phone{};
    std::string email{};
    std::string cls{};
    std::string comment{};
    std::string role{};
    bool is_active{false};

    bool empty() const
    {
        return !static_cast<bool>(chat_id);
    }
};


struct UserLesson{
    UserLesson()
    {
        const std::chrono::time_point now{std::chrono::system_clock::now()};
        date = std::chrono::year_month_day{
            std::chrono::floor<std::chrono::days>(now)
        };
    }
    UserLesson(const UserLesson& other)
    {
        id = other.id;
        date = other.date;
        time = other.time;
        teacher = other.teacher;
        pupil = other.pupil;
        objectives = other.objectives;
        comment_for_pupil = other.comment_for_pupil;
        comment_for_teacher = other.comment_for_teacher;
        is_paid = other.is_paid;
    }

    static std::shared_ptr<UserLesson> get(int);
    static std::vector<std::shared_ptr<UserLesson>> get_all(std::string&);
    static bool exists(long id);
    void update();
    void destroy();
    int create();   
    
    int id{};
    std::chrono::year_month_day date{};
    std::string time{};
    long teacher{};
    long pupil{};
    std::string objectives{};
    std::string comment_for_pupil{};
    std::string comment_for_teacher{};
    bool is_paid{};
};

std::shared_ptr<BotUser> construct_user(const pqxx::row& res);
std::shared_ptr<UserLesson> construct_user_lesson(const pqxx::row& res);

#endif