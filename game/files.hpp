#include <string>

#ifndef __KAI__TOTM__FILES__
#define __KAI__TOTM__FILES__ 1

std::string getName(const char* fn_c_str);
std::string getName(std::string fn);
std::string getExtension(const char* fn_c_str);
std::string getExtension(std::string fn);

#endif