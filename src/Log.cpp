#include "Log.hpp"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>

namespace Teko {
    std::ofstream *Log::_file;

    void Log::init() {    
        time_t time;
        std::time(&time);

        std::ostringstream fileNameString;
        fileNameString << std::put_time(std::localtime(&time), "logs/%d.%m.%Y.log");
        _file = new std::ofstream();
        _file->open(fileNameString.str(), std::ios_base::app);
        
        (*_file) << "=== START LOG ===" << std::endl;
        info("Logs init.");
    }

    void Log::close() {
        warn("Logs closing");
        (*_file) << "=== END LOG ===" << std::endl << std::endl;
        _file->close();
        delete _file;
    }


    void Log::log(std::string type, std::string message) {
        time_t time;
        std::time(&time);

        (*_file) << std::put_time(std::localtime(&time), "(%H:%M:%S)");
        (*_file) << "[" << type << "] " << message << std::endl;
    }

    void Log::info(std::string message) {log("INFO", message);}
    void Log::warn(std::string message) {log("WARN", message);}
    void Log::erro(std::string message) {log("ERRO", message);}
}