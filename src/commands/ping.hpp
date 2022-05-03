#include <chrono> 


class PingCommand : public BaseCommand {
public:

  PingCommand(dpp::cluster &bot): BaseCommand(bot, "ping") {}

  void handle(const dpp::message &msg) const override {
    // this->bot->message_create(dpp::message(msg.channel_id, fmt::format("Pong! {}", this->bot->rest_ping)));
    auto start = std::chrono::high_resolution_clock::now();
    this->bot->message_create(dpp::message(msg.channel_id, "Pong!"), [this, start](dpp::confirmation_callback_t callback) {
      auto stop = std::chrono::high_resolution_clock::now();
      dpp::message msg = std::get<dpp::message>(callback.value);
      std::chrono::duration<double> elapsed_seconds = stop - start;
      msg.content = fmt::format("Pong!\n**Calc:**{}\n**Real:**{}", elapsed_seconds.count(), this->bot->rest_ping);
      this->bot->message_edit(msg);
    });
    // auto msg = std::get<2>(callback.value);
    // this->bot->message_edit(msg);
    // [&this](dpp::confirmation_callback_t::value v) {
    //   auto stop = std::chrono::high_resolution_clock::now();
    //   auto msg = std::get<2>(v);
    //   this->bot->message_edit(dpp::message("mhm"));
    // }
  }
};