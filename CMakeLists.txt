cmake_minimum_required(VERSION 3.10)

project(lwslog VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only part
add_library(lwslog INTERFACE)

cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)



# Interface library ASIO
add_library(asio INTERFACE)

# Add include dir
target_include_directories(asio INTERFACE
    ${CMAKE_SOURCE_DIR}/libs/asio/include
)

# Add define
target_compile_definitions(asio INTERFACE
    ASIO_STANDALONE
    ASIO_NO_DEPRECATED
)
if(WIN32)
    # Windows specific settings
    target_compile_definitions(asio INTERFACE
        _WIN32_WINNT=0x0601  # Windows 7 and more
        WIN32_LEAN_AND_MEAN  
    )
    
    # add windows socket
    target_link_libraries(asio INTERFACE
        ws2_32    # Windows Sockets 2
        wsock32   # Windows Sockets 1.1 
    )
    
else()
    # Unix/Linux/MacOS
    target_link_libraries(asio INTERFACE pthread)
endif()



# Directory with headers
target_include_directories(lwslog INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

# Implementation library
add_library(lwslog_impl STATIC
    src/FileSink.cpp
)

# add include dirs for lwslog_impl
target_include_directories(lwslog_impl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Executable
add_executable(main temp/test.cpp)
target_link_libraries(main PRIVATE lwslog lwslog_impl)