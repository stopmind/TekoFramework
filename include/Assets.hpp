#pragma once

#include <string>
#include <map>
#include "Reg.hpp"

namespace Teko {
    struct AssetData {
        AssetData* owner;
        std::map<std::string, AssetData*> object;
        std::string stringValue;
        int integerValue;
        void* resource;
    };

    class Assets {
        private:
        static RegNode *assetsNode;

        static AssetData* loadFile(std::string path, AssetData* owner);
        static void functions(std::string name, AssetData* data);
        static AssetData* value(std::string* text, int* index, AssetData* owner);
        static AssetData* code(std::string* text, int* index, AssetData* owner);

        public:
        static void init();
        static void close();

        static void loadAsset(std::string path);
    };
}
