# exe_path

A small cross-platform library to retrieve the path to the directory where your executable is located.

This is very useful to load assets that are located in the same directory as your executable.

## Including

To add this library to your project, simply add those two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/exe_path)
target_link_libraries(${PROJECT_NAME} PRIVATE exe_path::exe_path)
```

Then include it as:
```cpp
#include <exe_path/exe_path.hpp>
```

## Example

```cpp
#include <exe_path/exe_path.h>

int main()
{
    const std::filesystem::path path_to_my_image 
        = exe_path::dir() / "assets/images/my_img.png";
    // Then load the image...
}
```

## Installing

Simply copy the library to your project and include it with CMake:
```cmake title="CMakeLists.txt"
# CMakeLists.txt
add_subdirectory(my_libs/exe_path)
target_link_libraries(${PROJECT_NAME} PRIVATE exe_path::exe_path)
```

## Automatically copying assets to your executable's directory

Consider using [CMakeUtils](https://github.com/CoolLibs/CMakeUtils).

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.