add_executable(test_$
    test_$.cpp
)

target_link_libraries(test_$
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_$)