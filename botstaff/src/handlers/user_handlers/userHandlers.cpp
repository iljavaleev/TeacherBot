#include "botstaff/handlers/user_handlers/UserHandlers.hpp"

#include <tgbot/tgbot.h>
#include <functional>

#include "botstaff/States.hpp"
#include "botstaff/Utils.hpp"
#include "botstaff/handlers/Handlers.hpp"
#include "botstaff/handlers/user_handlers/UserRegistration.hpp"
#include "botstaff/keyboards/user_keyboards/UserKeyboards.hpp"

using namespace TgBot;
using namespace std;


namespace UserHandlers
{
    Message::Ptr user_start_handler::operator()(const CallbackQuery::Ptr& query)
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
    }
}