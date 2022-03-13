#include <exe_path/exe_path.h>
#include <iostream>

int main()
{
    std::cout << exe_path::executable_path() << '\n';
    std::cout << exe_path::executable_directory() << '\n';
    std::cin.get();
}