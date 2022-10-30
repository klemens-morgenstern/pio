cmake_minimum_required(VERSION 3.23)
project(pio)

set(CMAKE_CXX_STANDARD 20)

include_directories(include ../asio/asio/include)
add_compile_definitions(ASIO_HAS_IO_URING=1)

add_library(pio src/pio/buffer.cpp src/pio/post.cpp src/pio/dispatch.cpp src/pio/defer.cpp include/pio/system_timer.hpp include/pio/basic_waitable_timer.hpp src/pio/system_timer.cpp src/pio/steady_timer.cpp src/pio/high_resolution_timer.cpp include/pio/signal_set.hpp src/pio/signal_set.cpp include/pio/serial_port.hpp src/pio/serial_port.cpp include/pio/stream_file.hpp src/pio/stream_file.cpp src/pio/random_access_file.cpp include/pio/random_access_file.hpp include/pio/writable_pipe.hpp src/pio/readable_pipe.cpp src/pio/writable_pipe.cpp include/pio/connect_pipe.hpp src/pio/connect_pipe.cpp include/pio/write.hpp include/pio/write_at.hpp include/pio/read.hpp include/pio/read_at.hpp src/pio/read.cpp src/pio/read_at.cpp src/pio/write.cpp src/pio/write_at.cpp)

add_subdirectory(test)