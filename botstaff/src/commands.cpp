#include "botstaff/commands.hpp"

std::vector<BotCommand::Ptr> create_commands()
{
    std::vector<BotCommand::Ptr> commands;

    BotCommand::Ptr start_command{new BotCommand};
    start_command->command = "start";
    start_command->description = "start dis shit in";
    commands.push_back(start_command);

    BotCommand::Ptr cancel_command{new BotCommand};
    cancel_command->command = "cancel";
    cancel_command->description = "cancel dis shit out";
    commands.push_back(cancel_command);

    BotCommand::Ptr help_command{new BotCommand};
    help_command->command = "help";
    help_command->description = "help your dumb head";
    commands.push_back(help_command);

    return commands;
}