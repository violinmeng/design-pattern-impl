add_library(base STATIC
    include/base.hpp
    base.cpp
)

target_link_libraries(base PUBLIC )
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(base
)