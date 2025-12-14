#pragma once

#include <memory>

// Détection de plateforme
#ifdef _WIN32
    /* Windows x64/x86 */
    #ifdef _WIN64
        #define CLUTTER_PLATFORM_WINDOWS
    #else
        #error "x86 Builds are not supported!"
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #error "Apple is not supported!"
#elif defined(__linux__)
    #define CLUTTER_PLATFORM_LINUX
#else
    #error "Unknown platform!"
#endif
