project(ClutterCore)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- GLAD ---
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad)
set(GLAD_SOURCES "${GLAD_DIR}/src/glad.c")

if(NOT EXISTS "${GLAD_SOURCES}")
    message(FATAL_ERROR "ERROR : Cant find glad.c : ${GLAD_SOURCES}")
endif()

# --- JSON ---
set(JSON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/json)

# --- SOURCES ---
file(GLOB_RECURSE CORE_SOURCES 
    "src/*.cpp" 
    "src/*.h"       # private headers (ex: WindowsWindow.h)
    "include/*.h"   # public headers (ex: Application.h)
)

# --- CREATING STATIC LIB (.lib) ---

add_library(ClutterCore STATIC
        ${CORE_SOURCES}
        ${GLAD_SOURCES}
)

# --- DEFINITIONS ---
target_compile_definitions(ClutterCore 
	PUBLIC
        	CLUTTER_PLATFORM_WINDOWS
        	CLUTTER_DEBUG

	PRIVATE
        	GLFW_INCLUDE_NONE
        	GLFW_INCLUDE_VULKAN
)

if(MSVC)
	target_compile_options(ClutterCore PUBLIC /W4)
	set_source_files_properties(${GLAD_SOURCES} PROPERTIES COMPILE_FLAGS "/w")
else ()
	target_compile_options(ClutterCore PUBLIC
			-Wall -Wextra -Wpedantic -Wconversion)
	set_source_files_properties(${GLAD_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
endif ()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(ClutterCore PUBLIC CLUTTER_DEBUG)
endif()

# --- INCLUDES ---
target_include_directories(ClutterCore SYSTEM PUBLIC
		${GLAD_DIR}/include
		${JSON_DIR}/
)

target_include_directories(ClutterCore
		PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

# --- LINKS ---
target_link_libraries(ClutterCore
        PUBLIC
        Vulkan::Vulkan
        vk-bootstrap
        glfw
        glm::glm
        spdlog::spdlog
		EnTT::EnTT
        ${CMAKE_DL_LIBS}
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
	target_compile_definitions(ClutterCore PUBLIC CLT_DEBUG)
	message(STATUS "ClutterCore: DEBUG Mode")
else()
	target_compile_definitions(ClutterCore PUBLIC NDEBUG)
	message(STATUS "ClutterCore: RELEASE Mode")
endif()

if(MINGW)
    target_link_options(ClutterCore PRIVATE -static -static-libgcc -static-libstdc++)
endif()