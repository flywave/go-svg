package svg

// #include <stdlib.h>
// #include <string.h>
// #include "svg_api.h"
// #cgo CFLAGS: -I ./  -I ./libs
// #cgo CXXFLAGS: -I ./ -I ./libs
import "C"
import (
	"image/color"
	"runtime"
	"unsafe"
)

type Context struct {
	m *C.struct__svg_context_t
}

func NewContext(width, height uint32, flip_y bool) *Context {
	ret := &Context{m: C.svg_context_create(C.bool(flip_y))}
	runtime.SetFinalizer(ret, (*Context).free)
	ret.Resize(width, height)
	return ret
}

func (g *Context) free() {
	C.svg_context_free(g.m)
}

func (ctx *Context) Clear(c color.Color) {
	r, g, b, a := c.RGBA()
	C.svg_context_clear(ctx.m, C.uchar(r/256), C.uchar(g/256), C.uchar(b/256), C.uchar(a/256))
}

func (g *Context) Reset() {
	C.svg_context_reset(g.m)
}

func (g *Context) Parse(svg string) {
	cstr := C.CString(svg)
	defer C.free(unsafe.Pointer(cstr))
	C.svg_context_parse(g.m, cstr)
}

func (g *Context) Resize(width, height uint32) {
	C.svg_context_resize(g.m, C.uint(width), C.uint(height))
}

func (g *Context) GetSize() (width, height uint32, stride int32) {
	var w, h C.uint
	var s C.int
	C.svg_context_get_size(g.m, &w, &h, &s)
	width, height, stride = uint32(w), uint32(h), int32(s)
	return
}

func (g *Context) Render() *RenderBuf {
	width, height, stride := g.GetSize()
	buf := NewRenderBuf(width, height, stride)
	C.svg_context_draw(g.m, buf.m)
	return buf
}
