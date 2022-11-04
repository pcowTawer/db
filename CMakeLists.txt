cmake_minimum_required(VERSION 3.5)
project(DB)

add_executable(DB db.cpp)

target_include_directories(DB
PRIVATE
        mongo-cxx-driver/include/mongocxx/v_noabi/
        mongo-cxx-driver/include/bsoncxx/v_noabi/
)
target_link_directories(DB
PRIVATE
    mongo-cxx-driver/lib
    mongo-c-driver/lib
    mongo-cxx-driver/bin
    mongo-c-driver/bin
)
target_link_libraries(DB
PRIVATE
        bsoncxx
        mongocxx
)
