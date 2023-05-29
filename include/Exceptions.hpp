//
// Created by max on 5/9/23.
//

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace Teko {
    class AssetException : public std::exception {
    private:
        std::string _message;
    public:
        std::string file;

        const char* what() const noexcept override;
        AssetException(std::string message);
    };
}

#endif //EXCEPTIONS_HPP
