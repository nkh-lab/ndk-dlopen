cmake_minimum_required(VERSION 3.10.2)

find_library(log-lib log)

add_library(native-lib SHARED native-lib.cpp)
target_link_libraries(native-lib ${log-lib} Boost::filesystem)

add_library(plugin SHARED plugin.cpp)
target_link_libraries(plugin Boost::boost)
