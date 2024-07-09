#include <tgbot/tgbot.h>
#include "botstaff/handlers/teacher_handlers/teacherHandlers.hpp"
#include <functional>
#include <format>
#include "botstaff/utils.hpp"
#include "botstaff/database/CRUD.hpp"
#include "botstaff/keyboards/teacher_keyboards/teacherKeyboards.hpp"

using namespace TgBot;
using namespace std;

namespace teacherHandlers
{   

    std::function<Message::Ptr (CallbackQuery::Ptr)> list_comments_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (query->data == "comments")
            {
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Ваши недавние комметарии", 
                        nullptr, 
                        nullptr,  
                        teacherKeyboards::create_comments_kb(query->message->chat->id)
                    );
            }
            return Message::Ptr(nullptr);
        };
        
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> comment_text_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::split(query->data, ' ').at(0) == "comment_for_teacher")
            {
                    int lesson_id(std::stoi(StringTools::split(query->data, ' ').at(1)));
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        get_comment_text(lesson_id),
                        nullptr, 
                        nullptr, 
                        nullptr,
                        "HTML"
                    );
            }
            return Message::Ptr(nullptr);
        };
        
    }


    std::function<Message::Ptr (CallbackQuery::Ptr)> list_all_teachers_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (query->data == "teachers")
            {
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Выберите категорию", 
                        nullptr, 
                        nullptr,  
                        teacherKeyboards::create_teachers_kb()
                    );
            }
            return Message::Ptr(nullptr);
        };
        
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> list_teachers_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::startsWith(query->data, "teachers_list"))
            {
                if (query->data == "teachers_list_active")
                {
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Список педагогов по фамилии", 
                        nullptr, 
                        nullptr, 
                        teacherKeyboards::create_list_users_kb(0)
                    );
                }
                else
                {
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Список кандидатов по фамилии", 
                        nullptr, 
                        nullptr, 
                        teacherKeyboards::create_list_users_kb(0, false)
                    );
                }
                    
            }
            return Message::Ptr(nullptr);
        };
        
    }


    std::function<Message::Ptr (CallbackQuery::Ptr)> list_active_not_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (query->data == "pupils")
            {
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Выберите категорию", 
                        nullptr, 
                        nullptr, 
                        teacherKeyboards::create_pupils_kb(query->message->chat->id)
                    );
            }
            return Message::Ptr(nullptr);
        };
        
    }
    
    std::function<Message::Ptr (CallbackQuery::Ptr)> list_user_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::startsWith(query->data, "pupils_list"))
            {
                long teacher_id(query->message->chat->id);
                if (StringTools::startsWith(query->data, "pupils_list_active"))
                {
                    auto kb = teacherKeyboards::create_list_users_kb(teacher_id);
                    std::string message = kb->inlineKeyboard.empty() ? "Здесь пока никого" : "Список учеников по фамилии";
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        message,
                        nullptr, 
                        nullptr,
                        kb 
                        );
                }
                else
                {   
                    auto kb = teacherKeyboards::create_list_users_kb(teacher_id, false);
                    std::string message = kb->inlineKeyboard.empty() ? "Здесь пока никого" : "Список желающих обучаться по фамилии";
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        message, 
                        nullptr, 
                        nullptr,
                        kb
                        );
                }
                    
            }
            return Message::Ptr(nullptr);
        };
        
    }
 

    std::function<Message::Ptr (CallbackQuery::Ptr)> user_info_handler(TgBot::Bot& bot)
    {
         return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::split(query->data, ' ').at(0) == "user_info")
            {   
                std::string pupil_id{StringTools::split(query->data, ' ').at(1)};
                std::shared_ptr<BotUser> u = get_user(std::stol(pupil_id));
                std::string info;
                if (u.role == "teacher")
                {
                    info = get_teacher_info(u);
                }
                else
                {
                    info = get_pupil_info(u);
                }
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    info,
                    nullptr, 
                    nullptr, 
                    teacherKeyboards::create_user_info_kb(u),
                    "HTML"
                );

            }
            return Message::Ptr(nullptr);
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> activate_user(TgBot::Bot& bot)
    {
         return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::split(query->data, ' ').at(0) == "activate_user")
            {   
                std::string pupil_id{StringTools::split(query->data, ' ').at(1)};
                activate_this_user(std::stol(pupil_id));
                try
                {
                    bot.getApi().sendMessage(
                    pupil_id, 
                    "Вы зарегестрированы");
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Вы добавили пользователя"
                );

            }
            return Message::Ptr(nullptr);
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> delete_user(TgBot::Bot& bot)
    {
         return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::split(query->data,' ').at(0) == "delete_user")
            {   
                std::string pupil_id{StringTools::split(query->data, ' ').at(1)};
                delete_this_user(std::stol(pupil_id));
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Вы удалили пользователя"
                );

            }
            return Message::Ptr(nullptr);
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> update_user(TgBot::Bot& bot)
    {
         return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::split(query->data, ' ').at(0) == "update_user")
            {   
                auto info = StringTools::split(query->data, ' ');
                long user_id{std::stol(info.at(2))};
                std::string role{info.at(1)};
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Что вы хотите изменить?",
                    nullptr, 
                    nullptr, 
                    teacherKeyboards::update_user_info_kb(role, user_id)
                );

            }
            return Message::Ptr(nullptr);
        };
    }

}


