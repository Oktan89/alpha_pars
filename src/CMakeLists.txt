cmake_minimum_required(VERSION 3.0.0)

set(SOURCES main.cpp getdate.cpp logreader.cpp logparser.cpp database.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(Boost_INCLUDE_DIR "C:\\boost\\boost_1_78_0")
set(Boost_LYBRARY_DIR "C:\\boost_1_78_0\\stage\\lib")

find_package(Boost COMPONENTS REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LYBRARY_DIR})
endif()

add_executable(Alpha_pars ${SOURCES})


target_link_libraries(Alpha_pars ${Boost_LYBRARIES})


if(MINGW)
    target_link_libraries(Alpha_pars ws2_32)
endif()

#Подключаем потоки
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
target_link_libraries(Alpha_pars Threads::Threads)

target_include_directories(Alpha_pars PUBLIC ${MY_INCLUDE_DIR})

