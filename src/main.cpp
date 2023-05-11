#include "jage/engine.hpp"

#include "jage/event/timerevent.hpp"

int main() {

    jage::event::DummyEvent::Manager dummyManager;

    {
        jage::event::DummyEvent listenerOne("hi");
        dummyManager += listenerOne;

        {
            jage::event::DummyEvent listenerTwo("hey");
            dummyManager += listenerTwo;

            dummyManager.notifyAll(1);
        }

        dummyManager.notifyAll(2);
    }

    dummyManager.notifyAll(3);

//    auto& engine = jage::JAGEngine::getInstance();
//    engine.init();
//    engine.loadScene();
//    engine.loop();

    return 0;
}
