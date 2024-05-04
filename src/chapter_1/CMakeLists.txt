project(chapter_1)

add_executable(hello_world hello.c)

install(TARGETS hello_world DESTINATION ${OUTPUT_ROOT}/bin)