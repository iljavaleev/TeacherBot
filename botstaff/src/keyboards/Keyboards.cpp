#include "botstaff/keyboards/Keyboards.hpp"

#include <tgbot/tgbot.h>
#include <vector>
#include <utility>
#include <format>
#include <unordered_set>

#include "botstaff/Utils.hpp"
#include "botstaff/database/CRUD.hpp"

using namespace std;
using namespace TgBot;


namespace Keyboards
{
    InlineKeyboardMarkup::Ptr create_calendar_kb(
        int year, 
        int month, 
        int day, 
        const std::string& role, 
        long chat_id, 
        bool update
        )
    {
        
        std::unordered_set<int> lesson_days = get_lesson_days(
            year, 
            month, 
            chat_id, 
            role
        );
        
        int first_day_number = dayNumber(year, month, day);
        int month_day_number = num_days(month, year);
        int count = 1;
        
        
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        InlineKeyboardButton::Ptr empty_btn(new InlineKeyboardButton);
        empty_btn->text = " ";
        empty_btn->callbackData = " ";
        
        create_first_row(keyboard);
        
        bool first_row{true};
        bool outer{true};

        std::string callback_data = "calendar_day {} {} {} {}";
        if (update)
        {
            callback_data = "update_lesson_day_date {} {} {} {}";
        }
        while(outer)
        {   
            int start{};
            vector<InlineKeyboardButton::Ptr> row(7, empty_btn);
            if (first_row)
            {
                start = first_day_number;
                first_row = false;
            }
            for (int j{start}; j < 7; ++j)
            {
                InlineKeyboardButton::Ptr cal_btn(new InlineKeyboardButton);
                
                if (lesson_days.contains(count))
                    cal_btn->text = std::format("{}.", count);
                else
                    cal_btn->text = std::format("{}", count);
                
                cal_btn->callbackData = std::vformat(
                    callback_data, 
                    std::make_format_args(role, year, month, count)
                );
                
                row.at(j) = cal_btn;
                count++;
                
                if (count > month_day_number)
                {   
                    outer = false;
                    break;
                }
            }
            keyboard->inlineKeyboard.push_back(row);
        }
        
        create_last_row(keyboard, year, month, role, update);

        return keyboard;
    }

    InlineKeyboardMarkup::Ptr create_day_kb()
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        InlineKeyboardButton::Ptr admin_calendar_btn(new InlineKeyboardButton);
        admin_calendar_btn->text = "Календарь";
        admin_calendar_btn->callbackData = "admin calendar";
        row.push_back(admin_calendar_btn);

        InlineKeyboardButton::Ptr list_pupils_btn(new InlineKeyboardButton);
        list_pupils_btn->text = "Список учеников";
        list_pupils_btn->callbackData = "admin pupils";
        row.push_back(list_pupils_btn);

        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr agreement_kb()
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        InlineKeyboardButton::Ptr yes_btn(new InlineKeyboardButton);
        yes_btn->text = "Да";
        yes_btn->callbackData = "agreement yes";
        row.push_back(yes_btn);

        InlineKeyboardButton::Ptr no_btn(new InlineKeyboardButton);
        no_btn->text = "Нет";
        no_btn->callbackData = "agreement no";
        row.push_back(no_btn);

        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr lessons_list_kb(
        long chat_id, 
        std::string role, 
        int year, 
        int month, 
        int day
    )
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        std::vector<std::vector<std::string>> info = get_lessons_by_day(
            chat_id, 
            role, 
            year, 
            month, 
            day
        );
        for (auto it{info.begin()}; it != info.end(); ++it)
        {
            vector<InlineKeyboardButton::Ptr> row;
            InlineKeyboardButton::Ptr user_btn(new InlineKeyboardButton);
            user_btn->text = std::format(
                "{} {} {}", 
                it->at(0), 
                it->at(1), 
                it->at(3)
            );
            user_btn->callbackData = std::format(
                "user_lesson {} {}", 
                it->at(2), 
                role
            );
            row.push_back(user_btn);
            keyboard->inlineKeyboard.push_back(row);
        }
        if (role == "teacher")
        {
            vector<InlineKeyboardButton::Ptr> row;
            InlineKeyboardButton::Ptr create_lesson_btn(
                new InlineKeyboardButton
            );
            create_lesson_btn->text = "Создать новое занятие";
            create_lesson_btn->callbackData = std::format(
                "create_lesson {} {} {}", 
                year, 
                month, 
                day
            );
            row.push_back(create_lesson_btn);
            keyboard->inlineKeyboard.push_back(row);
        }

        return keyboard;
    }

    InlineKeyboardMarkup::Ptr day_info_kb(int lesson_id, std::string role)
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        if (role == "pupil")
        {
            InlineKeyboardButton::Ptr change_date_btn(new InlineKeyboardButton);
            change_date_btn->text = "Запрос на перенос занятия";
            change_date_btn->callbackData = std::format(
                "change_lesson_date {}", 
                lesson_id
            );
            row.push_back(change_date_btn);
        }
        else
        {
            InlineKeyboardButton::Ptr update_lesson_btn(
                new InlineKeyboardButton
            );
            update_lesson_btn->text = "Редактировать занятие";
            update_lesson_btn->callbackData = std::format(
                "update_lesson_field {}", 
                lesson_id
            );
            row.push_back(update_lesson_btn);

            InlineKeyboardButton::Ptr delete_lesson_btn(
                new InlineKeyboardButton
            );
            delete_lesson_btn->text = "Отменить занятие";
            delete_lesson_btn->callbackData = std::format(
                "delete_lesson {}", 
                lesson_id
            );
            row.push_back(delete_lesson_btn);
        }
        
        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }
}
