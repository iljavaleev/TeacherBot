#include "botstaff/commands.hpp"

std::vector<BotCommand::Ptr> create_commands()
{
    std::vector<BotCommand::Ptr> commands;

    BotCommand::Ptr start_command{new BotCommand};
    start_command->command = "menu";
    start_command->description = "выход в главное меню";
    commands.push_back(start_command);

    BotCommand::Ptr cancel_command{new BotCommand};
    cancel_command->command = "cancel";
    cancel_command->description = "сброс/отмена";
    commands.push_back(cancel_command);

    BotCommand::Ptr help_command{new BotCommand};
    help_command->command = "calendar";
    help_command->description = "переход в календарь";
    commands.push_back(help_command);

    return commands;
}