#ifndef userKeyboards_hpp
#define userKeyboards_hpp

#include <tgbot/tgbot.h>
#include <string>

using namespace TgBot;

namespace UserKeyboards
{
    InlineKeyboardMarkup::Ptr create_user_start_kb(long chat_id, bool exists);
    InlineKeyboardMarkup::Ptr choose_role_kb();
    InlineKeyboardMarkup::Ptr create_list_teachers_kb();
}


#endif