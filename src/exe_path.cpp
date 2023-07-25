#include <exe_path/exe_path.h>
#include <filesystem>

// Thanks to https://stackoverflow.com/questions/1528298/get-path-of-executable/60250581#60250581

#if defined(_WIN32)
#include <windows.h>
static std::filesystem::path executable_path_impl()
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return path;
}
#endif

#if defined(__linux__)
#include <limits.h>
#if defined(__sun)
#define PROC_SELF_EXE "/proc/self/path/a.out"
#else
#define PROC_SELF_EXE "/proc/self/exe"
#endif
static std::filesystem::path executable_path_impl()
{
    char              buffer[PATH_MAX];
    const char* const path = realpath(PROC_SELF_EXE, buffer);
    return path;
}
#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#include <sys/syslimits.h>
static std::filesystem::path executable_path_impl()
{
    char raw_path_name[PATH_MAX];
    char real_path_name[PATH_MAX];
    auto raw_path_size = static_cast<uint32_t>(sizeof(raw_path_name));
    if (!_NSGetExecutablePath(raw_path_name, &raw_path_size))
    {
        realpath(raw_path_name, real_path_name);
    }
    return real_path_name;
}
#endif

namespace exe_path {

auto exe() -> std::filesystem::path const&
{
    static auto const path = std::filesystem::weakly_canonical(executable_path_impl());
    return path;
}

auto dir() -> std::filesystem::path const&
{
    static auto const path = exe().parent_path();
    return path;
}

} // namespace exe_path