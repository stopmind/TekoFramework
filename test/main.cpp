#include "Log.hpp"
#include "GameBase.hpp"
#include "Reg.hpp"
#include "Assets.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace Teko;

class Game : public GameBase {
protected:
    sf::Sprite *sprite;

    void init() override {
        setMaxTPS(7);
        setMaxFPS(60);

        window = new sf::RenderWindow(sf::VideoMode(640, 360), "Teko test");

        //Test reg

        RegNode* node = Reg::root->addNode("Test");
        Log::info(node->getOwner()->getName());
        if (Reg::root->getNode("Test") != node) Log::erro("Чет не по плану все пошло.");
        Log::info(Reg::root->getChildren()[0]->getName());
        Log::info(Reg::root->hasNode("Test") ? "true" : "false");
        Reg::root->delNode("Test");
        Log::info(Reg::root->hasNode("Test") ? "true" : "false");

        Assets::loadAsset("asset");

        sf::Texture *tex = (sf::Texture *)(Reg::root->getNode("Textures::Agent")->data);

        sprite = new sf::Sprite();
        sprite->setTexture(*tex);
        sprite->scale(sf::Vector2f(3.f, 3.f));
    }

    void update() override {

    }

    void tick() override {
        
    }

    void draw() override {
        window->draw(*sprite);
    }

    void event(sf::Event *event) override {
        if (event->type == sf::Event::Closed) close();
    }

    void close() override {
        stopped = true;
    }
public:
    ~Game() {
        delete sprite;
    }
};

int main() {
    Game *g = new Game();

    g->start();
    delete g;
}