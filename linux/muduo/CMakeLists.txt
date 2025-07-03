# 设置cmake版本
cmake_minimum_required(VERSION 3.10)
# 项目名称
project(muduo)
# 设置项目编译生成的lib文件的输出目录
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# 设置编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -w")
# 添加源文件
aux_source_directory(. SRC_LIST)
# 生成可执行文件
add_executable(muduo ${SRC_LIST})