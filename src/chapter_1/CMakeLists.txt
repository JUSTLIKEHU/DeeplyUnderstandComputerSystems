project(chapter_1)

add_executable(hello_world hello.c)
target_link_options(hello_world PRIVATE -static)

install(TARGETS hello_world DESTINATION ${OUTPUT_ROOT}/${PROJECT_NAME}/bin)