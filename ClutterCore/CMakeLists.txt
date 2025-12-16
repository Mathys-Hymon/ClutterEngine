project(ClutterCore)

# --- GLAD ---
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad)
set(GLAD_SOURCES "${GLAD_DIR}/src/glad.c")

if(NOT EXISTS "${GLAD_SOURCES}")
    message(FATAL_ERROR "Erreur: glad.c introuvable ici: ${GLAD_SOURCES}")
endif()

# --- SOURCES ---
file(GLOB_RECURSE CORE_SOURCES 
    "src/*.cpp" 
    "src/*.h"       # Headers privés (ex: WindowsWindow.h)
    "include/*.h"   # Headers publics (ex: Application.h)
)

# --- CREATION LIB STATIQUE (.lib) ---
# C'est ici que ça se joue : STATIC au lieu de SHARED
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

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(ClutterCore PUBLIC CLUTTER_DEBUG)
endif()

# --- INCLUDES ---
target_include_directories(ClutterCore
        PUBLIC
        ${GLAD_DIR}/include
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
        ${CMAKE_DL_LIBS}
)

if(MINGW)
    target_link_options(ClutterCore PRIVATE -static -static-libgcc -static-libstdc++)
endif()