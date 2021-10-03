configure_file(config.h.in ${PROJECT_BINARY_DIR}/include/projectconfig.h)
include_directories(${PROJECT_BINARY_DIR}/include)

add_subdirectory(data)
add_subdirectory(plan)
add_subdirectory(ui)
add_subdirectory(proofs)