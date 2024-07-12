#ifndef UserRegistration_hpp
#define UserRegistration_hpp

#include <tgbot/tgbot.h>
#include <unordered_map>

#include "botstaff/States.hpp"

using namespace TgBot;
using std::unordered_map;

static unordered_map<long, StateForUser> userState;

void clear_user_state(long user_id);

Message::Ptr check_user_state( 
    const TgBot::Bot& bot, 
    const Message::Ptr& message
);

Message::Ptr user_first_name_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update = false
);

Message::Ptr user_last_name_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update = false
);

Message::Ptr user_phone_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update = false
);

Message::Ptr user_email_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update = false
);

Message::Ptr user_class_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update = false
);

Message::Ptr user_comment_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update
);

#endif 