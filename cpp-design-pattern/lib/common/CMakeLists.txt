add_library(common STATIC
    include/common.hpp
    common.cpp
    creational/factory/factory.hpp
)

target_link_libraries(common PUBLIC )
target_include_directories(common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/factory
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/abstract_factory
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/singleton
    ${CMAKE_CURRENT_SOURCE_DIR}/creational/builder
)
target_link_libraries(common
    base
)