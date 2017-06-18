cmake_minimum_required(VERSION 3.3)
project(spotisync_client)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14)


### CURL CONFIG
option(BUILD_CURL_EXE "" OFF)
option(CURL_STATICLIB "" ON)
option(HTTP_ONLY "" ON)
option(ENABLE_MANUAL "" OFF)
option(CURL_DISABLE_CRYPTO_AUTH "" ON)
option(USE_UNIX_SOCKETS "" OFF)
option(USE_LIBSSH2 "" OFF)
option(CMAKE_USE_LIBSSH2 "" OFF)
add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/curl" EXCLUDE_FROM_ALL)

### RAPIDJSON CONFIG
add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/rapidjson" EXCLUDE_FROM_ALL)
find_package(RapidJSON REQUIRED)


### CAP'N' PROTO CONFIG
set(BUILD_TESTING OFF)
add_subdirectory("${CMAKE_SOURCE_DIR}/third_party/capnproto" EXCLUDE_FROM_ALL)
capnp_generate_cpp(CAPNP_SRCS CAPNP_HDRS "src/schema.capnp")
include_directories("${CMAKE_BINARY_DIR}/generated")

### SPOTISYNC CONFIG
set(SRC
    src/main.cpp
    ${CAPNP_SRCS}
)

add_executable(spotisync ${SRC})

# Enforce consistent naming on CapnProto headers
foreach(header_path ${CAPNP_HDRS})
    get_filename_component(filename ${header_path} NAME_WE)
    add_custom_command(TARGET spotisync PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${header_path} "${CMAKE_BINARY_DIR}/generated/${filename}.hpp")
endforeach()

target_link_libraries(spotisync 
    PRIVATE Threads::Threads 
    PRIVATE libcurl
    PRIVATE CapnProto::capnp-rpc
    PRIVATE RapidJSON
)
