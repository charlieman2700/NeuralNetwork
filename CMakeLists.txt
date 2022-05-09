cmake_minimum_required(VERSION )


PROJECT(NeuralNetwork)

add_subdirectory(src)
add_subdirectory(include)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIRS})
