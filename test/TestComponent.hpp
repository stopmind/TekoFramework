//
// Created by max on 5/21/23.
//

#ifndef TESTCOMPONENT_HPP
#define TESTCOMPONENT_HPP

#include "World/EntityComponent.hpp"

#include <SFML/Graphics/Sprite.hpp>

class TestComponent : public Teko::EntityComponent {
private:
    sf::Sprite *sprite;
public:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void setData(std::map<std::string, void *> data) override;
    void tick() override;
    void update(float delta) override;
};


#endif //TESTCOMPONENT_HPP
