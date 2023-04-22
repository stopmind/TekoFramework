#include "Log.hpp"
#include "GameBase.hpp"
#include "Reg.hpp"
#include <iostream>

using namespace Teko;

class Game : public GameBase {
    protected:

    void init() override {
        setMaxTPS(7);
        setMaxFPS(60);

        //Test reg

        RegNode* node = Reg::root->addNode("Test");
        Log::info(node->getOwner()->getName());
        if (Reg::root->getNode("Test") != node) Log::erro("Чет не по плану все пошло.");
        Log::info(Reg::root->getChildren()[0]->getName());
        Log::info(Reg::root->hasNode("Test") ? "true" : "false");
        Reg::root->delNode("Test");
        Log::info(Reg::root->hasNode("Test") ? "true" : "false");
    }

    void update() override {
        close();
    }

    void tick() override {
        
    }

    void draw() override {
        
    }

    void close() override {
        stopped = true;
    }
};

int main() {
    Game g = Game();

    g.start();
}