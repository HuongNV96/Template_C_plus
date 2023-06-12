cmake_minimum_required (VERSION 2.8.11)
project (Template_C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

add_executable(SingletonTest SingletonTemplateEx.cpp)

add_executable(HandlerTest HandlerTemplateEx.cpp)
target_link_libraries(HandlerTest pthread)
