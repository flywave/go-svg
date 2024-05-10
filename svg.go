package svg

// #include <stdlib.h>
// #include <string.h>
// #include "svg_api.h"
// #cgo CFLAGS: -I ./  -I ./libs
// #cgo CXXFLAGS: -I ./ -I ./libs
// #cgo linux LDFLAGS:  -L ./libs/linux -Wl,--start-group  -lstdc++ -lm -pthread -ldl -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licutools-svg -licui18n-svg -licudt-svg -licudata-svg -licuuc-svg   -Wl,--end-group
// #cgo windows LDFLAGS: -L ./libs/windows -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licutools-svg -licui18n-svg -licudt-svg -licudata-svg -licuuc-svg
// #cgo darwin LDFLAGS: -L /usr/libs/darwin -lc++ -L　./libs -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licutools-svg -licui18n-svg -licudt-svg -licudata-svg -licuuc-svg
// #cgo darwin,arm LDFLAGS: -L /usr/libs/darwin_arm -lc++ -L　./libs -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licutools-svg -licui18n-svg -licudt-svg -licudata-svg -licuuc-svg
import "C"
