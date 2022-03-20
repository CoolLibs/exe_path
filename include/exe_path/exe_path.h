#pragma once

#include <filesystem>

namespace exe_path {

/// Returns the absolute path to your program's executable
std::filesystem::path exe();
/// Returns the absolute path to the directory containing your program's executable
std::filesystem::path dir();

} // namespace exe_path