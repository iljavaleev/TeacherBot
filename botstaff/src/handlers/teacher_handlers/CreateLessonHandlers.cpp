#include "botstaff/handlers/user_handlers/UserRegistration.hpp"

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <chrono>
#include <exception>
#include <memory>

#include "botstaff/handlers/teacher_handlers/CreateLessonHandlers.hpp"
#include "botstaff/database/CRUD.hpp"
#include "botstaff/handlers/Handlers.hpp"
#include "botstaff/keyboards/teacher_keyboards/TeacherKeyboards.hpp"
#include "botstaff/keyboards/user_keyboards/UserKeyboards.hpp"
#include "botstaff/handlers/teacher_handlers/TeacherHandlers.hpp"
#include "botstaff/keyboards/Keyboards.hpp"
#include "botstaff/States.hpp"
#include "botstaff/Utils.hpp"

using namespace std::chrono;

namespace createLesson
{   
    Message::Ptr create_lesson_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if(StringTools::split(query->data, ' ').at(0) == "create_lesson")
        {   
            
            clear_lesson_state(query->message->chat->id);
            auto info = StringTools::split(query->data, ' ');
            year_month_day date{
                year(stoi(info.at(1))),
                month(stoi(info.at(2))), 
                day(stoi(info.at(3)))
            };
            std::shared_ptr<UserLesson> lesson(
                new UserLesson()
            );
            lesson->teacher = query->message->chat->id;
            lesson->date = date;
            
            std::shared_ptr<LessonState> state(
                new LessonState()
            );
            state->pupil = true;
            
            DayForLesson dfl{state, lesson}; 
            lessonState.insert({query->message->chat->id, dfl});

            return bot.getApi().sendMessage(
                query->message->chat->id, 
                "Выберите ученика",
                nullptr, 
                nullptr,
                teacherKeyboards::create_list_pupils_kb(
                    query->message->chat->id
                )
            );

        }
        return Message::Ptr(nullptr);
    }
    

    Message::Ptr delete_lesson_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if(StringTools::split(query->data, ' ').at(0) == "delete_lesson")
        {   
            
            int lesson_id = stoi(
                StringTools::split(query->data, ' ').at(1)
            );
            delete_lesson(lesson_id);
            
            return bot.getApi().sendMessage(
                query->message->chat->id, 
                "Вы удалили занятие"
            );

        }
        return Message::Ptr(nullptr);
    }

    Message::Ptr lesson_pupil_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if(StringTools::split(query->data, ' ').at(0) == "lesson_pupil")
        {   
            
            long id = stoi(StringTools::split(query->data, ' ').at(1));
            lessonState.at(query->message->chat->id).state->pupil = false;
            lessonState.at(query->message->chat->id).state->time = true;
            lessonState.at(query->message->chat->id).inst->pupil = id;
            
            return bot.getApi().sendMessage(
                query->message->chat->id, 
                "Введите время начала занятия в удобном для вас формате"
            );

        }
        return Message::Ptr(nullptr);
    }

    Message::Ptr update_lesson_pupil_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if(StringTools::split(query->data, ' ').at(0) == "update_lesson_pupil")
        {   
            long id = stoi(StringTools::split(query->data, ' ').at(1));
            lessonState.at(query->message->chat->id).inst->pupil = id;
            return send_lesson_update_kb(bot, query->message);

        }
        return Message::Ptr(nullptr);
    }


    Message::Ptr lesson_day_date_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if (StringTools::split(query->data, ' ').at(0) == 
        "update_lesson_day_date")
        {   
            
            std::vector<std::string> info = StringTools::split(
                query->data, ' '
            );
            std::chrono::year_month_day ymd(
                std::chrono::year(stoi(info.at(2))),
                std::chrono::month(stoi(info.at(3))),
                std::chrono::day(stoi(info.at(4)))
            );
            lessonState.at(query->message->chat->id).inst->date = ymd;
            
            return send_lesson_update_kb(bot, query->message);

        }
        return Message::Ptr(nullptr);
    }

    Message::Ptr lesson_update_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if (StringTools::split(query->data, ' ').at(0) == 
        "update_lesson_field") 
        {
            
            std::vector<std::string> info = StringTools::split(
                query->data, ' '
            );
            long teacher_chat_id{query->message->chat->id};
            
            if (info.at(1) == "finish_lesson_update")
            {
                lessonState.at(teacher_chat_id).inst->update();
                auto lesson = lessonState.at(teacher_chat_id).inst;
                std::shared_ptr<BotUser> teacher = get_user(
                    query->message->chat->id
                );
                std::string mess = std::format(
                    "<b>Некоторыя данные по вашему" 
                    " занятию были изменены</b>\n\n"
                    "<b>Преподователь {} {}</b>\n"
                    "<b>Время начачла занятия: {} в {}</b>\n"
                    "<b>Тема урока</b>: {}\n"
                    "<b>Информация для ученика</b>:\n{}", 
                    teacher->first_name, 
                    teacher->last_name, 
                    lesson->date, 
                    lesson->time, 
                    lesson->objectives, 
                    lesson->comment_for_pupil
                );

                send_lesson_info_to_pupil(bot, mess, lesson->pupil);
                clear_user_state(teacher_chat_id);
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Вы закончили редактирование урока"
                );  
            }
                
            if (!lessonState.contains(teacher_chat_id))
            {
                
                std::shared_ptr<UserLesson> lesson = UserLesson::get(
                    std::stol(info.at(1))
                );
                
                std::shared_ptr<LessonState> state(new LessonState());
                state->update = true;

                DayForLesson dfl{state, lesson}; 
                
                lessonState.insert({teacher_chat_id, dfl});
                return send_lesson_update_kb(bot, query->message);
            }
            
            if (info.at(1) == "date")
            {
                lessonState.at(teacher_chat_id).state->date = true;
                auto ymd = get_curent_ymd();
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Выберите новую дату",
                    nullptr,
                    nullptr,
                    Keyboards::create_calendar_kb(
                        ymd[0], 
                        ymd[1], 
                        1,
                        "teacher", 
                        query->message->chat->id, true
                        )
                );
            }
            else if (info.at(1) == "pupil")
            {
                lessonState.at(teacher_chat_id).state->pupil = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Выберите ученика",
                    nullptr,
                    nullptr,
                    teacherKeyboards::create_list_pupils_kb(
                        query->message->chat->id, 
                        true, 
                        true
                    )
                );
            }
            else if (info.at(1) == "time")
            {
                lessonState.at(teacher_chat_id).state->time = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите время"
                );  
            }
            else if (info.at(1) == "objectives")
            {
                lessonState.at(teacher_chat_id).state->objectives = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите тему"
                );  
            }
            else if (info.at(1) == "comment_for_pupil")
            {
                lessonState.at(teacher_chat_id).state->comment_for_pupil = 
                true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите комментарий для учащегося"
                );  
            }
            else
            {
                lessonState.at(teacher_chat_id).state->comment_for_teacher = 
                true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите комментарий для учителя"
                );  
            }
        } 
        else
            return Message::Ptr(nullptr);
    }

    Message::Ptr lesson_delete_request::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if (StringTools::split(query->data, ' ').at(0) == "change_lesson_date")
        {   
            long lesson_id = stol(
                StringTools::split(query->data, ' ').at(1)
            );
            long teacher_id;
            std::string mess = lesson_delete_request_message(
                lesson_id, 
                &teacher_id
            );
            try
            {
                bot.getApi().sendMessage(
                            teacher_id,
                            mess,
                            nullptr, 
                            nullptr, 
                            nullptr,
                            "HTML"
                        );
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }    

            return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Мы отправили ваш запрос преподователю"
                );

        }
        return Message::Ptr(nullptr);
    }
};


Message::Ptr check_lesson_state(
    const TgBot::Bot& bot, 
    const Message::Ptr message
    )
{   
    
    long chat_id = message->chat->id;
    if (lessonState.contains(chat_id))
    {
        bool update{lessonState.at(chat_id).state->update};
        if (lessonState.at(chat_id).state->time)
        {   
            return lesson_time_handler(bot, message, update);
        }
        else if (lessonState.at(chat_id).state->objectives)
        {   
            return lesson_objectives_handler(bot, message, update);
        }
        else if (lessonState.at(chat_id).state->comment_for_pupil)
        {
            return lesson_comment_for_pupil_handler(bot, message, update);
        }
        else if (lessonState.at(chat_id).state->comment_for_teacher)
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
    const TgBot::Bot& bot, 
    const Message::Ptr& message
    )
{
    long chat_id{message->chat->id};
    int lesson_id = lessonState.at(chat_id).inst->id;
    return bot.getApi().sendMessage(
            message->chat->id, 
            "Редактирование. Нажмите Завершить, чтобы сохранить изменения",
            nullptr,
            nullptr,
            teacherKeyboards::update_lesson_info_kb(lesson_id)
        ); 
}


Message::Ptr lesson_time_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    lessonState.at(message->chat->id).state->time = false;
    lessonState.at(message->chat->id).inst->time = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
        
    lessonState.at(message->chat->id).state->objectives = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите тему занятия");

}

Message::Ptr lesson_objectives_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{   
    lessonState.at(message->chat->id).state->objectives = false;
    lessonState.at(message->chat->id).inst->objectives = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
    
    lessonState.at(message->chat->id).state->comment_for_pupil = true;
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Введите комментарии для ученика (полезная информация)"
    ); 
}


Message::Ptr lesson_comment_for_pupil_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    lessonState.at(message->chat->id).state->comment_for_pupil = false;
    lessonState.at(message->chat->id).inst->comment_for_pupil = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
   
    lessonState.at(message->chat->id).state->comment_for_teacher = true;
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Введите информацию для себя (служебные пометки)"
    );        
}

Message::Ptr lesson_comment_for_teacher_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    lessonState.at(message->chat->id).state->comment_for_teacher = false;
    lessonState.at(message->chat->id).inst->comment_for_teacher = message->text;
    if (update)
        return send_lesson_update_kb(bot, message);
    
    int user_lesson_id = lessonState.at(message->chat->id).inst->create();
    std::shared_ptr<UserLesson> lesson = lessonState.at(message->chat->id).inst;
    clear_lesson_state(message->chat->id);
   
    std::shared_ptr<BotUser> teacher = get_user(message->chat->id);
    std::string mess = std::format(
            "<b>Преподователь {} {}</b>\n"
            "<b>Время начачла занятия: {} в {}</b>\n"
            "<b>Тема урока</b>: {}\n<b>Информация для ученика</b>:\n{}", 
            teacher->first_name, 
            teacher->last_name, 
            lesson->date, 
            lesson->time, 
            lesson->objectives, 
            lesson->comment_for_pupil
        );


    send_lesson_info_to_pupil(bot, mess, lesson->pupil);
    return bot.getApi().sendMessage(
                message->chat->id, 
                std::format(
                    "Вы успешно создали занятие.\n"
                    "Ученику отправлено сообщение\n\n{}", 
                    get_user_lesson_info(
                        message->chat->id, 
                        user_lesson_id, 
                        teacher->role
                    )
                ),
                nullptr,
                nullptr,
                Keyboards::day_info_kb(user_lesson_id, teacher->role),
                "HTML"
            );

}   


Message::Ptr send_lesson_info_to_pupil(
    const TgBot::Bot& bot,
    std::string& message,
    long pupil_id
    )
{
    try
    {
        return bot.getApi().sendMessage(
            pupil_id, 
            message, 
            nullptr, 
            nullptr, 
            nullptr,
            "HTML"
            );
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return Message::Ptr(nullptr);
    }    
}
