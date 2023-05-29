//
// Created by max on 5/21/23.
//

#include "TestComponent.hpp"
#include "Reg.hpp"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

void TestComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*sprite, states);
}

void TestComponent::setData(std::map<std::string, void *> data) {
    sprite = new sf::Sprite();
    sprite->setTexture(*(sf::Texture*)Teko::Reg::root->getNode("Textures::Agent")->data);
    sprite->setScale(2, 2);
}

void TestComponent::tick() {
    std::cout << "Tick!" << std::endl;
}

void TestComponent::update(float delta) {

}
