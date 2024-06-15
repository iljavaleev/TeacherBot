#include <tgbot/tgbot.h>
#include <functional>
#include "botstaff/states.hpp"
#include "botstaff/utils.hpp"
#include "botstaff/handlers/handlers.hpp"
#include "botstaff/handlers/user_handlers/userHandlers.hpp"
#include "botstaff/handlers/user_handlers/userRegistration.hpp"
#include "botstaff/keyboards/user_keyboards/userKeyboards.hpp"

using namespace TgBot;
using namespace std;


namespace UserHandlers
{
    std::function<Message::Ptr (CallbackQuery::Ptr)> user_start_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (query->data == "register") 
            {
                return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Выберите роль",
                        nullptr, 
                        nullptr, 
                        UserKeyboards::choose_role_kb()
                        );
                
            }
            return Message::Ptr(nullptr);
        };
    }
}