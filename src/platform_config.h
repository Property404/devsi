#pragma once
#ifdef __APPLE__
/* macOS specific */
#define DEVSI_MACOS
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>
#elif _WIN32
#define DEVSI_WINDOWS
#elif __unix__
#define DEVSI_X11
#endif
