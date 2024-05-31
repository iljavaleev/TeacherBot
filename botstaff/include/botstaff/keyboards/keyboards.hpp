#include <tgbot/tgbot.h>
#include <string>

using namespace TgBot;


namespace Keyboards
{
    InlineKeyboardMarkup::Ptr create_calendar_kb(
        int year, 
        int month, 
        int day, 
        const std::string& role, 
        long chat_id=0, 
        bool update=false
        );
    InlineKeyboardMarkup::Ptr create_day_kb();
    InlineKeyboardMarkup::Ptr agreement_kb();
    InlineKeyboardMarkup::Ptr lessons_list_kb(long, std::string, int, int, int);
    InlineKeyboardMarkup::Ptr day_info_kb(int, std::string);
} 
