SET( svg_HEADERS
agg_svg_assoc_pod_array.h
agg_svg_attributes.h
agg_svg_attributes_map.h
agg_svg_attribute_source.h
agg_svg_attributes_setter.h
agg_svg_basics.h
agg_svg_color_parser.h
agg_svg_data_accessor.h
agg_svg_defines.h
agg_svg_dom_read_protocol.h
agg_svg_dom_storage.h
agg_svg_exception.h
agg_svg_frame_buffer_rgba.h
agg_svg_gradient.h
agg_svg_gradient_lut_cache.h
agg_svg_indexation_interpreter.h
agg_svg_iomemstream.h
agg_svg_parse_real.h
agg_svg_parser.h
agg_svg_path_interpreter.h
agg_svg_path_renderer.h
agg_svg_path_serializer.h
agg_svg_path_tokenizer.h
agg_svg_percent.h
agg_svg_pipeline.h
agg_svg_ptr_size_pair.h
agg_svg_rasterizer.h
agg_svg_renderer_rgba.h
agg_svg_rendering_interpreter.h
agg_svg_shape_adaptors.h
agg_svg_tags.h
agg_svg_transformer.h
agg_svg_utils.h
member_comparer.h
)

SET( svg_SOURCES
agg_svg_attributes.cpp
agg_svg_attributes_map.cpp
agg_svg_attributes_setter.cpp
agg_svg_color_parser.cpp
agg_svg_dom_read_protocol.cpp
agg_svg_dom_storage.cpp
agg_svg_gradient.cpp
agg_svg_parser.cpp
agg_svg_parse_real.cpp
agg_svg_path_renderer.cpp
agg_svg_path_tokenizer.cpp
agg_svg_renderer_rgba.cpp
agg_svg_rendering_interpreter.cpp
agg_svg_transformer.cpp
agg_svg_utils.cpp
)

ADD_LIBRARY( svg STATIC
    ${svg_SOURCES}
)


SET_TARGET_PROPERTIES(svg PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(svg PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(svg PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
  