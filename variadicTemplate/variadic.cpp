#include <type_traits>
#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <cstddef>
#include "variadic.h"
#include "string.h"

static inline bool isdigit(const char c)
{
    return (c >= '0' && c <= '9');
}

void runtime_assert(bool assertion, const std::string& what)
{
    if(!assertion)
        throw std::runtime_error(what);
}

std::string Sprintf(const std::string& fmt)
{
    std::cerr << "in base final: " << fmt << std::endl;
    std::size_t index = fmt.find('%');
    while(index+1 < fmt.length() && fmt[index+1] == '%')
    {
        index = fmt.find('%', index+2);
    }
    runtime_assert(index == std::string::npos,
                  "extra format specifier in string passed to Sprintf");
    return fmt;
}
#if 0
template<typename T>
std::string Sprintf(const std::string& fmt, const T& t)
{
    std::cerr << "in base intermediate: " << fmt << std::endl;
    std::size_t index = fmt.find('%');
    while(index+1 < fmt.length() && fmt[index+1] == '%')
    {
        index = fmt.find('%', index+2);
    }
    runtime_assert(index != std::string::npos,
                  "unmatched argument passed to Sprintf");
    std::string ret = fmt.substr(0,index);
    /* ignore padding for now */
    while(++index < fmt.length() && isdigit(fmt[index]));
    runtime_assert(index < fmt.length(),
                  "unmatched argument passed to Sprintf");
    if(fmt.substr(index,2) == "ll")
    {
        index += 2;
        runtime_assert(index < fmt.length(),
                      "unmatched argument passed to Sprintf");
    }
    else if(fmt[index] == 'l')
    {
        index += 1;
        runtime_assert(index < fmt.length(),
                      "unmatched argument passed to Sprintf");
    }
    ret += std::to_string(t);
    return ret +  Sprintf(fmt.substr(index+1));
}
#endif
template<typename T, typename... Us>
std::string Sprintf(const std::string& fmt, const T& t, Us... Args)
{
    std::cerr << "in variadic: " << fmt << std::endl;
    std::size_t index = fmt.find('%');
    while(index+1 < fmt.length() && fmt[index+1] == '%')
    {
        index = fmt.find('%', index+2);
    }
    runtime_assert(index != std::string::npos,
                  "unmatched argument passed to Sprintf");
    std::string ret = fmt.substr(0,index);

    /* ignore padding for now */
    while(++index < fmt.length() && isdigit(fmt[index]));
    runtime_assert(index < fmt.length(),
                  "unmatched argument passed to Sprintf");
    if(fmt.substr(index,2) == "ll")
    {
        index += 2;
        runtime_assert(index < fmt.length(),
                      "unmatched argument passed to Sprintf");
    }
    else if(fmt[index] == 'l')
    {
        index += 1;
        runtime_assert(index < fmt.length(),
                      "unmatched argument passed to Sprintf");
    }
    
    ret += std::to_string(t);
    return ret + Sprintf(fmt.substr(index+1), Args...);
}

template<typename... Us>
const char* cSprintf(const char* fmt, Us... args)
{
    return Sprintf(std::string(fmt), args...).c_str();
}


const char* cSprintf(const char* str)
{
    return Sprintf(std::string(str)).c_str();
}

extern "C" {
int main(void)
{
    //std::string formatted = Sprintf("int %d, flt %f", 9, 25.2);
    //std::cout << formatted << std::endl;
    const char* ret = cSprintf("foobeans: %d %d %f", 1, 2, 3.0);
    printf("%s\n", ret);
    const char* set = cSprintf("bizbars");
    printf("%s\n", set);
    char str[] = "abcdefg";
    std::cout << strfnd(str, 'e',0) << std::endl;
    std::cout << strfnd(str, 'a',0) << std::endl;
    std::cout << strfnd(str, 'g',0) << std::endl;
    std::cout << strfnd(str, 'e',10) << std::endl;
    char rts[10] = {0};
    std::cout << strlen(str) << " " << strlen(rts) << std::endl;
    strcpy(rts, str);
    std::cout << "rts" << rts << " " << str << std::endl;
    std::cout << (!strcmp(str,rts)?"true":"false") << std::endl;

    std::cout << (!strncmp(str,rts, 15)?"true":"false") << std::endl;
    rts[6] = rts[5] = 'Q';

    std::cout << (!strcmp(str,rts)?"true":"false") << std::endl;
    std::cout << (!strncmp(str,rts, 2)?"true":"false") << std::endl;
    std::cout << (!strncmp(str,rts, 4)?"true":"false") << std::endl;
    std::cout << (!strncmp(str,rts, 5)?"true":"false") << std::endl;
    std::cout << (!strncmp(str,rts, 6)?"true":"false") << std::endl;
    std::cout << (!strncmp(str,rts, 7)?"true":"false") << std::endl;
    std::cout << "sizeof(mblock_t)=" << sizeof(mblock_t) << std::endl;
    std::cout << "sizeof(mblock_info_t)=" << sizeof(mblock_info_t) << std::endl;
    std::cout << "offsetof(mblock_t, data)=" << offsetof(mblock_t, data) << std::endl;
    mblock_t mblock;
    std::cout << std::hex << std::setw(16) << "     &mblock=" << &mblock << std::endl;
    std::cout << std::hex << std::setw(16) << "&mblock.prev=" << &mblock.prev << std::endl;
    std::cout << std::hex << std::setw(16) << "&mblock.size=" << &mblock.size << std::endl;
    std::cout << std::hex << std::setw(16) << "&mblock.info=" << &mblock.info << std::endl;
    std::cout << std::hex << std::setw(16) << "&mblock.data=" << &mblock.data << std::endl;
    return 0;
}
}
