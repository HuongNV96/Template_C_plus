#include "HandlerTemplate.hpp"

class Handler: public HandlerTemplate<Event> {
public :
    void handle(std::unique_ptr<Event> & message) override {
        std::cout << message->type << std::endl; 
    }
};

int main() {
    Handler handler;
    Event event;
    event.type  = 100;
    handler.sendMessage(event);
    std::this_thread::sleep_for(1s);
}