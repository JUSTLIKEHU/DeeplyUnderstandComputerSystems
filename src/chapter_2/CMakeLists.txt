project(chapter_2)

file(GLOB_RECURSE SOURCES_FILS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_executable(main ${SOURCES_FILS})

install(TARGETS main DESTINATION ${OUTPUT_ROOT}/${PROJECT_NAME}/bin)