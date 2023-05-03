#include "Assets.hpp"
#include "Log.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Reg.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace Teko {
    RegNode *Assets::assetsNode;

    AssetData* Assets::value(std::string* text, int* index, AssetData* owner) {
        std::string stringVal;
        std::string functionName;
        std::string integerStringVal;

        bool integerStarted = false;
        bool stringStarted = false;
        bool functionStarted = false;

        while (true) {
            if (functionStarted) {
                if ((*text)[*index] == '.') {
                    (*index)++;
                    auto subValue = value(text, index, owner);
                    functions(functionName, subValue);

                    return subValue;
                } else {
                    functionName += (*text)[*index];
                    (*index)++;
                    continue;
                }
            }

            //integer :/
            if (integerStarted) {
                switch ((*text)[*index]) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        integerStringVal += (*text)[*index];
                        (*index)++;
                        continue;

                    default:
                        return new AssetData {owner, {}, "", std::stoi(integerStringVal)};
                }
            }

            // string
            if (stringStarted) {
                if ((*index) >= text->size()) {
                    Log::erro("String not closed");
                    exit(1);
                }

                if ((*text)[*index] == '"') {
                    (*index)++;
                    return new AssetData {owner, {}, stringVal};
                } else {
                    stringVal += (*text)[*index];
                    (*index)++;
                    continue;
                }
            }

            // find start
            switch ((*text)[*index]) {
                case '"':
                    (*index)++;
                    stringStarted = true;
                    break;
                case '{':
                    (*index)++;
                    return code(text, index, owner);

                    // integer :/
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    integerStarted = true;
                    break;

                default:
                    functionStarted = true;
            }
        }
    }

    AssetData* Assets::code(std::string* text, int* index, AssetData* owner) {
        auto* result = new AssetData {owner, std::map<std::string, AssetData*>()};
        std::string key = std::string();

        while (true) {
            switch ((*text)[*index]) {
                case '}':
                    if (!key.empty()) {
                        Log::erro("Expected \":\".");
                        exit(1);
                    }
                    return result;
                case ':':
                    if (key.empty()) {
                        Log::erro("Not found key.");
                        exit(1);
                    }

                    (*index)++;
                    result->object[key] = value(text, index, result);
                    key = "";
                    break;
                default:
                    key += (*text)[*index];
                    (*index)++;
            }

            if ((*index) >= text->size()) {
                Log::erro("Code not finished.");
                exit(1);
            }
        }
    }

    void Assets::init() {
        assetsNode = Reg::root->addNode("Assets");
        Log::info("Asset init.");
    }

    void Assets::close() {
        Reg::root->delNode("Assets");
        Log::warn("Asset closed!");
    }


    void Assets::loadAsset(std::string path) {
        if (path[path.size()-1] != '/') path += "/";
        std::string infoPath = path;
        infoPath += "AssetInfo.dat";

        loadFile(infoPath, new AssetData{
                nullptr, {}, path, 0, nullptr,
        });
    }

    void Assets::functions(std::string name, AssetData *data) {
        if (name == "copy") {
            RegNode *node = Reg::root->getNode(data->object["To"]->stringValue);

            delete data->object["To"];
            data->object.erase("To");

            for (auto &pair: data->object)
                if (pair.second->resource != nullptr)
                    node->addNode(pair.first)->data = pair.second->resource;

        } else if (name == "from_file") {
            AssetData *assetPathValue = data;
            while (assetPathValue->owner != nullptr) assetPathValue = assetPathValue->owner;

            auto file = loadFile(assetPathValue->stringValue + data->stringValue, data->owner);
            (*data) = *file;
            delete file;
        } else if (name == "texture") {
            AssetData *assetPathValue = data;
            while (assetPathValue->owner != nullptr) assetPathValue = assetPathValue->owner;

            sf::Texture* texture = new sf::Texture();
            texture->loadFromFile(assetPathValue->stringValue + data->stringValue);
            data->resource = texture;
            data->stringValue = "";
        } else {
            Log::erro("Not found function " + name);
            exit(1);
        }

    }

    AssetData *Assets::loadFile(std::string path, AssetData* owner) {
        std::ifstream infoFile = std::ifstream();
        infoFile.open(path);

        if (!infoFile.is_open()) {
            Log::erro("Can't load file \"" + path + "\".");
            exit(1);
        }

        std::string infoData;

        while (!infoFile.eof()) {
            std::string line;
            infoFile >> line;
            infoData += line;
        }

        int index = 0;
        auto* data = value(&infoData, &index, owner);
        return data;
    }
}
