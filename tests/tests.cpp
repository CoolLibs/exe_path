#include <exe_path/exe_path.h>
#include <cassert>
#include <iostream>

auto main() -> int
{
#ifdef _WIN32
    std::cout << "Windows" << std::endl;
#endif

#ifdef __linux__
    std::cout << "Linux" << std::endl;
#endif

#ifdef __APPLE__
    std::cout << "macOS" << std::endl;
#endif
#ifdef _MSC_VER
    std::cout << "MSVC" << std::endl;
#endif

#ifdef __GNUC__
    std::cout << "GCC" << std::endl;
#endif

#ifdef __clang__
    std::cout << "Clang" << std::endl;
#endif
#ifndef NDEBUG
    std::cout << "Debug" << std::endl;
#else
    std::cout << "Release" << std::endl;
#endif

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