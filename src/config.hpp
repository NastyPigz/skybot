// configuration file... including all the commands
#include "commands/ping.hpp"
#include "commands/test.hpp"
#include "commands/collect.hpp"

void initCommands(dpp::cluster &bot) {
    new TestCommand(bot);
    new PingCommand(bot);
    new CollectCommand(bot);
}