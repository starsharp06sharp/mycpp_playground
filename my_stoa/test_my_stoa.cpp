#include "my_stoa.h"
#include <iostream>

int main()
{
    std::string str;
    std::getline(std::cin, str);

    bool ok = true;
    std::cout << "my_stoi:" << my_stoi(str, &ok) << ", ok:" << ok << std::endl;
    std::cout << "my_stol:" << my_stol(str, &ok) << ", ok:" << ok << std::endl;
    std::cout << "my_stoll:" << my_stoll(str, &ok) << ", ok:" << ok << std::endl;

    std::cout << "my_stoul:" << my_stoul(str, &ok) << ", ok:" << ok << std::endl;
    std::cout << "my_stoull:" << my_stoull(str, &ok) << ", ok:" << ok << std::endl;
    return 0;
}