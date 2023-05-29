#include "Log.hpp"
#include "GameBase.hpp"
#include "Reg.hpp"
#include "Assets.hpp"
#include "World/World.hpp"
#include "TestComponent.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace Teko;

class Game : public GameBase {
protected:
    World* world = nullptr;

    void init() override {
        setMaxTPS(7);
        setMaxFPS(60);

        _window = new sf::RenderWindow(sf::VideoMode(640, 360), "Teko test");

        Assets::loadAsset("asset");

        world = new World();

        Entity* entity = world->createSurface("main")->addEntity("test");
        auto* testComp = new TestComponent();
        testComp->setData({});
        entity->AddComponent(testComp);

        world->selectSurface("main");
    }

    void update(float delta) override {
        world->update(delta);

        sf::Vector2f move;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            move += {-1, 0};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            move += {1, 0};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            move += {0, -1};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            move += {0, 1};
        }

        Camera* camera = world->getSurface("main")->getCamera();
        camera->setPosition(camera->getPosition() + (move * delta * 200.f));
    }

    void tick() override {
        world->tick();
    }

    void draw() override {
        _window->clear();
        _window->draw(*world);
    }

    void event(sf::Event *event) override {
        if (event->type == sf::Event::Closed) close();
    }

    void close() override {
        _stopped = true;
    }
public:
    ~Game() {
        delete world;
    }
};

int main() {
    Game *g = new Game();

    g->start();
    delete g;
}