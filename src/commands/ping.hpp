#include <chrono> 

class PingCommand : public BaseCommand {
public:
    PingCommand(dpp::cluster &bot): BaseCommand(bot, "ping") {}

    void handle(const dpp::message &msg) const override {
      auto start = std::chrono::high_resolution_clock::now();
      this->bot->message_create(dpp::message(msg.channel_id, "Pong!"), [this, start](dpp::confirmation_callback_t callback) {
        auto stop = std::chrono::high_resolution_clock::now();
        dpp::message msg = std::get<dpp::message>(callback.value);
        std::chrono::duration<double> elapsed_seconds = stop - start;
        msg.content = fmt::format("Pong!\n**Calc:**{}\n**Real:**{}", elapsed_seconds.count(), this->bot->rest_ping);
        this->bot->message_edit(msg);
      });
    }
};