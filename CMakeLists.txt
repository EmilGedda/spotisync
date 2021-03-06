cmake_minimum_required(VERSION 3.3)
project(spotisync_client)
find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include "${CMAKE_SOURCE_DIR}/third_party/json/src")
link_directories(/usr/local/lib)

set(PROTO_PATH "${CMAKE_SOURCE_DIR}/protos")
set(SPOTISYNC_PROTO "${PROTO_PATH}/spotisync.proto")
set(GENERATED_PROTOBUF_PATH "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTOBUF_PATH})

set(SPOTISYNC_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/spotisync.pb.cc")
set(SPOTISYNC_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/spotisync.pb.h")
set(SPOTISYNC_GRPC_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/spotisync.grpc.pb.cc")
set(SPOTISYNC_GRPC_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/spotisync.grpc.pb.h")

add_custom_command(
    OUTPUT "${SPOTISYNC_PB_H_FILE}"
    "${SPOTISYNC_PB_CPP_FILE}"
    "${SPOTISYNC_GRPC_PB_H_FILE}"
    "${SPOTISYNC_GRPC_PB_CPP_FILE}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--cpp_out=${GENERATED_PROTOBUF_PATH}"
         "${SPOTISYNC_PROTO}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--grpc_out=${GENERATED_PROTOBUF_PATH}"
         "--plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin" #TODO: Read up on this for windows
         "${SPOTISYNC_PROTO}"
    DEPENDS "${SPOTISYNC_PROTO}"
    )

set(GENERATED_PROTOBUF_FILES ${SPOTISYNC_PB_H_FILE} ${SPOTISYNC_PB_CPP_FILE}
    ${SPOTISYNC_GRPC_PB_H_FILE} ${SPOTISYNC_GRPC_PB_CPP_FILE})

set(
    SOURCE_FILES
    src/track.cpp
    src/client.cpp
    src/spotify.hpp
    src/track.cpp
    src/spotifyupdate.cpp   
    src/main.cpp
)
include_directories(${GENERATED_PROTOBUF_PATH})
link_libraries(grpc++_unsecure grpc gpr ${PROTOBUF_LIBRARY})

add_executable(spotisync ${SOURCE_FILES} ${GENERATED_PROTOBUF_FILES})
target_link_libraries(spotisync Threads::Threads)
