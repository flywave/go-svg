package svg

// #include <stdlib.h>
// #include <string.h>
// #include "svg_api.h"
// #cgo CFLAGS: -I ./  -I ./libs
// #cgo CXXFLAGS: -I ./ -I ./libs
import "C"
import (
	"image"
	"image/color"
	"runtime"
	"unsafe"
)

type RenderBuf struct {
	m   *C.struct__svg_render_buf_t
	buf []byte
}

func NewRenderBuf(width, height uint32, stride int32) *RenderBuf {
	buf := make([]byte, int(height*uint32(stride)))
	cb := C.svg_render_buf_create((*C.uchar)(unsafe.Pointer(&buf[0])), C.uint(width), C.uint(height), C.int(stride))
	ret := &RenderBuf{m: cb, buf: buf[:]}
	runtime.SetFinalizer(ret, (*RenderBuf).free)
	return ret
}

func (g *RenderBuf) free() {
	C.svg_render_buf_free(g.m)
}

func (g *RenderBuf) GetSize() (width, height uint32, stride int32) {
	var w, h C.uint
	var s C.int
	C.svg_render_buf_get_size(g.m, &w, &h, &s)
	width, height, stride = uint32(w), uint32(h), int32(s)
	return
}

func (ctx *RenderBuf) Clear(c uint8) {
	C.svg_render_buf_clear(ctx.m, C.uchar(c))
}

func (ctx *RenderBuf) CopyFrom(s *RenderBuf) {
	C.svg_render_buf_copy_from(ctx.m, s.m)
}

func (ctx *RenderBuf) GetRaw() []byte {
	return ctx.buf
}

func (ctx *RenderBuf) GetImage() image.Image {
	width, height, _ := ctx.GetSize()

	rect := image.Rect(0, 0, int(width), int(height))
	rgba := image.NewNRGBA(rect)

	copy(rgba.Pix, ctx.buf)
	for y := 0; y < int(height); y++ {
		for x := 0; x < int(width); x++ {
			c := rgba.NRGBAAt(x, y)
			rgba.Set(x, y, color.NRGBA{R: c.B, G: c.G, B: c.R, A: c.A})
		}
	}
	return rgba
}
