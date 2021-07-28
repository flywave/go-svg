package svg

// #include <stdlib.h>
// #include <string.h>
// #include "svg_api.h"
// #cgo CFLAGS: -I ./  -I ./libs
// #cgo CXXFLAGS: -I ./ -I ./libs
// #cgo linux LDFLAGS:  -L ./libs -Wl,--start-group  -lstdc++ -lm -pthread -ldl -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licudata -licudt -licui18n -licutools -licuuc -lplatform -Wl,--end-group
// #cgo windows LDFLAGS: -L ./libs -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licudata -licudt -licui18n -licutools -licuuc -lplatform
// #cgo darwin LDFLAGS: -L /usr/lib -lc++ -L　./libs -lcsvg -lsvg -lxml2 -lzlib -lantigrain -lcontrols -lexpat -lfontconfig -lfreetype -licudata -licudt -licui18n -licutools -licuuc
import "C"
