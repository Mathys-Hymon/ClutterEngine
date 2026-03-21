project(ClutterEditor)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Editor sources
file(GLOB_RECURSE EDITOR_SOURCES
        "src/*.cpp"
        "src/*.h"     # private headers (ex: WindowsWindow.h)
        "include/*.h" # public headers (ex: Application.h)
)

add_executable(ClutterEditor WIN32 ${EDITOR_SOURCES})

add_custom_command(TARGET ClutterEditor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/EditorContent" # Source
        "$<TARGET_FILE_DIR:ClutterEditor>/EditorContent"  # Destination
)

# Includes
target_include_directories(ClutterEditor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ClutterEditor
        PRIVATE
        ClutterCore
        ImGuiLib
        nfd
)

# Working directory
set_target_properties(ClutterEditor PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" )

if(MINGW)
    target_link_options(ClutterEditor PRIVATE -static -static-libgcc -static-libstdc++)
endif()