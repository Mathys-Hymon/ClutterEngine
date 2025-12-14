project(ClutterEditor)

# Sources de l'éditeur
file(GLOB_RECURSE EDITOR_SOURCES "src/*.cpp" "src/*.h")

add_executable(ClutterEditor ${EDITOR_SOURCES})

# Includes
target_include_directories(ClutterEditor PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Links : Editor a besoin du Core pour le moteur, et d'ImGui pour l'UI
# Note : ImGuiLib est défini dans le CMakeLists.txt racine
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