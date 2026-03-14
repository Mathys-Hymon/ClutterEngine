project(ClutterEditor)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Editor sources
file(GLOB_RECURSE EDITOR_SOURCES
        "src/*.cpp"
        "src/*.h"     # private headers (ex: WindowsWindow.h)
        "include/*.h" # public headers (ex: Application.h)
)

add_executable(ClutterEditor ${EDITOR_SOURCES})

# Includes
target_include_directories(ClutterEditor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ClutterEditor
        PRIVATE
        ClutterCore
        ImGuiLib
)

# Working directory
set_target_properties(ClutterEditor PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

if(MINGW)
    target_link_options(ClutterEditor PRIVATE -static -static-libgcc -static-libstdc++)
endif()