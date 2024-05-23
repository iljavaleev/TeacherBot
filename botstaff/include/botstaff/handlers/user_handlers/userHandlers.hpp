#ifndef userHandlers_hpp
#define userHandlers_hpp

#include <tgbot/tgbot.h>
#include <functional>

using namespace TgBot;
using namespace std;


namespace UserHandlers
{
     extern std::function<Message::Ptr (CallbackQuery::Ptr)> user_start_handler(TgBot::Bot& bot);
}

namespace UserRegisterHandlers
{
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> pupil_rigister_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> teacher_rigister_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> agreement_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> user_update_handler(TgBot::Bot& bot); 
}

#endif