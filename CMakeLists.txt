cmake_minimum_required(VERSION 3.10)

project(test)

message(${PROJECT_SOURCE_DIR} ":Project Name: " ${PROJECT_NAME})

# 查找当前目录下的所有源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)

# 设定头文件路径
include_directories(${PROJECT_SOURCE_DIR}/inc)


# 生成目标 以及源文件
add_executable(${PROJECT_NAME} ${SRCS})

# 设定库
# set(LIB ${PROJECT_SOURCE_DIR}/lib/test.a)

# 链接库
# 有三种
# 1、link_directories链接库目录
# 2、target_link_libraries 添加单个
# 3、find_library() 查找库
target_link_libraries(${PROJECT_NAME} ${LIB})
