#include "botstaff/handlers/user_handlers/userRegistration.hpp"
#include "botstaff/handlers/teacher_handlers/createLessonHandlers.hpp"
#include "botstaff/database/CRUD.hpp"
#include "botstaff/handlers/handlers.hpp"
#include "botstaff/keyboards/teacher_keyboards/teacherKeyboards.hpp"
#include "botstaff/keyboards/user_keyboards/userKeyboards.hpp"
#include "botstaff/handlers/teacher_handlers/teacherHandlers.hpp"
#include "botstaff/keyboards/keyboards.hpp"
#include "botstaff/states.hpp"
#include <unordered_map>
#include "botstaff/utils.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include <exception>

using namespace std::chrono;

namespace createLesson
{
    std::function<Message::Ptr (CallbackQuery::Ptr)> create_lesson_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::startsWith(query->data, "create_lesson"))
            {   
                
                auto info = StringTools::split(query->data, ' ');
                year_month_day date{
                    year(stoi(info.at(1))), month(stoi(info.at(2))), day(stoi(info.at(3)))
                };
                UserLesson lesson;
                lesson.teacher = query->message->chat->id;
                lesson.date = date;
                LessonState state;
                state.pupil = true;
                
                DayForLesson dfl{state, lesson}; 
                lessonState.insert({query->message->chat->id, dfl});

                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Выберите ученика",
                    false, 
                    0,
                    teacherKeyboards::create_list_pupils_kb(query->message->chat->id)
                );

            }
            return Message::Ptr(nullptr);
        };
    }
    
    
    std::function<Message::Ptr (CallbackQuery::Ptr)> lesson_pupil_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::startsWith(query->data, "lesson_pupil"))
            {   
                
                long id = stoi(StringTools::split(query->data, ' ').at(1));
                lessonState.at(query->message->chat->id).state.pupil = false;
                lessonState.at(query->message->chat->id).state.time = true;
                lessonState.at(query->message->chat->id).inst.pupil = id;
                
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите время начала занятия в удобном для вас формате"
                );

            }
            return Message::Ptr(nullptr);
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> update_lesson_pupil_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::startsWith(query->data, "update_lesson_pupil"))
            {   
                
                long id = stoi(StringTools::split(query->data, ' ').at(1));
                lessonState.at(query->message->chat->id).inst.pupil = id;
                return send_lesson_update_kb(bot, query->message);

            }
            return Message::Ptr(nullptr);
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> lesson_day_date_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query)
        {   
            if(StringTools::startsWith(query->data, "update_lesson_day_date"))
            {   
                
                std::vector<std::string> info = StringTools::split(query->data, ' ');
                std::chrono::year_month_day ymd(
                    std::chrono::year(stoi(info.at(2))),
                    std::chrono::month(stoi(info.at(3))),
                    std::chrono::day(stoi(info.at(4)))
                );
                lessonState.at(query->message->chat->id).inst.date = ymd;
                
                return send_lesson_update_kb(bot, query->message);

            }
            return Message::Ptr(nullptr);
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> lesson_update_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::startsWith(query->data, "update_lesson_field")) 
            {
                
                std::vector<std::string> info = StringTools::split(query->data, ' ');
                long teacher_chat_id{query->message->chat->id};
                
                if (info.at(1) == "finish_lesson_update")
                {
                    lessonState.at(teacher_chat_id).inst.update();
                    clear_user_state(teacher_chat_id);
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Вы закончили редактирование урока"
                    );  
                }
                    
                if (!lessonState.contains(teacher_chat_id))
                {
                    
                    UserLesson lesson = UserLesson::get(std::stol(info.at(1)));;
                    LessonState state;
                    state.update = true;
                    DayForLesson dfl{state, lesson}; 
                    lessonState.insert({teacher_chat_id, dfl});
                    return send_lesson_update_kb(bot, query->message);
                }
                
                if (info.at(1) == "date")
                {
                    lessonState.at(teacher_chat_id).state.date = true;
                    auto ymd = get_curent_ymd();
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Выберите новую дату",
                        false,
                        0,
                        Keyboards::create_calendar_kb(ymd[0], ymd[1], 1, query->message->chat->id, true)
                    );
                }
                else if (info.at(1) == "pupil")
                {
                    lessonState.at(teacher_chat_id).state.pupil = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Выберите ученика",
                        false,
                        0,
                        teacherKeyboards::create_list_pupils_kb(query->message->chat->id, true, true)
                    );
                }
                else if (info.at(1) == "time")
                {
                    lessonState.at(teacher_chat_id).state.time = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите время"
                    );  
                }
                else if (info.at(1) == "objectives")
                {
                    lessonState.at(teacher_chat_id).state.objectives = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите тему"
                    );  
                }
                else if (info.at(1) == "comment_for_pupil")
                {
                    lessonState.at(teacher_chat_id).state.comment_for_pupil = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите комментарий для учащегося"
                    );  
                }
                else
                {
                    lessonState.at(teacher_chat_id).state.comment_for_teacher = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите комментарий для учителя"
                    );  
                }
            } 
            else
                return Message::Ptr(nullptr);
        };
    }

};


Message::Ptr check_lesson_state(
    TgBot::Bot& bot, 
    const Message::Ptr message
    )
{   
    
    long chat_id = message->chat->id;
    if (lessonState.contains(chat_id))
    {
        bool update{lessonState.at(chat_id).state.update};
        if (lessonState.at(chat_id).state.time)
        {   
            return lesson_time_handler(bot, message, update);
        }
        else if (lessonState.at(chat_id).state.objectives)
        {   
            return lesson_objectives_handler(bot, message, update);
        }
        else if (lessonState.at(chat_id).state.comment_for_pupil)
        {
            return lesson_comment_for_pupil_handler(bot, message, update);
        }
        else if (lessonState.at(chat_id).state.comment_for_teacher)
        {
            return lesson_comment_for_teacher_handler(bot, message, update);
        }
    }
    return Message::Ptr(nullptr);
}

void clear_lesson_state(long user_id)
{
    if (lessonState.contains(user_id))
    {
        lessonState.erase(user_id);
    }
}


Message::Ptr send_lesson_update_kb(
    TgBot::Bot& bot, 
    const Message::Ptr& message
    )
{
    long chat_id{message->chat->id};
    int lesson_id = lessonState.at(chat_id).inst.id;
    return bot.getApi().sendMessage(
            message->chat->id, 
            "Редактирование. Нажмите Завершить, чтобы сохранить изменения",
            false,
            0,
            teacherKeyboards::update_lesson_info_kb(lesson_id)
        ); 
}


Message::Ptr lesson_time_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    lessonState.at(message->chat->id).state.time = false;
    lessonState.at(message->chat->id).inst.time = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
        
    lessonState.at(message->chat->id).state.objectives = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите тему занятия");

}

Message::Ptr lesson_objectives_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{   
    lessonState.at(message->chat->id).state.objectives = false;
    lessonState.at(message->chat->id).inst.objectives = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
    
    lessonState.at(message->chat->id).state.comment_for_pupil = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите комментарии для ученика (полезная информация)"); 
}


Message::Ptr lesson_comment_for_pupil_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    lessonState.at(message->chat->id).state.comment_for_pupil = false;
    lessonState.at(message->chat->id).inst.comment_for_pupil = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
   
    lessonState.at(message->chat->id).state.comment_for_teacher = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите информацию для себя (служебные пометки)");
  
        
}


Message::Ptr lesson_comment_for_teacher_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    lessonState.at(message->chat->id).state.comment_for_teacher = false;
    lessonState.at(message->chat->id).inst.comment_for_teacher = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
    
    lessonState.at(message->chat->id).inst.create();
    UserLesson lesson = lessonState.at(message->chat->id).inst;
    clear_lesson_state(message->chat->id);
   

    send_lesson_info_to_pupil(bot, message, lesson);
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Вы успешно создали. Вашему ученику отправлено сообщение"
        );
}


Message::Ptr send_lesson_info_to_pupil(
    TgBot::Bot& bot,
    const Message::Ptr message,
    UserLesson& lesson
    )
{
    botUser u = get_user(message->chat->id);
    std::string mess = std::format(
            "<b>Преподователь {} {}</b>\n\
            <b>Время начачла занятия: {} в {}</b>\n\
            <b>Тема урока</b>: {}\n\
            <b>Информация для ученика</b>:\n{}", 
            u.first_name, u.last_name, lesson.date, lesson.time, lesson.objectives, lesson.comment_for_pupil
            );

    try
    {
        return bot.getApi().sendMessage(lesson.pupil, mess);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return Message::Ptr(nullptr);
    }    
}
