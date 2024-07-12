#ifndef CreateLessonHandlers_hpp
#define CreateLessonHandlers_hpp

#include <tgbot/tgbot.h>
#include <unordered_map>

#include "botstaff/States.hpp"

using namespace TgBot;
using std::unordered_map;

static unordered_map<long, DayForLesson> lessonState;

void clear_lesson_state(long chat_id);

Message::Ptr check_lesson_state( 
    const TgBot::Bot& bot, 
    const Message::Ptr message
);

Message::Ptr lesson_time_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
);

Message::Ptr lesson_objectives_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
);

Message::Ptr lesson_comment_for_pupil_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
);

Message::Ptr lesson_comment_for_teacher_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update = false
);

// Message::Ptr lesson_paid_handler(
//     TgBot::Bot& bot, 
//     const Message::Ptr message,
//     bool update
//     );

Message::Ptr send_lesson_info_to_pupil(
    const TgBot::Bot& bot,
    std::string& message,
    long pupil_id
);

Message::Ptr send_lesson_update_kb(
    const TgBot::Bot& bot, 
    const Message::Ptr& message
);

#endif 