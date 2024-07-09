#ifndef states_hpp
#define states_hpp
#include <unordered_map>

#include "botstaff/database/CRUD.hpp"

struct LessonState{
    LessonState(){};
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
    BotUserState(){};
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
    StateForUser(BotUserState& state, BotUser& inst): inst(inst), state(state){}
    StateForUser(const StateForUser& from)
    {
        inst = from.inst;
        state = from.state;
    }
    BotUser inst;
    BotUserState state;
};

struct DayForLesson{
    DayForLesson(LessonState& state, UserLesson& inst): 
    inst(inst), 
    state(state){}
    DayForLesson(const DayForLesson& from)
    {
        inst = from.inst;
        state = from.state;
    }
    UserLesson inst;
    LessonState state;
};

#endif