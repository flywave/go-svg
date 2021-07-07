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

typedef struct _svg_context_t svg_context_t;
typedef struct _svg_render_buf_t svg_render_buf_t;

FLYWAVE_SVG_API svg_context_t *svg_context_create(_Bool flip_y);
FLYWAVE_SVG_API void svg_context_free(svg_context_t *ctx);
FLYWAVE_SVG_API void svg_context_draw(svg_context_t *ctx,
                                      svg_render_buf_t *buf);
FLYWAVE_SVG_API void svg_context_reset(svg_context_t *ctx);
FLYWAVE_SVG_API void svg_context_parse(svg_context_t *ctx, char *fname);
FLYWAVE_SVG_API int svg_context_resize(svg_context_t *ctx, unsigned sx,
                                       unsigned sy);
FLYWAVE_SVG_API void svg_context_get_size(svg_context_t *ctx, unsigned *sx,
                                          unsigned *sy, int *stride);
FLYWAVE_SVG_API void svg_context_clear(svg_context_t *ctx, uint8_t r, uint8_t g,
                                       uint8_t b, uint8_t a);

FLYWAVE_SVG_API svg_render_buf_t *
svg_render_buf_create_empty(svg_context_t *ctx);
FLYWAVE_SVG_API svg_render_buf_t *svg_render_buf_create(uint8_t *buf,
                                                        unsigned width,
                                                        unsigned height,
                                                        int stride);
FLYWAVE_SVG_API void svg_render_buf_free(svg_render_buf_t *ctx);
FLYWAVE_SVG_API void svg_render_buf_attach(svg_render_buf_t *ctx, uint8_t *buf,
                                           unsigned width, unsigned height,
                                           int stride);
FLYWAVE_SVG_API void svg_render_buf_get_size(svg_render_buf_t *ctx,
                                             unsigned *width, unsigned *height,
                                             int *stride);
FLYWAVE_SVG_API void svg_render_buf_clear(svg_render_buf_t *ctx, uint8_t v);
FLYWAVE_SVG_API void svg_render_buf_copy_from(svg_render_buf_t *ctx,
                                              svg_render_buf_t *src);

#ifdef __cplusplus
}
#endif
