#pragma once

#include <filesystem>

namespace exe_path {

std::filesystem::path executable_path();
std::filesystem::path executable_directory();

} // namespace exe_path