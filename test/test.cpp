#include <exe_path/exe_path.h>
#include <iostream>

int main()
{
    std::cout << exe_path::exe() << '\n';
    std::cout << exe_path::dir() << '\n';
    std::cin.get();
}