cmake_minimum_required(VERSION 3.17)

project(cppbot)

set(CMAKE_CXX_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq -Wall -lstdc++")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)  

set(PQXX /usr/local/include/pqxx)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

add_subdirectory(botstaff)
add_executable(cppbot main.cpp)
target_link_libraries(cppbot func /usr/local/lib/libTgBot.a ${PQXX_LIB} ${PQ_LIB} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
#target_link_libraries(cppbot func /usr/local/lib/libTgBot.a ${PQXX_LIB} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})