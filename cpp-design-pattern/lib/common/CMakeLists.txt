add_library(common STATIC
    include/common.hpp
    common.cpp
)

target_link_libraries(common PUBLIC )
target_include_directories(common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/creational
    ${CMAKE_CURRENT_SOURCE_DIR}/structural
    ${CMAKE_CURRENT_SOURCE_DIR}/behavioral
)
target_link_libraries(common
    base
)