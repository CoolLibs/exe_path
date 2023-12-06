#include <exe_path/exe_path.h>
#include <filesystem>

// Thanks to https://stackoverflow.com/questions/1528298/get-path-of-executable/60250581#60250581

#if defined(_WIN32)
#include <ShlObj.h>
#include <windows.h>

static auto executable_path_impl() -> std::filesystem::path
{
    char path[MAX_PATH]; // NOLINT(*avoid-c-arrays)
    GetModuleFileNameA(nullptr, path, MAX_PATH);
    return path;
}

static auto user_data_path_impl() -> std::filesystem::path
{
    PWSTR   path   = nullptr;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

    if (!SUCCEEDED(result))
        return "";

    auto const res = std::filesystem::path{path};
    CoTaskMemFree(static_cast<void*>(path));

    return res;
}

#endif

#if defined(__linux__)
#include <limits.h>
#if defined(__sun)
#define PROC_SELF_EXE "/proc/self/path/a.out"
#else
#define PROC_SELF_EXE "/proc/self/exe"
#endif

static auto executable_path_impl() -> std::filesystem::path
{
    char              buffer[PATH_MAX];
    const char* const path = realpath(PROC_SELF_EXE, buffer);
    return path;
}

static auto user_data_path_impl() -> std::filesystem::path
{
    const char* path = std::getenv("HOME");
    if (path == nullptr)
        return "";
    return std::filesystem::path(path) / ".local/share";
}

#endif

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#include <sys/syslimits.h>

static auto executable_path_impl() -> std::filesystem::path
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

static auto user_data_path_impl() -> std::filesystem::path
{
    const char* path = std::getenv("HOME");
    if (path == nullptr)
        return "";
    return path;
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

auto user_data() -> std::filesystem::path const&
{
    static auto const path = std::filesystem::weakly_canonical(user_data_path_impl());
    return path;
}

} // namespace exe_path