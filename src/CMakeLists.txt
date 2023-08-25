cmake_minimum_required(VERSION 3.1)


#搜索源文件
aux_source_directory(. SRC)

#编译静态库文件

add_library(src ${SRC})