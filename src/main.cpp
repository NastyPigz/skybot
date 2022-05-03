#include <dpp/dpp.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <filesystem>
#include <dpp/fmt/format.h>
#include <map>
#include "cmd.hpp"
#include "config.hpp"

void ls_recursive(const std::filesystem::path& path) {
    for(const auto& p: std::filesystem::recursive_directory_iterator(path)) {
        if (!std::filesystem::is_directory(p)) {
            std::cout << p.path().u8string().substr(6) << '\n';
        }
    }
}

void join(const std::vector<std::string>& v, char c, std::string& s) {

    s.clear();

    for (std::vector<std::string>::const_iterator p = v.begin(); p != v.end(); ++p) {
        s += *p;
        if (p != v.end() - 1)
            s += c;
    }
}

int main() {
    // comment this out for faster recompile
    ls_recursive("./src/commands");

	if (!getenv("DISCORD_TOKEN")) {
		std::cout << "Could not find the DISCORD_TOKEN environment variable.\n";
		return 1;
	}

    dpp::cluster bot(getenv("DISCORD_TOKEN"), dpp::i_default_intents | dpp::i_message_content);

    bot.on_ready([&bot](const dpp::ready_t & event) {
        std::cout << "Logged in as " << bot.me.username << "!\n";
    });

    // std::cout << typeid(bot).name();
    
    initCommands(bot);

    bot.on_message_create([&bot](const dpp::message_create_t & event) {
        if (event.msg.author.is_bot()) {
            return;
        }
        if (event.msg.content == "test") {
            bot.message_create(dpp::message(event.msg.channel_id, "Test success"));
        }
        if (event.msg.content.rfind("s!", 0) == 0 && event.msg.content.length() > 2) {
            std::string content = event.msg.content.substr(2);
            std::stringstream ss(content);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> vstrings(begin, end);
            std::string cmd = vstrings[0];
            std::transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c){ return std::tolower(c); });
            std::string s;
            vstrings.erase(vstrings.begin());
            join(vstrings, ',', s);
            
            // dbg print
            // std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
            if (!find_commands(cmd, event.msg)) {
               bot.message_create(dpp::message(event.msg.channel_id, fmt::format("Prefix detected! Cmd: {} Args: (len = {}) {}", cmd, std::to_string(vstrings.size()), s)));
            }
        }
    });
 
    bot.start(false);
    return 0;
}
