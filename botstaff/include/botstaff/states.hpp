#ifndef States_hpp
#define States_hpp

#include <unordered_map>
#include <memory>

#include "botstaff/database/CRUD.hpp"

struct LessonState{
    bool update{false};
    bool date{false};
    bool pupil{false};
    bool time{false};
    bool objectives{false};
    bool comment_for_pupil{false};
    bool comment_for_teacher{false};
    bool paid{false};
};

struct BotUserState{
    bool update{false};
    bool teacher{false};
    bool first_name{false};
    bool last_name{false};
    bool phone{false};
    bool email{false}; 
    bool user_class{false};
    bool comment{false};
};


struct StateForUser{
    StateForUser(BotUserState& state, BotUser& inst): 
    inst(std::shared_ptr<BotUser>(new BotUser(inst))), 
    state(std::shared_ptr<BotUserState>(new BotUserState(state))){}
    
    StateForUser(const StateForUser& from)
    {
        inst = std::shared_ptr<BotUser>(new BotUser(*(from.inst)));
        state = std::shared_ptr<BotUserState>(new BotUserState(*(from.state)));
    }

    StateForUser(
        const std::shared_ptr<BotUser>& inst, 
        const std::shared_ptr<BotUserState>& state
    ): inst(inst), state(state){}


    std::shared_ptr<BotUser> inst;
    std::shared_ptr<BotUserState> state;
};

struct DayForLesson{
    DayForLesson(LessonState& state, UserLesson& inst): 
    inst(std::shared_ptr<UserLesson>(new UserLesson(inst))), 
    state(std::shared_ptr<LessonState>(new LessonState(state))){}
    
    DayForLesson(
        const std::shared_ptr<LessonState>& state, 
        const std::shared_ptr<UserLesson>& inst
    ): inst(inst), state(state){}
    
    DayForLesson(const DayForLesson& from)
    {
        inst = std::shared_ptr<UserLesson>(new UserLesson(*(from.inst)));
        state = std::shared_ptr<LessonState>(new LessonState(*(from.state)));
    }
    std::shared_ptr<UserLesson> inst;
    std::shared_ptr<LessonState> state;
};

#endif