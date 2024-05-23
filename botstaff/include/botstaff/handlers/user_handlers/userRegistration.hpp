#ifndef userRegistration_hpp
#define userRegistration_hpp
#include <tgbot/tgbot.h>
#include "botstaff/states.hpp"
#include <unordered_map>

using namespace TgBot;
using std::unordered_map;

static unordered_map<long, StateForUser> userState;

void clear_user_state(long user_id);
Message::Ptr check_user_state( 
    TgBot::Bot& bot, 
    const Message::Ptr message
    );

Message::Ptr user_first_name_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
Message::Ptr user_last_name_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
Message::Ptr user_phone_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
Message::Ptr user_email_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
Message::Ptr user_class_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
Message::Ptr user_comment_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    );

#endif 