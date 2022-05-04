class message_collector : public dpp::message_collector {
public:
    message_collector(dpp::cluster* cl, uint64_t duration) : dpp::message_collector(cl, duration) {
        std::cout << "aaaa";
        std::ofstream myfile;
        myfile.open ("./example.txt");
        myfile << "Writing this to a file.\n";
        myfile.close();
    }

    virtual void completed(const std::vector<dpp::message>& list) {
        if (list.size()) {
            owner->message_create(dpp::message(list[0].channel_id, "I collected " + std::to_string(list.size()) + " messages!"));
        } else {
            owner->message_create(dpp::message("... I got nothin'."));
        }
    }

    virtual const dpp::message* filter(const dpp::message_create_t& m) {
        owner->message_create(dpp::message(m.msg.channel_id, "test1"));
        if (m.msg.content.find("a") != std::string::npos) {
            owner->message_create(dpp::message(m.msg.channel_id, "test2"));
            return &m.msg;
        } else {
            return nullptr;
        }
    }
};

class CollectCommand: public BaseCommand {
public:
    CollectCommand(dpp::cluster &bot): BaseCommand(bot, "collect") {}

    void handle(const dpp::message &msg) const override {
        this->bot->message_create(dpp::message(msg.channel_id, "Waiting for a message..."));
        new message_collector(bot, 2);
        // std::shared_ptr<message_collector> sptr(new message_collector(this->bot));
    }
};