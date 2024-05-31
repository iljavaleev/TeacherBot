#include "botstaff/keyboards/user_keyboards/userKeyboards.hpp"
#include "botstaff/utils.hpp"
#include "botstaff/database/CRUD.hpp"
#include <tgbot/tgbot.h>
#include <vector>
#include <utility>
#include <format>
#include <unordered_set>

using namespace std;
using namespace TgBot;

namespace UserKeyboards
{
    InlineKeyboardMarkup::Ptr create_user_start_kb(long chat_id, bool exists)
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

        if (exists)
        {
            InlineKeyboardButton::Ptr user_calendar_btn(new InlineKeyboardButton);
            user_calendar_btn->text = "Календарь";
            user_calendar_btn->callbackData = "calendar pupil";
            row.push_back(user_calendar_btn);
            keyboard->inlineKeyboard.push_back(row);
            return keyboard;
        }
        
        InlineKeyboardButton::Ptr register_btn(new InlineKeyboardButton);
        register_btn->text = "Регистрация";
        register_btn->callbackData = "register";
        row.push_back(register_btn);
        keyboard->inlineKeyboard.push_back(row);
        
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr choose_role_kb()
    {
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
        vector<InlineKeyboardButton::Ptr> row;

       
        InlineKeyboardButton::Ptr pupil_btn(new InlineKeyboardButton);
        pupil_btn->text = "Ученик";
        pupil_btn->callbackData = "register_pupil";
        row.push_back(pupil_btn);
  
        
        InlineKeyboardButton::Ptr teacher_btn(new InlineKeyboardButton);
        teacher_btn->text = "Учитель";
        teacher_btn->callbackData = "register_teacher";
        row.push_back(teacher_btn);
        
        keyboard->inlineKeyboard.push_back(row);
        return keyboard;
    }

    InlineKeyboardMarkup::Ptr create_list_teachers_kb()
    {
        
        InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
     
        std::string  query = "SELECT * FROM bot_user WHERE teacher is null AND \
        is_active=true ORDER BY last_name";

        std::vector<botUser> teacher_list = botUser::get_all(query);
        for (auto it{teacher_list.begin()}; it!=teacher_list.end(); ++it)
        {
            std::vector<InlineKeyboardButton::Ptr> row;
            InlineKeyboardButton::Ptr teacher_btn(new InlineKeyboardButton);
            teacher_btn->text = std::format("{} {}", it->first_name, it->last_name);
            teacher_btn->callbackData = std::format("register_pupil {}", it->chat_id);
            row.push_back(teacher_btn);
            keyboard->inlineKeyboard.push_back(row);
        }

        return keyboard;
    }
}
