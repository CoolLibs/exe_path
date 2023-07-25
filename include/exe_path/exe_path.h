#pragma once

#include <filesystem>

namespace exe_path {

/// Returns the absolute path to your program's executable
auto exe() -> std::filesystem::path const&;
/// Returns the absolute path to the directory containing your program's executable
auto dir() -> std::filesystem::path const&;
/// Returns the absolute path to the user data directory. (e.g. AppData/Roaming on Windows)
auto user_data() -> std::filesystem::path const&;

} // namespace exe_path