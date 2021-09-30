#include "weather_error.hpp"
#include <iostream>


Log_error::Log_error(const std::string& error, const std::string ex) : 
                    message(error + ex){}
                    
void Log_error::print_error()
{ 
#ifdef DEBUG_ERROR     
    std::cerr << "****Error!!!" << this->message<< "****" << std::endl;
#endif
}

