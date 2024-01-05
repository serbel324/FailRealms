cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)

set(INCPATH ${PROJECT_SOURCE_DIR}/include)

project(Driver)

set(SOURCES
    driver.cpp)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${INCPATH}
)

target_link_libraries(${PROJECT_NAME}
    Core
)