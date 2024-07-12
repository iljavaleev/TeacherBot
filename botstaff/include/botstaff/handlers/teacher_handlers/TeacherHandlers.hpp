#ifndef TeacherHandlers_hpp
#define TeacherHandlers_hpp

#include <tgbot/tgbot.h>
#include <functional>

using namespace TgBot;
using namespace std;


namespace teacherHandlers
{
    class list_all_teachers_handler{
        const TgBot::Bot& bot;
    public:
        list_all_teachers_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };
    
    class list_teachers_handler{
        const TgBot::Bot& bot;
    public:
        list_teachers_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class list_user_handler{
        const TgBot::Bot& bot;
    public:
        list_user_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class list_active_not_handler{
        const TgBot::Bot& bot;
    public:
        list_active_not_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class user_info_handler{
        const TgBot::Bot& bot;
    public:
        user_info_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class activate_user{
        const TgBot::Bot& bot;
    public:
        activate_user(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class delete_user{
        const TgBot::Bot& bot;
    public:
        delete_user(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class update_user{
        const TgBot::Bot& bot;
    public:
        update_user(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class comment_text_handler{
        const TgBot::Bot& bot;
    public:
        comment_text_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class list_comments_handler{
        const TgBot::Bot& bot;
    public:
        list_comments_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };
}

namespace createLesson
{
    class create_lesson_handler{
        const TgBot::Bot& bot;
    public:
        create_lesson_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class lesson_update_handler{
        const TgBot::Bot& bot;
    public:
        lesson_update_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class lesson_pupil_handler{
        const TgBot::Bot& bot;
    public:
        lesson_pupil_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class lesson_day_date_handler{
        const TgBot::Bot& bot;
    public:
        lesson_day_date_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class update_lesson_pupil_handler{
        const TgBot::Bot& bot;
    public:
        update_lesson_pupil_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class lesson_delete_request{
        const TgBot::Bot& bot;
    public:
        lesson_delete_request(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class delete_lesson_handler{
        const TgBot::Bot& bot;
    public:
        delete_lesson_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };
}


#endif