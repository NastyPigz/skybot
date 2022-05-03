class TestCommand : public BaseCommand {
public:
  TestCommand(dpp::cluster &bot): BaseCommand(bot, "test") {}

  void handle(const dpp::message &msg) const override {
    this->bot->message_create(dpp::message(msg.channel_id, "Test successfully. Bot is up and running."));
  }
};