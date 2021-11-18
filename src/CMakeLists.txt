cmake_minimum_required(VERSION 3.0.0)

set(SOURCES main.cpp getdate.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(Alpha_pars ${SOURCES})

target_include_directories(Alpha_pars PUBLIC ${MY_INCLUDE_DIR})