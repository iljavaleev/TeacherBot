#include <stdio.h>
#include <tgbot/tgbot.h>
#include <memory>
#include <functional>
#include <exception>
#include <cstdlib>
#include <format>

#include "botstaff/handlers/Handlers.hpp"
#include "botstaff/handlers/user_handlers/UserHandlers.hpp"
#include "botstaff/handlers/teacher_handlers/TeacherHandlers.hpp"
#include "botstaff/handlers/teacher_handlers/CreateLessonHandlers.hpp"
#include "botstaff/handlers/user_handlers/UserRegistration.hpp"
#include "botstaff/Commands.hpp"

using namespace TgBot;
using namespace std;


int main() {
    std::string bot_token = std::string(std::getenv("BOT_TOKEN"));
    std::string base_webhook_url = std::string(std::getenv("BASE_WEBHOOK_URL"));
    std::string TEL = std::format("https://api.telegram.org/bot{}/setWebhook?url=", bot_token);
    std::string WEBHOOK_URL = base_webhook_url + std::format("/{}", bot_token);    
    
    TgBot::Bot bot(std::getenv("BOT_TOKEN"));
    std::vector<BotCommand::Ptr> commands = create_commands();
    bot.getApi().setMyCommands(commands);

    bot.getEvents().onCommand("start", CommandHandlers::start_command(bot));
    bot.getEvents().onCommand("cancel", CommandHandlers::cancel_command(bot));
    bot.getEvents().onAnyMessage(Handlers::any_message_handler(bot));
    bot.getEvents().onCallbackQuery(Handlers::calendar_handler(bot));
    bot.getEvents().onCallbackQuery(Handlers::next_month_handler(bot));
    bot.getEvents().onCallbackQuery(Handlers::day_info_handler(bot));
    bot.getEvents().onCallbackQuery(Handlers::calendar_day_handler(bot));

    
    bot.getEvents().onCallbackQuery(UserRegisterHandlers::pupil_rigister_handler(bot));
    bot.getEvents().onCallbackQuery(UserRegisterHandlers::teacher_rigister_handler(bot));
    bot.getEvents().onCallbackQuery(UserRegisterHandlers::user_update_handler(bot));
    bot.getEvents().onCallbackQuery(UserRegisterHandlers::agreement_handler(bot));

    bot.getEvents().onCallbackQuery(UserHandlers::user_start_handler(bot));
    
    bot.getEvents().onCallbackQuery(teacherHandlers::list_active_not_handler(bot));
    bot.getEvents().onCallbackQuery(teacherHandlers::list_user_handler(bot));

    bot.getEvents().onCallbackQuery(teacherHandlers::list_all_teachers_handler(bot));
    bot.getEvents().onCallbackQuery(teacherHandlers::list_teachers_handler(bot));

    bot.getEvents().onCallbackQuery(teacherHandlers::user_info_handler(bot));
    bot.getEvents().onCallbackQuery(teacherHandlers::activate_user(bot));
    bot.getEvents().onCallbackQuery(teacherHandlers::delete_user(bot));
    bot.getEvents().onCallbackQuery(teacherHandlers::update_user(bot));
    bot.getEvents().onCallbackQuery(teacherHandlers::list_comments_handler(bot));
    bot.getEvents().onCallbackQuery(teacherHandlers::comment_text_handler(bot));
    
    bot.getEvents().onCallbackQuery(createLesson::create_lesson_handler(bot));
    bot.getEvents().onCallbackQuery(createLesson::lesson_update_handler(bot));
    bot.getEvents().onCallbackQuery(createLesson::lesson_pupil_handler(bot));
    bot.getEvents().onCallbackQuery(createLesson::lesson_day_date_handler(bot));
    bot.getEvents().onCallbackQuery(createLesson::update_lesson_pupil_handler(bot));
    bot.getEvents().onCallbackQuery(createLesson::lesson_delete_request(bot));
    bot.getEvents().onCallbackQuery(createLesson::delete_lesson_handler(bot));


    signal(SIGINT, [](int s) { printf("SIGINT got\n"); exit(0);});

    startWebhook(bot, WEBHOOK_URL);

    return 0;
}
