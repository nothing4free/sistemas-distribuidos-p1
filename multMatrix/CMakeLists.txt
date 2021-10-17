cmake_minimum_required (VERSION 2.8.11)

#project (multMatrix)

#add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h multMatrixImp.cpp multMatrixImp.h multMatrixStub.cpp multMatrixStub.h )

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(serverMatrix LANGUAGES CXX)
add_executable(serverMatrix mainServer.cpp utils.cpp utils.h multmatrix.cpp
                multmatrix.h multMatrixImp.cpp multMatrixImp.h)
target_link_libraries(serverMatrix pthread)

project(serverMatrix LANGUAGES CXX)
add_executable(clientMatrix mainClient.cpp utils.cpp utils.h multmatrix.cpp
                multmatrix.h multMatrixStub.cpp multMatrixStub.h)
target_link_libraries(clientMatrix pthread)