#include <exe_path/exe_path.h>

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
    char path[PATH_MAX];
    (void)realpath(PROC_SELF_EXE, path); // Cast to void to avoid warning of unused variable
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

std::filesystem::path exe()
{
    static const auto path = executable_path_impl();
    return path;
}

std::filesystem::path dir()
{
    static const auto path = exe()
                                 .parent_path();
    return path;
}

} // namespace exe_path