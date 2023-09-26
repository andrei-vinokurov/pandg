cmake_minimum_required(VERSION 3.20.0)
project(ListOP VERSION 0.1.0)

set(wxWidgets_ROOT_DIR "C:/wxwidgets")
set(wxWidgets_LIB_DIR "C:/wxwidgets/lib/gcc810_x64_dll")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

file(GLOB project_GLOB
    *
)

add_executable(ListOP ${project_GLOB})

target_link_libraries(ListOP ${wxWidgets_LIBRARIES})

target_include_directories(ListOP PRIVATE ${wxWidgets_INCLUDE_DIRS})
