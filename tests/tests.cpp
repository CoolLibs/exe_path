#include <exe_path/exe_path.h>
#include <cassert>
#include <iostream>

auto main() -> int
{
    {
        std::filesystem::path const& path = exe_path::exe();
        assert(!path.empty());
        std::cout << "Exe       " << path << '\n';
    }
    {
        std::filesystem::path const& path = exe_path::dir();
        assert(!path.empty());
        std::cout << "Exe dir   " << path << '\n';
    }
    {
        std::filesystem::path const& path = exe_path::user_data();
        assert(!path.empty());
        std::cout << "User data " << path << '\n';
    }
}