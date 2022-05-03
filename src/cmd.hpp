class BaseCommand;

std::map<std::string, BaseCommand*> cmds = {};

class BaseCommand {
  std::string name;
public:
  dpp::cluster* bot;
  BaseCommand(dpp::cluster &bot, const std::string &name):
    bot(&bot), name(name) {
        cmds.insert({ name, this });
    }
  virtual void handle(const dpp::message &msg) const = 0; // pure virtual 
};

bool find_commands(std::string cmd, dpp::message msg) {
    if (cmds.find(cmd) != cmds.end()) {
        cmds.at(cmd)->handle(msg);
        return true;
    } else {
        return false;
    }
}