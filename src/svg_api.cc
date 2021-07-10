#include "svg_api.h"

#include "agg_scanline_p.h"
#include "agg_svg_attributes_map.h"
#include "agg_svg_exception.h"
#include "agg_svg_indexation_interpreter.h"
#include "agg_svg_parser.h"
#include "agg_svg_rasterizer.h"
#include "agg_svg_rendering_interpreter.h"
#include "ctrl/agg_slider_ctrl.h"
#include "platform/agg_platform_support.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <stdint.h>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

enum { flip_y_e = false };

struct _svg_context_t {
  agg::svg::dom_storage storage;
  agg::svg::dom_storage::map_type id2elem_map;
  agg::svg::attributes_map attr_map;
  agg::svg::global_settings settings;
  std::unique_ptr<agg::svg::attributes> attributes;
  agg::svg::frame_buffer_rgba frame_buffer;
  agg::svg::rasterizer rasterizer;
  std::unique_ptr<agg::svg::renderer_rgba> renderer;
  agg::svg::pipeline pipeline;
  agg::svg::gradient_lut_cache gradient_lut_cache;
  std::unique_ptr<agg::slider_ctrl<agg::rgba8>> gamma;
  std::string error;
};

struct _svg_render_buf_t {
  agg::rendering_buffer rbuf;
};

FLYWAVE_SVG_API struct _svg_context_t *svg_context_create(_Bool flip_y) {
  _svg_context_t *ctx = new _svg_context_t;
  ctx->attributes = std::make_unique<agg::svg::attributes>(ctx->settings);
  ctx->renderer = std::make_unique<agg::svg::renderer_rgba>(ctx->rasterizer,
                                                            ctx->frame_buffer);
  ctx->gamma = std::make_unique<agg::slider_ctrl<agg::rgba8>>(5, 5, 256 - 5, 20,
                                                              !flip_y);

  ctx->gamma->label("Gamma=%3.2f");
  ctx->gamma->range(0.0, 3.0);
  ctx->gamma->value(1.0);

  return ctx;
}

FLYWAVE_SVG_API void svg_context_free(svg_context_t *ctx) {
  if (ctx != nullptr) {
    delete ctx;
  }
}

FLYWAVE_SVG_API void svg_context_clear(svg_context_t *ctx, uint8_t r, uint8_t g,
                                       uint8_t b, uint8_t a) {
  ctx->frame_buffer.clear(agg::svg::color_type(r, g, b, a));
}

FLYWAVE_SVG_API void svg_context_draw(svg_context_t *ctx,
                                      svg_render_buf_t *buf) {
  agg::svg::renderer_rgba::pixfmt_type pixfmt(buf->rbuf);
  agg::svg::renderer_rgba::renderer_base_type rbase(pixfmt);

  double gamma = ctx->gamma->value();

  ctx->rasterizer.gamma(gamma);
  ctx->settings.gamma(gamma);

  ctx->attributes->window(0, 0, buf->rbuf.width(), buf->rbuf.height());

  ctx->renderer->attach(ctx->frame_buffer);

  agg::svg::rendering_interpreter rin(ctx->pipeline, *ctx->attributes,
                                      *ctx->renderer, ctx->id2elem_map,
                                      ctx->gradient_lut_cache);

  ctx->storage.traverse(rin);

  assert(0 == ctx->attributes->num_sessions());

  if (ctx->frame_buffer.is_valid()) {
    rbase.copy_from(ctx->frame_buffer.ren_buf());
  }
}

FLYWAVE_SVG_API void svg_context_reset(svg_context_t *ctx) {
  ctx->id2elem_map.clear();
  ctx->attributes->clear();
  ctx->renderer->reset();
}

void _indexation(svg_context_t *ctx) {
  agg::svg::indexation_interpreter consumer(ctx->id2elem_map);

  ctx->storage.traverse(consumer);

  ctx->id2elem_map.sort_state(agg::svg::on);
}

FLYWAVE_SVG_API void svg_context_parse(svg_context_t *ctx, char *fname) {
  if (!fname)
    return;

  ctx->attributes->initial_zoom();
  ctx->storage.clear();
  svg_context_reset(ctx);

  agg::svg::parser p(ctx->storage, ctx->attr_map);
  try {
    p.parse(fname);
  } catch (std::exception ex) {
    ctx->error = ex.what();
  }
  _indexation(ctx);
}

FLYWAVE_SVG_API _Bool svg_context_has_error(svg_context_t *ctx) {
  return !ctx->error.empty();
}

FLYWAVE_SVG_API const char *svg_context_get_error(svg_context_t *ctx) {
  return ctx->error.c_str();
}

FLYWAVE_SVG_API int svg_context_resize(svg_context_t *ctx, unsigned sx,
                                       unsigned sy) {
  int stride;
  ctx->frame_buffer.create(sx, sy, flip_y_e, stride);
  return stride;
}

FLYWAVE_SVG_API void svg_context_get_size(svg_context_t *ctx, unsigned *sx,
                                          unsigned *sy, int *stride) {
  *sx = ctx->frame_buffer.width();
  *sy = ctx->frame_buffer.height();
  *stride = ctx->frame_buffer.ren_buf().stride();
}

FLYWAVE_SVG_API svg_render_buf_t *
svg_render_buf_create_empty(svg_context_t *ctx) {
  svg_render_buf_t *buf = new svg_render_buf_t;
  return buf;
}

FLYWAVE_SVG_API svg_render_buf_t *svg_render_buf_create(uint8_t *data,
                                                        unsigned width,
                                                        unsigned height,
                                                        int stride) {
  svg_render_buf_t *buf =
      new svg_render_buf_t{agg::rendering_buffer{data, width, height, stride}};
  return buf;
}

FLYWAVE_SVG_API void svg_render_buf_free(svg_render_buf_t *buf) {
  if (buf != nullptr) {
    delete buf;
  }
}

FLYWAVE_SVG_API void svg_render_buf_attach(svg_render_buf_t *rbuf, uint8_t *buf,
                                           unsigned width, unsigned height,
                                           int stride) {
  rbuf->rbuf.attach(buf, width, height, stride);
}

FLYWAVE_SVG_API void svg_render_buf_get_size(svg_render_buf_t *rbuf,
                                             unsigned *width, unsigned *height,
                                             int *stride) {
  *width = rbuf->rbuf.width();
  *height = rbuf->rbuf.height();
  *stride = rbuf->rbuf.stride();
}

FLYWAVE_SVG_API void svg_render_buf_clear(svg_render_buf_t *rbuf, uint8_t v) {
  rbuf->rbuf.clear(v);
}

FLYWAVE_SVG_API void svg_render_buf_copy_from(svg_render_buf_t *ctx,
                                              svg_render_buf_t *src) {
  ctx->rbuf.copy_from(src->rbuf);
}

#ifdef __cplusplus
}
#endif
