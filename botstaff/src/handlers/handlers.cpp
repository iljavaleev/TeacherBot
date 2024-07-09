#include "botstaff/handlers/handlers.hpp"

#include <unordered_map>
#include <string>
#include <exception>
#include <iostream>
#include <memory>

#include "botstaff/states.hpp"
#include "botstaff/utils.hpp"
#include "botstaff/vocabular.hpp"
#include "botstaff/keyboards/teacher_keyboards/teacherKeyboards.hpp"
#include "botstaff/keyboards/user_keyboards/userKeyboards.hpp"
#include "botstaff/keyboards/keyboards.hpp"
#include "botstaff/handlers/user_handlers/userRegistration.hpp"
#include "botstaff/handlers/teacher_handlers/createLessonHandlers.hpp"
#include "botstaff/database/CRUD.hpp"

namespace CommandHandlers
{
    std::function<Message::Ptr (Message::Ptr)> startCommand(TgBot::Bot& bot)
    {
        return [&bot](Message::Ptr message) 
        {   
            long chat_id(message->chat->id);
            clear_user_state(chat_id);
            clear_lesson_state(chat_id);
            std::shared_ptr<BotUser> user = botUser::get(chat_id);
            if (is_admin(chat_id))
                return bot.getApi().sendMessage(
                    chat_id, 
                    "Вход для админа", 
                    nullptr, 
                    nullptr, 
                    teacherKeyboards::create_teacher_start_kb(true)
                ); 
            else if(is_teacher(*user))
                return bot.getApi().sendMessage(
                    chat_id, 
                    "Вход для учителя", 
                    nullptr, 
                    nullptr, 
                    teacherKeyboards::create_teacher_start_kb(false)
                );
            else
                return bot.getApi().sendMessage(
                    chat_id, 
                    "Вход для пользователя", 
                    nullptr, 
                    nullptr, 
                    UserKeyboards::create_user_start_kb(
                        chat_id, 
                        !user->empty()
                    )
                );  
                          
        };
    }


    std::function<Message::Ptr (Message::Ptr)> cancelCommand(TgBot::Bot& bot)
    {
        return [&bot](Message::Ptr message) 
        {   
            long chat_id(message->chat->id);
            clear_user_state(chat_id);
            clear_lesson_state(chat_id);
            return bot.getApi().sendMessage(
                message->chat->id, 
                "Cancel command"
            );
        };
    }
}

namespace Handlers
{
    std::function<Message::Ptr (Message::Ptr)> any_message_handler(
        TgBot::Bot& bot
    )
    {
        return [&bot](Message::Ptr message)
        {
            if (
                StringTools::startsWith(message->text, "/start") 
                || StringTools::startsWith(message->text, "/cancel")
                ) 
            {
                return Message::Ptr(nullptr);
            }
            long user_chat_id{message->chat->id};
            try
            {
                auto res = check_user_state(bot, message);
                if (res)
                    return res;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            try
            {
                auto res = check_lesson_state(bot, message);
                if (res)
                    return res;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            return bot.getApi().sendMessage(
                user_chat_id, 
                "Your message is: " + message->text
            );
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> calendar_handler(
        TgBot::Bot& bot
    ) 
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::split(query->data, ' ').at(0) == "calendar") 
            {
                auto ymd = get_curent_ymd();
                std::string role = StringTools::split(query->data, ' ').at(1);
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    std::format(
                        "<b><i>Расписание на {}</i></b>", 
                        MONTHS_RU.at(ymd[1]-1)
                    ), 
                    nullptr, 
                    nullptr, 
                    Keyboards::create_calendar_kb(
                        ymd[0], 
                        ymd[1], 
                        1, 
                        role, 
                        query->message->chat->id
                    ),
                    "HTML"
                    );  
            }
             else
                return Message::Ptr(nullptr); 
        };
    }
    
    std::function<Message::Ptr (CallbackQuery::Ptr)> next_month_handler(
        TgBot::Bot& bot
    )
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::split(query->data, ' ').at(0) == "change_month")
            {
                auto info = StringTools::split(query->data, ' ');
                int year = stoi(info.at(2));
                int month = stoi(info.at(3));
                bool update = true ? info.at(4) == "true" : false;
                std::string role = info.at(5);
                if (info.at(1) == "<<")
                {   
                    month--;
                }
                else
                {
                    month++;
                }
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    std::format(
                        "<b><i>Расписание на {}</i></b>", 
                        MONTHS_RU.at(month-1)
                    ),
                    nullptr, 
                    nullptr, 
                    Keyboards::create_calendar_kb(
                        year, 
                        month, 
                        1, 
                        role, 
                        query->message->chat->id, 
                        update
                    ),
                    "HTML"
                    );  
            }
             else
                return Message::Ptr(nullptr); 
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> calendar_day_handler(TgBot::Bot& bot)
    {
         return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::split(query->data, ' ').at(0) == "calendar_day") 
            {
                auto info = StringTools::split(query->data, ' ');
                
                std::string role{info.at(1)};
                int year = stoi(info.at(2));
                int month = stoi(info.at(3));
                int day = stoi(info.at(4));

                
                auto kb = Keyboards::lessons_list_kb(
                    query->message->chat->id, 
                    role, 
                    year, 
                    month, 
                    day
                );
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    kb->inlineKeyboard.empty() ? "Сегодня нет занятий" : 
                    "Занятия сегодня",
                    nullptr, 
                    nullptr, 
                    kb
                );

            }
             else
                return Message::Ptr(nullptr); 
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> day_info_handler(
        TgBot::Bot& bot
    )
    {
         return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::split(query->data, ' ').at(0) == 
            "user_lesson")
            {
                auto info = StringTools::split(query->data, ' ');
                int user_lesson_id = stoi(info.at(1));
                std::string role = info.at(2);
                
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    get_user_lesson_info(
                        query->message->chat->id, 
                        user_lesson_id, 
                        role
                    ),
                    nullptr, 
                    nullptr, 
                    Keyboards::day_info_kb(user_lesson_id, role),
                    "HTML"
                    );

            }
             else
                return Message::Ptr(nullptr); 
        };
    }
}

void startWebhook(TgBot::Bot& bot, std::string& webhookUrl)
{
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());

        TgWebhookTcpServer webhookServer(8080, bot);

        printf("Server starting\n");
        bot.getApi().setWebhook(webhookUrl);
        webhookServer.start();
    } catch (exception& e) {
        printf("error: %s\n", e.what());
    }
}
