cmake_minimum_required(VERSION 3.28)
project(ClutterEngine)

# --- Set C++ standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Output directories ---
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# --- Options ---
option(BUILD_CLUTTER_EDITOR "Build the ImGui Editor Toolchain" ON)

# --- Dependencies ---
#find_package(Vulkan REQUIRED)
include(FetchContent)

# --- Options GLFW ---
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# 1. GLFW
message(STATUS "Fetching glfw...")
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.8)
FetchContent_MakeAvailable(glfw)

# 2. Vulkan Bootstrap
#message(STATUS "Fetching Vulkan Bootstrap...")
#FetchContent_Declare(vk-bootstrap GIT_REPOSITORY https://github.com/charles-lunarg/vk-bootstrap.git GIT_TAG v1.4.334)
#FetchContent_MakeAvailable(vk-bootstrap)

# 3. GLM
message(STATUS "Fetching glm...")
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.2)
FetchContent_MakeAvailable(glm)

# 4. SpdLog
message(STATUS "Fetching spdlog...")
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.12.0)
FetchContent_MakeAvailable(spdlog)

# 5. EnTT
message(STATUS "Fetching EnTT...")
FetchContent_Declare(entt GIT_REPOSITORY https://github.com/skypjack/entt.git GIT_TAG v3.16.0)
FetchContent_MakeAvailable(entt)

# --- Check Editor ---
if(BUILD_CLUTTER_EDITOR)
    message(STATUS "Clutter Engine is in editor mode")

    # 6. Nfd
    message(STATUS "Fetching Nfd...")
    FetchContent_Declare(nfd GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git GIT_TAG v1.2.1)
    FetchContent_MakeAvailable(nfd)

    # 7. ImGui
    message(STATUS "Fetching ImGui...")
    FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG docking)
    FetchContent_MakeAvailable(imgui)

    # --- DEFINE IMGUI LIBRARY (Editor only) ---
    set(IMGUI_DIR ${imgui_SOURCE_DIR})
    file(GLOB IMGUI_SOURCES
            "${IMGUI_DIR}/*.cpp"
            "${IMGUI_DIR}/*.h"
            "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
            #"${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp"
            "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
    )

    add_library(ImGuiLib STATIC ${IMGUI_SOURCES})

    target_include_directories(ImGuiLib PUBLIC
            ${IMGUI_DIR}
            ${IMGUI_DIR}/backends
    )

    target_link_libraries(ImGuiLib PRIVATE glfw)
    add_subdirectory(ClutterEditor)

    endif()

# --- Subdirectories ---
add_subdirectory(ClutterCore)