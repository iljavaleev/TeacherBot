#ifndef handlers_hpp
#define handlers_hpp
#include <tgbot/tgbot.h>
#include <exception>
#include <functional>
#include "botstaff/database/psql.hpp"
#include "botstaff/utils.hpp"
#include "botstaff/states.hpp"
#include "botstaff/database/CRUD.hpp"
#include <unordered_map>

using namespace TgBot;
using namespace std;


namespace CommandHandlers
{
    extern std::function<Message::Ptr (Message::Ptr)> startCommand(TgBot::Bot& bot);
    extern std::function<Message::Ptr (Message::Ptr)> cancelCommand(TgBot::Bot& bot);
    extern std::function<Message::Ptr (Message::Ptr)> helpCommand(TgBot::Bot& bot);   
};

namespace Handlers
{   
    extern std::function<Message::Ptr (Message::Ptr)> any_message_handler(TgBot::Bot& bot);   
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> calendar_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> next_month_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> calendar_day_handler(TgBot::Bot& bot);
    extern std::function<Message::Ptr (CallbackQuery::Ptr)> day_info_handler(TgBot::Bot& bot);
};


void startPolling(TgBot::Bot& bot);
void startWebhook(TgBot::Bot& bot, std::string& webhookUrl);

#endif