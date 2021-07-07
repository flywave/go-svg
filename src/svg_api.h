#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(WINDOWS) || defined(_WIN32) || defined(_WINDOWS)
#define FLYWAVE_SVG_API __declspec(dllexport)
#else
#define FLYWAVE_SVG_API
#endif

#ifdef __cplusplus
}
#endif
