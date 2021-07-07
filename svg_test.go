package svg

import (
	"image/color"
	"testing"

	"github.com/flywave/imaging"
)

func TestSvg(t *testing.T) {
	ctx := NewContext(600, 400, false)
	ctx.Parse("./data/tiger.svg")
	ctx.Clear(color.Transparent)
	buf := ctx.Render()

	img := buf.GetImage()

	imaging.Save(img, "./data/out.png")
}
