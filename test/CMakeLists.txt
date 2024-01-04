add_subdirectory(./catch2 cmake-build-debug/Catch2-build)
add_executable(test-main test-main.cpp)

target_link_libraries(test-main PUBLIC ini_lib)
target_link_libraries(test-main PRIVATE Catch2::Catch2)