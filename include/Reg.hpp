#pragma once

#include <vector>
#include <string>

namespace Teko {
    class RegNode {
        private:
        std::vector<RegNode*> _children;
        RegNode* _owner;
        std::string _name;
        public:
        void* data;

        RegNode(RegNode* ownerNode, std::string nodeName);
        ~RegNode();

        RegNode* getNode(std::string path);
        void delNode(std::string name);
        RegNode* getOwner();
        std::vector<RegNode*> getChildren();
        RegNode* addNode(std::string name);
        std::string getName();
        bool hasNode(std::string path);
    };

    class Reg {
        public:

        static RegNode* root;

        static void init();
        static void close();
    };
}