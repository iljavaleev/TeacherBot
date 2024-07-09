#ifndef vocabular_hpp
#define vocabular_hpp
#include <vector>
#include <string>

#define RU

#ifdef RU
const static std::vector<std::string> MONTHS_RU = {
    "Январь", 
    "Февраль", 
    "Март", 
    "Апрель", 
    "Май", 
    "Июнь", 
    "Июль", 
    "Август", 
    "Сентябрь", 
    "Октябрь", 
    "Ноябрь", 
    "Декабрь"
};
#elif EN
const static std::vector<std::string> MONTHS_EN = {
    "January", 
    "February", 
    "March", 
    "April", 
    "May", 
    "June", 
    "July", 
    "August", 
    "September", 
    "October", 
    "November", 
    "December"
};
#endif

#endif
