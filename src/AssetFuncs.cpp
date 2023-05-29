//
// Created by max on 5/13/23.
//

#include "Assets.hpp"
#include "AssetFuncs.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace Teko::AssetFuncs {
    void copyFunction(AssetData *data, tinyxml2::XMLElement* element) {

    }

    void fromFileFunction(AssetData *data, tinyxml2::XMLElement* element) {

    }

    void textureFunction(AssetData *data, tinyxml2::XMLElement* element) {
        auto pathData = data;
        while (pathData->owner != nullptr)
            pathData = pathData->owner;

        sf::Texture* tex = new sf::Texture();
        tex->loadFromFile(*(std::string*)pathData->value + std::string(element->Attribute("path")));

        data->value = tex;
    }

    void vec2(AssetData *data, tinyxml2::XMLElement* element) {

    }
}