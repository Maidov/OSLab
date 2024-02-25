cmake_minimum_required(VERSION 3.10)

project(YourProjectName)

# Укажите исходные файлы вашего проекта
file(GLOB SOURCES "src/*.cpp")

# Установка переменной CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "/usr/local;/usr")

find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)

# Поиск библиотеки ZeroMQ

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )
# Укажите, в какие исполняемые файлы должны быть скомпилированы ваши исходные файлы
add_executable(calculation src/calculation_node.cpp)
add_executable(control src/control.cpp)

# Линковка библиотек к исполняемым файлам
target_link_libraries(calculation PRIVATE ${ZeroMQ_LIBRARY})
target_link_libraries(control PRIVATE ${ZeroMQ_LIBRARY})

## add the include directory to our compile directives
target_include_directories(calculation PUBLIC ${ZeroMQ_INCLUDE_DIR})
## at the 0mq library to our link directive
target_link_libraries(calculation PUBLIC ${ZeroMQ_LIBRARY})


## add the include directory to our compile directives
target_include_directories(control PUBLIC ${ZeroMQ_INCLUDE_DIR})
## at the 0mq library to our link directive
target_link_libraries(control PUBLIC ${ZeroMQ_LIBRARY})