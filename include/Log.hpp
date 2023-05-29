#pragma once

#include <string>
#include <fstream>

namespace Teko {
    class Log {
        private:
        static std::ofstream *_file;

        static void log(std::string type, std::string message);

        public:
        static void init();
        static void close();

        static void info(std::string message);
        static void warn(std::string message);
        static void erro(std::string message);
    };
}
