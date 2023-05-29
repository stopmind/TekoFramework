#include <fstream>
#include <algorithm>

#include "Assets.hpp"
#include "Log.hpp"
#include "Reg.hpp"
#include "Exceptions.hpp"
#include "AssetFuncs.hpp"

namespace Teko {
    std::map<std::string, std::function<void(AssetData*, tinyxml2::XMLElement*)>> Assets::types;

    AssetData::~AssetData() {
        Log::info("Delete asset data.");

        for (auto &child : children) {
            delete child;
        }
    }

    void Assets::init() {
        types = {
                {"copy", AssetFuncs::copyFunction},
                {"from_file", AssetFuncs::fromFileFunction},
                {"texture", AssetFuncs::textureFunction},
                {"vec2", AssetFuncs::vec2},
        };

        Log::info("Asset init.");
    }

    void Assets::close() {

    }

    void Assets::loadAsset(std::string path) {
        if (path[path.size()-1] != '/') path += "/";

        AssetData pathData = {
            .children = {},
            .name = "",
            .owner = nullptr,
            .value = &path,
        };

        loadFile(path + "AssetInfo.xml", &pathData);
    }

    AssetData *Assets::loadFile(std::string path, AssetData *owner) {
        using namespace tinyxml2;

        XMLDocument file;
        file.LoadFile(path.c_str());

        AssetData *currentData = new AssetData {
            .children = {},
            .owner = owner,
            .value = nullptr,
        };
        owner->children.push_back(currentData);

        std::vector<XMLElement *> elements = {file.RootElement()};
        int currentIndex = 0;

        while (currentIndex > -1) {
            std::string name = elements[currentIndex]->Name();

            if (elements[currentIndex]->Attribute("name") == nullptr) throw AssetException("No find name.");
            currentData->name = std::string(elements[currentIndex]->Attribute("name"));
            if (name == "value") {
                types[std::string(elements[currentIndex]->Attribute("type"))](currentData, elements[currentIndex]);
                currentData = currentData->owner;
                currentIndex--;
            } else if (name == "data") {
                if (elements[currentIndex]->NoChildren()) {
                    currentData = currentData->owner;
                    currentIndex--;
                    continue;
                }

                if (currentIndex + 1 < elements.size() && elements[currentIndex + 1]->Parent() == elements[currentIndex]) {
                    if (elements[currentIndex + 1] == elements[currentIndex]->LastChildElement()) {
                        if (elements[currentIndex]->Attribute("to") != nullptr) {
                            auto to = std::string(elements[currentIndex]->Attribute("to"));
                            for (auto child : currentData->children) {
                                Reg::root->getNode(to)->addNode(child->name)->data = child->value;
                            }
                        }

                        currentData = currentData->owner;
                        currentIndex--;
                        continue;
                    } else {
                        elements[currentIndex + 1]++;
                    }
                } else {
                    elements.push_back(elements[currentIndex]->FirstChildElement());
                }

                auto newData = new AssetData {
                    .children = {},
                    .owner = currentData,
                    .value = nullptr,
                };
                currentData->children.push_back(newData);
                currentData = newData;
                currentIndex++;

            } else throw AssetException("Unknown element name.");
        }

        return nullptr;
    }
}
