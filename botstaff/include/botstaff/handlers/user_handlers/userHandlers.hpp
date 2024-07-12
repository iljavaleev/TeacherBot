#ifndef UserHandlers_hpp
#define UserHandlers_hpp

#include <tgbot/tgbot.h>
#include <functional>

using namespace TgBot;
using namespace std;
 

namespace UserHandlers
{   
    class user_start_handler{
        const TgBot::Bot& bot;
    public:
        user_start_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };
}

namespace UserRegisterHandlers
{   
    class pupil_rigister_handler{
        const TgBot::Bot& bot;
    public:
        pupil_rigister_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class teacher_rigister_handler{
        const TgBot::Bot& bot;
    public:
        teacher_rigister_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class agreement_handler{
        const TgBot::Bot& bot;
    public:
        agreement_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };

    class user_update_handler{
        const TgBot::Bot& bot;
    public:
        user_update_handler(const TgBot::Bot& _bot):bot(_bot){}
        Message::Ptr operator()(const CallbackQuery::Ptr&);
    };
}

#endif