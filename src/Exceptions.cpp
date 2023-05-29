//
// Created by max on 5/9/23.
//

#include "Exceptions.hpp"

namespace Teko {

    const char *AssetException::what() const noexcept {
        std::string *fullMessage = new std::string(_message + " In _file" + file);
        return fullMessage->c_str();
    }

    AssetException::AssetException(std::string message) : _message(message) {}
}