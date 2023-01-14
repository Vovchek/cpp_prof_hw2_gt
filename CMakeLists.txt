cmake_minimum_required(VERSION 3.14)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

# ++for google test
include(FetchContent)   # run ..\CMake\share\cmake-X.YY\Modules\FetchContent.cmake
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()    # Enables testing for this directory and below
add_executable(ip_filter_test ip_filter_test.cpp ip_filter.cpp)
target_link_libraries(ip_filter_test GTest::gtest_main)
# --for google test

add_executable(ip_filter_cli main.cpp ip_filter.cpp) # target source ...

set_target_properties(ip_filter_cli PROPERTIES    # target PROPERTIES prop1 value1  ...
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

# ++for google test
include(GoogleTest)               # run ..\CMake\share\cmake-X.YY\Modules\GoogleTest.cmake
gtest_discover_tests(ip_filter_test)  # discover tests by asking the compiled test executable to enumerate its tests
# ++for google test

#install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
