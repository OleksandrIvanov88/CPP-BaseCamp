#pragma once
#include <string>

class Log_error
{
public:    
    Log_error(const std::string& error, const std::string ex = "");
    void print_error();
private:
    std::string message;
};