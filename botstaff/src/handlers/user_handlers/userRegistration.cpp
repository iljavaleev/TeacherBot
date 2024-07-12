#include "botstaff/handlers/user_handlers/UserRegistration.hpp"

#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

#include "botstaff/database/CRUD.hpp"
#include "botstaff/handlers/Handlers.hpp"
#include "botstaff/handlers/user_handlers/UserHandlers.hpp"
#include "botstaff/keyboards/teacher_keyboards/TeacherKeyboards.hpp"
#include "botstaff/keyboards/user_keyboards/UserKeyboards.hpp"
#include "botstaff/keyboards/Keyboards.hpp"
#include "botstaff/Utils.hpp"
#include "botstaff/States.hpp"

namespace UserRegisterHandlers
{
    Message::Ptr pupil_rigister_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if (StringTools::split(query->data, ' ').at(0) == "register_pupil") 
        {
            auto info = StringTools::split(query->data, ' ');
            if (info.size() == 1)
            {
                clear_user_state(query->message->chat->id);
                std::shared_ptr<BotUser> current_user(
                    new BotUser(query->message->chat->id)
                );
                current_user->tgusername = query->message->chat->username;
                current_user->role = "pupil";
                
                std::shared_ptr<BotUserState> current_user_state(
                    new BotUserState()
                );
                current_user_state->teacher = true;                    
                
                StateForUser state_inst(current_user, current_user_state);
                userState.insert({current_user->chat_id, state_inst});
                
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Выберите учителя",
                    nullptr,
                    nullptr,
                    UserKeyboards::create_list_teachers_kb()
                ); 
            }
            else
            {
                userState.at(query->message->chat->id).state->teacher = 
                false;
                userState.at(query->message->chat->id).inst->teacher = 
                stol(info.at(1));    
                userState.at(query->message->chat->id).state->first_name = 
                true;
                
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите ваше имя"
                );

            }            
        } 
        else
            return Message::Ptr(nullptr);
    }

    Message::Ptr teacher_rigister_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if (query->data == "register_teacher") 
        {
            clear_user_state(query->message->chat->id);

            std::shared_ptr<BotUser> current_user(
                new BotUser(query->message->chat->id)
            );
            current_user->tgusername = query->message->chat->username;
            current_user->role = "teacher";
            
            std::shared_ptr<BotUserState> current_user_state(
                new BotUserState()
            );
            current_user_state->first_name = true;
            
            StateForUser state_inst(current_user, current_user_state);
            userState.insert({current_user->chat_id, state_inst});


            return bot.getApi().sendMessage(
                query->message->chat->id, 
                "Введите ваше имя");  
        } 
        else
            return Message::Ptr(nullptr);
    }

    Message::Ptr agreement_handler::operator()(const CallbackQuery::Ptr& query)
    {
        if (StringTools::split(query->data, ' ').at(0) == "agreement")
        {   
            std::string message{};
            if(StringTools::split(query->data, ' ').at(1) == "yes")
            {
                userState.at(query->message->chat->id).inst->create();
                if (userState.at(query->message->chat->id).inst->role 
                == "pupil")
                {
                    std::string text = std::format(
                        "Запрос от ученика:\n\n{}\n\n"
                        "Вы можете принять его в списке учеников бота", 
                        get_pupil_info(
                            userState.at(query->message->chat->id).inst
                        )
                    );
                    query->data = " ";
                    
                    try
                    {
                        bot.getApi().sendMessage(
                            userState.at(
                                query->message->chat->id
                            ).inst->teacher, 
                            text,
                            nullptr,
                            nullptr,
                            nullptr,
                            "HTML"
                            );
                    }
                    catch (std::exception& e)
                    {
                        std::cerr << e.what() << std::endl;
                    }    
                }
                message = "Вы успешно прошли регистрацию";
            }
            else
                message = "Извините, вы не сможете "
                "пользоваться нашим ботом";
            clear_user_state(query->message->chat->id);
            return  bot.getApi().sendMessage(
                query->message->chat->id, 
                message
            );
        } 
        else
            return Message::Ptr(nullptr);
    }


    Message::Ptr user_update_handler::operator()(
        const CallbackQuery::Ptr& query
    )
    {
        if ((StringTools::split(query->data, ' ').at(0) == 
        "update_user_field") && is_teacher(query->message->chat->id))
        {
            std::vector<std::string> info = StringTools::split(
                query->data, ' '
            );
            long admin_chat_id{query->message->chat->id};
            
            if (info.at(1) == "finish")
            {
                userState.at(admin_chat_id).inst->update();
                std::shared_ptr<BotUser> tmp = 
                userState.at(admin_chat_id).inst;
                clear_user_state(admin_chat_id);

                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    tmp->role == "user" ? get_pupil_info(tmp) : 
                    get_teacher_info(tmp),
                    nullptr,
                    nullptr,
                    teacherKeyboards::create_user_info_kb(*tmp),
                    "HTML"
                );  
            }
                
            if (!userState.contains(admin_chat_id))
            {
                std::shared_ptr<BotUser> user = BotUser::get(
                    std::stol(info.at(2))
                );
                std::shared_ptr<BotUserState> user_state(
                    new BotUserState()
                );
                StateForUser state_inst(user, user_state);
                userState.insert({admin_chat_id, state_inst});
            }
            
            if (info.at(1) == "first_name")
            {
                userState.at(admin_chat_id).state->first_name = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите имя"
                );  
            }
            else if (info.at(1) == "last_name")
            {
                userState.at(admin_chat_id).state->last_name = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите фамилию"
                );  
            }
            else if (info.at(1) == "class")
            {
                userState.at(admin_chat_id).state->user_class = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите класс"
                );  
            }
            else if (info.at(1) == "phone")
            {
                userState.at(admin_chat_id).state->phone = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите телефон"
                );  
            }
            else if (info.at(1) == "email")
            {
                userState.at(admin_chat_id).state->email = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите почту"
                );  
            }
            else
            {
                userState.at(admin_chat_id).state->comment = true;
                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите комментарий"
                );  
            }
        } 
        else
            return Message::Ptr(nullptr);
    };
}

Message::Ptr check_user_state(
    const TgBot::Bot& bot, 
    const Message::Ptr& message
    )
{   
    bool update{false};
    if (is_teacher(message->chat->id))
        update = true;
    long chat_id{message->chat->id};
    if (userState.contains(chat_id))
    {
        if (userState.at(chat_id).state->first_name)
        {   
            return user_first_name_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state->last_name)
        {
            return user_last_name_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state->email)
        {
            return user_email_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state->phone)
        {
            return user_phone_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state->user_class)
        {   
            return user_class_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state->comment)
        {   
            return user_comment_handler(bot, message, update);
        }
    }
    return Message::Ptr(nullptr);
}

void clear_user_state(long user_id)
{
    if (userState.contains(user_id))
    {
        userState.erase(user_id);
    }
}

Message::Ptr send_update_kb(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update, 
    std::string role
    )
{
    return bot.getApi().sendMessage(
                    message->chat->id, 
                    "Редактирование",
                    nullptr,
                    nullptr,
                    teacherKeyboards::update_user_info_kb(
                        role, 
                        message->chat->id
                    )
                ); 
}


Message::Ptr user_first_name_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update
    )
{
    userState.at(message->chat->id).state->first_name = false;
    userState.at(message->chat->id).inst->first_name = string_to_upper(
        message->text
    );
    if (update)
        return send_update_kb(
            bot, 
            message, 
            update, 
            userState.at(message->chat->id).inst->role
        );
    
    userState.at(message->chat->id).state->last_name = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите фамилию");

}

Message::Ptr user_last_name_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update
    )
{   
    userState.at(message->chat->id).state->last_name = false;
    userState.at(message->chat->id).inst->last_name = string_to_upper(
        message->text
    );
    if (update)
        return send_update_kb(
            bot, 
            message, 
            update, 
            userState.at(message->chat->id).inst->role
        );
    
    userState.at(message->chat->id).state->phone = true;
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Введите номер телефона"
    ); 
}

Message::Ptr user_phone_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update
    )
{
    userState.at(message->chat->id).state->phone = false;
    userState.at(message->chat->id).inst->phone = message->text;
    if (update)
        return send_update_kb(bot, message, update, userState.at(
            message->chat->id
        ).inst->role
    );
   
    userState.at(message->chat->id).state->email = true;
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Введите адрес электронной почты"
    );
}

Message::Ptr user_email_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update
    )
{
    userState.at(message->chat->id).state->email = false;
    userState.at(message->chat->id).inst->email = message->text;
    if (update)
        return send_update_kb(
            bot, 
            message, 
            update, 
            userState.at(message->chat->id).inst->role
        );
    
    if (userState.at(message->chat->id).inst->role == "pupil")
    {
         userState.at(message->chat->id).state->user_class = true;
        return bot.getApi().sendMessage(
            message->chat->id, 
            "Введите класс обучения"
        );   
    }
    
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Нам нужно ваше согласие на хранение и обработку введенной информации",
        nullptr,
        nullptr, 
        Keyboards::agreement_kb()
        );
}
    

Message::Ptr user_class_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update
    )
{
    userState.at(message->chat->id).state->user_class = false;
    userState.at(message->chat->id).inst->cls = message->text;
    if (update)
        return send_update_kb(
            bot, 
            message, 
            update, 
            userState.at(message->chat->id).inst->role
        );
    
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Нам нужно ваше согласие на хранение и обработку введенной информации",
        nullptr,
        nullptr, 
        Keyboards::agreement_kb()
        );
}

Message::Ptr user_comment_handler(
    const TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update
    )
{
    userState.at(message->chat->id).state->comment = false;
    userState.at(message->chat->id).inst->comment = message->text;
    return send_update_kb(
        bot, 
        message, 
        update, 
        userState.at(message->chat->id).inst->role
    );
}
