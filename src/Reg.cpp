#include "Reg.hpp"
#include "Log.hpp"

namespace Teko {
    RegNode* RegNode::getNode(std::string path) {
        int firstDelimitrPos = path.find_first_of("::");
        
        std::string name = path.substr(0, firstDelimitrPos);

        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getName() != name) continue;
            if (firstDelimitrPos == -1) return children[i];
            else return children[i]->getNode(path.substr(firstDelimitrPos+2));
        }

        return nullptr;
    }

    bool RegNode::hasNode(std::string path) {
        return getNode(path) != nullptr;
    }

    void RegNode::delNode(std::string name) {
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->getName() != name) continue;
            
            delete children[i];
            children.erase(children.begin() + i);
            return;
        }
    }

    RegNode* RegNode::getOwner() {
        return owner;
    }

    std::vector<RegNode*> RegNode::getChildren() {
        return children;
    }

    RegNode* RegNode::addNode(std::string name) {
        RegNode* newNode = new RegNode(this, name);

        children.push_back(newNode);
        return newNode;
    }

    std::string RegNode::getName() {
        return name;
    }
    
    RegNode::RegNode(RegNode* ownerNode, std::string nodeName) {
        children = std::vector<RegNode*>();
        owner = ownerNode;
        name = nodeName;
    }

    RegNode::~RegNode() {
        for (int i = 0; i < children.size(); i++) {
            delete children[i];
        }
    }

    RegNode *Reg::root;

    void Reg::init() {
        root = new RegNode(nullptr, "root");
        root->addNode("Textures");
        root->addNode("EntitiesTypes");
        Log::info("Registry init.");
    }

    void Reg::close() {
        delete root;
        Log::warn("Registry closed.");
    }
}