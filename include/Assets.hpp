#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <string>
#include <vector>
#include <functional>
#include <map>
#include <tinyxml2.h>

#include "Reg.hpp"

namespace Teko {
    struct AssetData {
        std::vector<AssetData *> children;
        std::string name;
        AssetData* owner;
        void* value;

        ~AssetData();
    };

    class Assets {
        private:

        public:
        static std::map<std::string, std::function<void(AssetData*, tinyxml2::XMLElement*)>> types;
        static void init();
        static void close();

        static void loadAsset(std::string path);
        static AssetData* loadFile(std::string path, AssetData* owner);
    };
}

#endif
