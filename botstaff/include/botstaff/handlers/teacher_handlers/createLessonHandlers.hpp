#ifndef createLessonHandlers_hpp
#define createLessonHandlers_hpp

#include <tgbot/tgbot.h>
#include "botstaff/states.hpp"
#include <unordered_map>

using namespace TgBot;
using std::unordered_map;

static unordered_map<long, DayForLesson> lessonState;
void clear_lesson_state(long chat_id);
Message::Ptr check_lesson_state( 
    TgBot::Bot& bot, 
    const Message::Ptr message
    );

Message::Ptr lesson_time_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );

Message::Ptr lesson_objectives_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
Message::Ptr lesson_comment_for_pupil_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
Message::Ptr lesson_comment_for_teacher_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
    );
// Message::Ptr lesson_paid_handler(
//     TgBot::Bot& bot, 
//     const Message::Ptr message,
//     bool update
//     );

Message::Ptr send_lesson_info_to_pupil(
    TgBot::Bot& bot,
    const Message::Ptr message,
    UserLesson& lesson
    );

Message::Ptr send_lesson_update_kb(
    TgBot::Bot& bot, 
    const Message::Ptr& message
    );

#endif 