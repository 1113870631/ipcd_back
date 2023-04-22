cmake_minimum_required(VERSION 3.0.0)
project(IPCD_BACK VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories("include")
link_directories("lib")
ADD_LIBRARY(IPCD_BACK_PORT  SHARED src/ipcd_backport.cpp  include/ipcd_backport.h src/config.cpp)
target_link_libraries(IPCD_BACK_PORT  "libxml2.dll")

add_executable(IPCD_back_test main.cpp )
target_link_libraries(IPCD_back_test IPCD_BACK_PORT "libxml2.dll")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
