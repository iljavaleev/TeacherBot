#include "botstaff/keyboards/teacher_keyboards/TeacherKeyboards.hpp"

#include <tgbot/tgbot.h>
#include <vector>
#include <utility>
#include <format>
#include <unordered_set>
#include <iostream>
#include <pqxx/pqxx>

#include "botstaff/database/CRUD.hpp"
#include "botstaff/database/PSQL.hpp"
#include "botstaff/Utils.hpp"


using namespace std;
using namespace TgBot;

namespace teacherKeyboards
{
    InlineKeyboardMarkup::Ptr create_comments_kb(long chat_id)
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;
        std::string query = std::format("SELECT l.id, TO_CHAR(l.date, \
        'dd/mm/yyyy'), u.first_name, u.last_name \
        FROM user_lesson as l JOIN bot_user as u ON l.pupil=u.chat_id \
        WHERE l.teacher={} ORDER BY date DESC LIMIT 10", chat_id); 
        
        pqxx::result R = SQL::select_from_table(query); 

        for (auto it{R.begin()}; it!=R.end(); ++it)
        {
            long id{it->at(0).as<long>()};
            std::string date{it->at(1).as<std::string>()};
            std::string first_name{it->at(2).as<std::string>()};
            std::string last_name{it->at(3).as<std::string>()};
            
            std::vector<InlineKeyboardButton::Ptr> row;
            InlineKeyboardButton::Ptr comment_btn(new InlineKeyboardButton);
            comment_btn->text = std::format(
                "{} {} {}", 
                date, 
                first_name, 
                last_name
            );
            comment_btn->callbackData = std::format(
                "comment_for_teacher {}", 
                id
            );
            row.push_back(comment_btn);
            keyboard->inlineKeyboard.push_back(row);
        }

        return keyboard;
    }
    
    InlineKeyboardMarkup::Ptr create_teacher_start_kb(bool is_admin)
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        InlineKeyboardButton::Ptr admin_calendar_btn(new InlineKeyboardButton);
        admin_calendar_btn->text = "Календарь";
        admin_calendar_btn->callbackData = "calendar teacher";
        row.push_back(admin_calendar_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        InlineKeyboardButton::Ptr list_pupils_btn(new InlineKeyboardButton);
        list_pupils_btn->text = "Список учеников";
        list_pupils_btn->callbackData = "pupils";
        row.push_back(list_pupils_btn);

        if (is_admin)
        {
            InlineKeyboardButton::Ptr list_teacher_btn(
                new InlineKeyboardButton
            );
            list_teacher_btn->text = "Список учетилей";
            list_teacher_btn->callbackData = "teachers";
            row.push_back(list_teacher_btn);
        }
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        InlineKeyboardButton::Ptr list_comments_btn(new InlineKeyboardButton);
        list_comments_btn->text = "Комментарии";
        list_comments_btn->callbackData = "comments";
        row.push_back(list_comments_btn);

        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr create_pupils_kb(long chat_id)
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        InlineKeyboardButton::Ptr teacher_active_pupils_btn(
            new InlineKeyboardButton
        );
        teacher_active_pupils_btn->text = "Список учеников";
        teacher_active_pupils_btn->callbackData = "pupils_list_active";
        row.push_back(teacher_active_pupils_btn);

        InlineKeyboardButton::Ptr list_pupils_btn(new InlineKeyboardButton);
        list_pupils_btn->text = "Список желающих обучаться";
        list_pupils_btn->callbackData = "pupils_list";
        row.push_back(list_pupils_btn);

        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr create_teachers_kb()
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        InlineKeyboardButton::Ptr teacher_active_teachers_btn(
            new InlineKeyboardButton
        );
        teacher_active_teachers_btn->text = "Список педагогов";
        teacher_active_teachers_btn->callbackData = "teachers_list_active";
        row.push_back(teacher_active_teachers_btn);

        InlineKeyboardButton::Ptr list_teachers_btn(new InlineKeyboardButton);
        list_teachers_btn->text = "Список кандидатов";
        list_teachers_btn->callbackData = "teachers_list";
        row.push_back(list_teachers_btn);

        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr create_list_users_kb(long chat_id, bool is_active)
    {
        
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        std::string query;
        if (chat_id)
        {
            query = std::format(
                "SELECT * FROM bot_user WHERE teacher={} \
                AND is_active={} ORDER BY last_name", 
                chat_id, 
                is_active
            );
        }
        else
        {
            query = std::format(
                "SELECT * FROM bot_user WHERE teacher is null AND NOT \
                chat_id={} AND is_active={} ORDER BY last_name", 
                std::getenv("ADMIN_CHAT_ID"), 
                is_active
            );
        }
        
        std::vector<std::shared_ptr<BotUser>> user_list = BotUser::get_all(
            query
        );
        for (auto it{user_list.begin()}; it!=user_list.end(); ++it)
        {
            std::vector<InlineKeyboardButton::Ptr> row;
            InlineKeyboardButton::Ptr user_btn(new InlineKeyboardButton);
            user_btn->text = std::format(
                "{} {}", 
                (*it)->first_name, 
                (*it)->last_name
            );
            user_btn->callbackData = std::format(
                "user_info {}", (*it)->chat_id
            );
            row.push_back(user_btn);
            keyboard->inlineKeyboard.push_back(row);
        }

        return keyboard;
    }


    InlineKeyboardMarkup::Ptr create_user_info_kb(BotUser& u)
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        if (!u.is_active)
        {
            
            InlineKeyboardButton::Ptr activate_btn(new InlineKeyboardButton);
            activate_btn->text = "Активировать";
            activate_btn->callbackData = std::format(
                "activate_user {}", 
                u.chat_id
            );
            row.push_back(activate_btn);
        }
        else
        {
            InlineKeyboardButton::Ptr update_btn(new InlineKeyboardButton);
            update_btn->text = "Редактировать";
            update_btn->callbackData = std::format(
                "update_user {} {}", 
                u.role, 
                u.chat_id
            );
            row.push_back(update_btn);
        }
        
        InlineKeyboardButton::Ptr delete_btn(new InlineKeyboardButton);
        delete_btn->text = "Удалить";
        delete_btn->callbackData = std::format("delete_user {}", u.chat_id);
        row.push_back(delete_btn);

        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr update_user_info_kb(
        std::string role, 
        long chat_id
    )
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;
        
        InlineKeyboardButton::Ptr update_first_name_btn(
            new InlineKeyboardButton
        );
        update_first_name_btn->text = "Изменить имя";
        update_first_name_btn->callbackData = std::format(
            "update_user_field first_name {}", 
            chat_id
        );
        row.push_back(update_first_name_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();
        
        InlineKeyboardButton::Ptr update_last_name_btn(
            new InlineKeyboardButton
        );
        update_last_name_btn->text = "Изменить фамилию";
        update_last_name_btn->callbackData = std::format(
            "update_user_field last_name {}", 
            chat_id
        );
        row.push_back(update_last_name_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();
        
        if (role == "pupil")
        {
            InlineKeyboardButton::Ptr update_class_btn(
                new InlineKeyboardButton
            );
            update_class_btn->text = "Изменить класс";
            update_class_btn->callbackData = std::format(
                "update_user_field class {}", 
                chat_id
            );
            row.push_back(update_class_btn);
            keyboard->inlineKeyboard.push_back(row);
            row.clear();
        }
        
        InlineKeyboardButton::Ptr update_phone_btn(new InlineKeyboardButton);
        update_phone_btn->text = "Изменить телефон";
        update_phone_btn->callbackData = std::format(
            "update_user_field phone {}", 
            chat_id
        );
        row.push_back(update_phone_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        InlineKeyboardButton::Ptr update_email_btn(new InlineKeyboardButton);
        update_email_btn->text = "Изменить почту";
        update_email_btn->callbackData = std::format(
            "update_user_field email {}", 
            chat_id
        );
        row.push_back(update_email_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        InlineKeyboardButton::Ptr update_comments_btn(new InlineKeyboardButton);
        update_comments_btn->text = "Изменить комментарии";
        update_comments_btn->callbackData = std::format(
            "update_user_field comments {}", 
            chat_id
        );
        row.push_back(update_comments_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        InlineKeyboardButton::Ptr finish_update_btn(new InlineKeyboardButton);
        finish_update_btn->text = "Закончить редактирование";
        finish_update_btn->callbackData = std::format(
            "update_user_field finish {}", 
            chat_id
        );
        row.push_back(finish_update_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        return keyboard;
    }

    InlineKeyboardMarkup::Ptr create_list_pupils_kb(
        long chat_id, 
        bool is_active, 
        bool update
    )
    {
        
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        std::string query = std::format(
                "SELECT * FROM bot_user WHERE teacher={} AND is_active={} \
                ORDER BY last_name", 
                chat_id, 
                is_active
            );
        std::vector<std::shared_ptr<BotUser>> user_list = BotUser::get_all(
            query
        );
        std::string callback_data = "lesson_pupil {}";
        if (update)
            callback_data = "update_lesson_pupil {}";
        
        for (auto it{user_list.begin()}; it!=user_list.end(); ++it)
        {
            std::vector<InlineKeyboardButton::Ptr> row;
            InlineKeyboardButton::Ptr user_btn(new InlineKeyboardButton);
            user_btn->text = std::format(
                "{} {}", 
                (*it)->first_name, 
                (*it)->last_name
            );
            user_btn->callbackData = std::vformat(
                callback_data, 
                std::make_format_args((*it)->chat_id)
            );
            row.push_back(user_btn);
            keyboard->inlineKeyboard.push_back(row);
        }

        return keyboard;
    }



    InlineKeyboardMarkup::Ptr update_lesson_info_kb(int lesson_id)
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;
        
        InlineKeyboardButton::Ptr update_lesson_date_btn(
            new InlineKeyboardButton
        );
        update_lesson_date_btn->text = "Изменить дату";
        update_lesson_date_btn->callbackData = std::format(
            "update_lesson_field date {}", 
            lesson_id
        );
        row.push_back(update_lesson_date_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();
        
        InlineKeyboardButton::Ptr update_lesson_pupil_btn(
            new InlineKeyboardButton
        );
        update_lesson_pupil_btn->text = "Изменить ученика";
        update_lesson_pupil_btn->callbackData = std::format(
            "update_lesson_field pupil {}", 
            lesson_id
        );
        row.push_back(update_lesson_pupil_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();
        
      
        InlineKeyboardButton::Ptr update_lesson_objectives_btn(
            new InlineKeyboardButton
        );
        update_lesson_objectives_btn->text = "Изменить тему занятия";
        update_lesson_objectives_btn->callbackData = std::format(
            "update_lesson_field objectives {}", 
            lesson_id
        );
        row.push_back(update_lesson_objectives_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();
     
        
        InlineKeyboardButton::Ptr update_lesson_pupil_comments_btn(
            new InlineKeyboardButton
        );
        update_lesson_pupil_comments_btn->text = "Изменить "
        "комментарий для ученика";
        update_lesson_pupil_comments_btn->callbackData = std::format(
            "update_lesson_field comment_for_pupil {}", 
            lesson_id
        );
        row.push_back(update_lesson_pupil_comments_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        InlineKeyboardButton::Ptr update_lesson_teacher_comments_btn(
            new InlineKeyboardButton
        );
        update_lesson_teacher_comments_btn->text = "Изменить комментарий"
        " для учителя";
        update_lesson_teacher_comments_btn->callbackData = std::format(
            "update_lesson_field comment_for_teacher {}", 
            lesson_id
        );
        row.push_back(update_lesson_teacher_comments_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        InlineKeyboardButton::Ptr finish_update_btn(new InlineKeyboardButton);
        finish_update_btn->text = "Закончить редактирование";
        finish_update_btn->callbackData = std::format("update_lesson_field "
        "finish_lesson_update {}", 
        lesson_id
        );
        row.push_back(finish_update_btn);
        keyboard->inlineKeyboard.push_back(row);
        row.clear();

        return keyboard;
    }

}
