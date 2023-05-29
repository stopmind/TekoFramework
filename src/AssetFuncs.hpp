//
// Created by max on 5/13/23.
//

#include "Assets.hpp"

#ifndef ASSETFUNCS_HPP
#define ASSETFUNCS_HPP

namespace Teko::AssetFuncs {
    void copyFunction(AssetData* data, tinyxml2::XMLElement* element);
    void fromFileFunction(AssetData* data, tinyxml2::XMLElement* element);
    void textureFunction(AssetData* data, tinyxml2::XMLElement* element);
    void vec2(AssetData* data, tinyxml2::XMLElement* element);
}

#endif //ASSETFUNCS_HPP

