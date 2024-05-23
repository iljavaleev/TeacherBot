#include "botstaff/handlers/user_handlers/userRegistration.hpp"
#include "botstaff/database/CRUD.hpp"
#include "botstaff/handlers/handlers.hpp"
#include "botstaff/keyboards/teacher_keyboards/teacherKeyboards.hpp"
#include "botstaff/keyboards/user_keyboards/userKeyboards.hpp"
#include "botstaff/keyboards/keyboards.hpp"
#include "botstaff/states.hpp"
#include <unordered_map>
#include "botstaff/utils.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


namespace UserRegisterHandlers
{
    
    std::function<Message::Ptr (CallbackQuery::Ptr)> pupil_rigister_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::startsWith(query->data, "register_pupil")) 
            {
                auto info = StringTools::split(query->data, ' ');
                if (info.size() == 1)
                {
                    clear_user_state(query->message->chat->id);
                    botUser current_user(query->message->chat->id);
                    current_user.tgusername = query->message->chat->username;
                    current_user.role = "pupil";
                    
                    BotUserState current_user_state;
                    current_user_state.teacher = true;                    
                    StateForUser state_inst(current_user_state, current_user);
                    userState.insert({current_user.chat_id, state_inst});
                    
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Выберите учителя",
                        false,
                        0,
                        UserKeyboards::create_list_teachers_kb()
                    ); 
                }
                else
                {
                    userState.at(query->message->chat->id).state.teacher = false;
                    userState.at(query->message->chat->id).inst.teacher = stol(info.at(1));    
                    userState.at(query->message->chat->id).state.first_name = true;
                    
                    return bot.getApi().sendMessage(query->message->chat->id, "Введите имя");

                }            
            } 
            else
                return Message::Ptr(nullptr);
        };
    }

    std::function<Message::Ptr (CallbackQuery::Ptr)> teacher_rigister_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (query->data == "register_teacher") 
            {
                clear_user_state(query->message->chat->id);

                botUser current_user(query->message->chat->id);
                current_user.tgusername = query->message->chat->username;
                current_user.role = "teacher";
                
                BotUserState current_user_state;
                current_user_state.first_name = true;
                
                StateForUser state_inst(current_user_state, current_user);
                userState.insert({current_user.chat_id, state_inst});


                return bot.getApi().sendMessage(
                    query->message->chat->id, 
                    "Введите имя");  
            } 
            else
                return Message::Ptr(nullptr);
        };
    }


    std::function<Message::Ptr (CallbackQuery::Ptr)> agreement_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::startsWith(query->data, "agreement")) 
            {   
                std::string message{};
                if(StringTools::split(query->data, ' ').at(1) == "yes")
                {
                    userState.at(query->message->chat->id).inst.create();
                    if (userState.at(query->message->chat->id).inst.role == "pupil")
                    {
                        std::string text = std::format(
                            "Запрос от ученика:\n\n{}\n\nВы можете принять его в списке учеников бота", 
                            get_pupil_info(userState.at(query->message->chat->id).inst)
                            );
                        query->data = " ";
                        
                        try
                        {
                            bot.getApi().sendMessage(
                                userState.at(query->message->chat->id).inst.teacher, 
                                text,
                                false,
                                0,
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
                    message = "Извините, вы не сможете пользоваться нашим ботом";
                clear_user_state(query->message->chat->id);
                return  bot.getApi().sendMessage(query->message->chat->id, message);
            } 
            else
                return Message::Ptr(nullptr);
        };
    }




    std::function<Message::Ptr (CallbackQuery::Ptr)> user_update_handler(TgBot::Bot& bot)
    {
        return [&bot](CallbackQuery::Ptr query) 
        {
            if (StringTools::startsWith(query->data, "update_user_field") && is_admin(query->message->chat->id)) 
            {
                
                std::vector<std::string> info = StringTools::split(query->data, ' ');
                long admin_chat_id{query->message->chat->id};
                
                if (info.at(1) == "finish")
                {
                    userState.at(admin_chat_id).inst.update();
                    clear_user_state(admin_chat_id);
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Вы закончили редактирование"
                    );  
                }
                    
                if (!userState.contains(admin_chat_id))
                {
                    botUser user = botUser::get(std::stol(info.at(2)));
                    BotUserState user_state;
                    StateForUser state_inst(user_state, user);
                    userState.insert({admin_chat_id, state_inst});
                }
                
                if (info.at(1) == "first_name")
                {
                    userState.at(admin_chat_id).state.first_name = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите имя"
                    );  
                }
                else if (info.at(1) == "last_name")
                {
                    userState.at(admin_chat_id).state.last_name = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите фамилию"
                    );  
                }
                else if (info.at(1) == "class")
                {
                    userState.at(admin_chat_id).state.user_class = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите класс"
                    );  
                }
                else if (info.at(1) == "phone")
                {
                    userState.at(admin_chat_id).state.phone = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите телефон"
                    );  
                }
                else if (info.at(1) == "email")
                {
                    userState.at(admin_chat_id).state.email = true;
                    return bot.getApi().sendMessage(
                        query->message->chat->id, 
                        "Введите почту"
                    );  
                }
                else
                {
                    userState.at(admin_chat_id).state.comment = true;
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
}

Message::Ptr check_user_state(
    TgBot::Bot& bot, 
    const Message::Ptr message
    )
{   
    bool update{false};
    if (is_teacher(message->chat->id))
        update = true;
    long chat_id{message->chat->id};
    if (userState.contains(chat_id))
    {
        if (userState.at(chat_id).state.first_name)
        {   
            return user_first_name_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state.last_name)
        {
            return user_last_name_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state.email)
        {
            return user_email_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state.phone)
        {
            return user_phone_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state.user_class)
        {   
            return user_class_handler(bot, message, update);
        }
        else if (userState.at(chat_id).state.comment)
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
    TgBot::Bot& bot, 
    const Message::Ptr& message,
    bool update, 
    std::string role
    )
{
    return bot.getApi().sendMessage(
                    message->chat->id, 
                    "Редактирование",
                    false,
                    0,
                    teacherKeyboards::update_user_info_kb(role, message->chat->id)
                ); 
}





Message::Ptr user_first_name_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    userState.at(message->chat->id).state.first_name = false;
    userState.at(message->chat->id).inst.first_name = string_to_upper(message->text);
    
    
    userState.at(message->chat->id).state.last_name = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите фамилию");

}

Message::Ptr user_last_name_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{   
    userState.at(message->chat->id).state.last_name = false;
    userState.at(message->chat->id).inst.last_name = string_to_upper(message->text);
    if (update)
        send_update_kb(bot, message, update, userState.at(message->chat->id).inst.role);
    
    userState.at(message->chat->id).state.phone = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите номер телефона"); 
}

Message::Ptr user_phone_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    userState.at(message->chat->id).state.phone = false;
    userState.at(message->chat->id).inst.phone = message->text;
    if (update)
        send_update_kb(bot, message, update, userState.at(message->chat->id).inst.role);
   
    userState.at(message->chat->id).state.email = true;
    return bot.getApi().sendMessage(message->chat->id, "Введите адрес электронной почты");
  
        
}

Message::Ptr user_email_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    userState.at(message->chat->id).state.email = false;
    userState.at(message->chat->id).inst.email = message->text;
    if (update)
        send_update_kb(bot, message, update, userState.at(message->chat->id).inst.role);
    
    if (userState.at(message->chat->id).inst.role == "pupil")
    {
         userState.at(message->chat->id).state.user_class = true;
        return bot.getApi().sendMessage(message->chat->id, "Введите класс обучения");   
    }
    
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Нам нужно ваше согласие на хранение и обработку введенной информации",
        false,
        0, 
        Keyboards::agreement_kb()
        );
}
    

Message::Ptr user_class_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    userState.at(message->chat->id).state.user_class = false;
    userState.at(message->chat->id).inst.cls = message->text;
    if (update)
        send_update_kb(bot, message, update, userState.at(message->chat->id).inst.role);
    
    return bot.getApi().sendMessage(
        message->chat->id, 
        "Нам нужно ваше согласие на хранение и обработку введенной информации",
        false,
        0, 
        Keyboards::agreement_kb()
        );
}

Message::Ptr user_comment_handler(
    TgBot::Bot& bot, 
    const Message::Ptr message,
    bool update
    )
{
    userState.at(message->chat->id).state.comment = false;
    userState.at(message->chat->id).inst.comment = message->text;
    return send_update_kb(bot, message, update, userState.at(message->chat->id).inst.role);
}
