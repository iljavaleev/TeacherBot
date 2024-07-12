#ifndef TeacherKeyboards_hpp
#define TeacherKeyboards_hpp

#include <tgbot/tgbot.h>
#include <string>

#include "botstaff/database/CRUD.hpp"

using namespace TgBot;

namespace teacherKeyboards
{
    InlineKeyboardMarkup::Ptr create_teacher_start_kb(bool);
    InlineKeyboardMarkup::Ptr create_teachers_kb();
    InlineKeyboardMarkup::Ptr create_pupils_kb(long);
    InlineKeyboardMarkup::Ptr create_comments_kb(long);
    InlineKeyboardMarkup::Ptr create_list_users_kb(
        long chat_id=0, 
        bool is_active=true
    );
    InlineKeyboardMarkup::Ptr create_user_info_kb(BotUser&);
    InlineKeyboardMarkup::Ptr update_user_info_kb(std::string, long);
    InlineKeyboardMarkup::Ptr create_list_pupils_kb(
        long chat_id, 
        bool is_active=true, 
        bool update=false
    );
    InlineKeyboardMarkup::Ptr update_lesson_info_kb(int lesson_id);
}


#endif