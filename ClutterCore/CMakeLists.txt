project(ClutterCore)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CLUTTER_BUILD_3DS "Build for Nintendo 3DS" OFF)

# --- JSON & STB (Universels) ---
set(JSON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/json)
set(STB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/stb)

# --- SOURCES ---
file(GLOB_RECURSE CORE_SOURCES
		"src/*.cpp"
		"src/*.h"
		"include/*.h"
)

# --- CREATING STATIC LIB (.lib / .a) ---
add_library(ClutterCore STATIC ${CORE_SOURCES})

# ==========================================
# 1. SWITCH ON PLATFORMS
# ==========================================

if(CLUTTER_BUILD_3DS)
	message(STATUS "--- CONFIGURING FOR NINTENDO 3DS ---")

	target_compile_definitions(ClutterCore PUBLIC CLUTTER_PLATFORM_3DS CLUTTER_DEBUG)


else()
	message(STATUS "--- CONFIGURING FOR WINDOWS ---")

	target_compile_definitions(ClutterCore
			PUBLIC
			CLUTTER_PLATFORM_WINDOWS
			CLUTTER_DEBUG

			PRIVATE
			GLFW_INCLUDE_NONE
	)

	set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/glad)
	set(GLAD_SOURCES "${GLAD_DIR}/src/glad.c")
	target_sources(ClutterCore PRIVATE ${GLAD_SOURCES})
	target_include_directories(ClutterCore SYSTEM PUBLIC ${GLAD_DIR}/include)

	if(MSVC)
		set_source_files_properties(${GLAD_SOURCES} PROPERTIES COMPILE_FLAGS "/w")
	else ()
		set_source_files_properties(${GLAD_SOURCES} PROPERTIES COMPILE_FLAGS "-w")
	endif ()

	target_link_libraries(ClutterCore PUBLIC glfw ${CMAKE_DL_LIBS})
endif()

# ==========================================
# 2. GLOBAL CONFIGURATION
# ==========================================

if(MSVC)
	target_compile_options(ClutterCore PUBLIC /W4)
else ()
	target_compile_options(ClutterCore PUBLIC -Wall -Wextra -Wpedantic -Wconversion)
endif ()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	target_compile_definitions(ClutterCore PUBLIC CLUTTER_DEBUG CLT_DEBUG)
	message(STATUS "ClutterCore: DEBUG Mode")
else()
	target_compile_definitions(ClutterCore PUBLIC NDEBUG)
	message(STATUS "ClutterCore: RELEASE Mode")
endif()


target_include_directories(ClutterCore SYSTEM PUBLIC
		${JSON_DIR}/
		${STB_DIR}/
)

target_include_directories(ClutterCore
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include

		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(ClutterCore
		PUBLIC
		glm::glm
		spdlog::spdlog
		EnTT::EnTT
)

if(MINGW)
	target_link_options(ClutterCore PRIVATE -static -static-libgcc -static-libstdc++)
endif()