#
# Author:     Oliver Blaser
#
# Date c:     29.11.2020
# Date e:     29.11.2020
#

cmake_minimum_required(VERSION 3.19)

project(cmake_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(
cmakeTestPrjExe
../main.cpp
../subModule/subModule.cpp
)
