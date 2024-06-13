#ifndef teacherHandlers_hpp
#define teacherHandlers_hpp
#include <tgbot/tgbot.h>
#include <functional>

using namespace TgBot;
using namespace std;


namespace teacherHandlers
{
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> list_all_teachers_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> list_teachers_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> list_user_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> list_active_not_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> user_info_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> activate_user(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> delete_user(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> update_user(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> comment_text_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> list_comments_handler(TgBot::Bot& bot);

    
}

namespace createLesson
{
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> create_lesson_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> lesson_update_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> lesson_pupil_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> lesson_day_date_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> update_lesson_pupil_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> lesson_delete_request(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> delete_lesson_handler(TgBot::Bot& bot);
}


#endif