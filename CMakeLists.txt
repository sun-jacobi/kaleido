project(kaleido)
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(kallib STATIC 
    ${PROJECT_SOURCE_DIR}/src/ast.cpp
    ${PROJECT_SOURCE_DIR}/src/lexer.cpp
    ${PROJECT_SOURCE_DIR}/src/parser.cpp
    ${PROJECT_SOURCE_DIR}/src/driver.cpp  
)


############################################################
# LLVM 
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

message(STATUS "${LLVM_INCLUDE_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
llvm_map_components_to_libnames(llvm_libs support core irreader)
############################################################


add_executable(kaledio src/main.cpp)
target_include_directories(kaledio
    PRIVATE 
        "${PROJECT_SOURCE_DIR}/include"
)



target_include_directories(kallib
    PRIVATE 
    "${PROJECT_SOURCE_DIR}/include"
)


target_link_libraries(kaledio kallib ${llvm_libs})

