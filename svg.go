package svg

// #include <stdlib.h>
// #include <string.h>
// #include "svg_api.h"
// #cgo CFLAGS: -I ./  -I ./libs
// #cgo CXXFLAGS: -I ./ -I ./libs
// #cgo linux LDFLAGS:  -L ./libs/linux -Wl,--start-group  -lstdc++ -lm -pthread -ldl -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licudata -licudt -licui18n -licutools -licuuc   -Wl,--end-group
// #cgo windows LDFLAGS: -L ./libs/windows -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licudata -licudt -licui18n -licutools -licuuc
// #cgo darwin LDFLAGS: -L /usr/libs/darwin -lc++ -L　./libs -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licudata -licudt -licui18n -licutools -licuuc
// #cgo darwin,arm LDFLAGS: -L /usr/libs/darwin_arm -lc++ -L　./libs -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licudata -licudt -licui18n -licutools -licuuc
import "C"
