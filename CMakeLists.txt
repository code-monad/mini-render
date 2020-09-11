cmake_minimum_required(VERSION 3.5)
project(mini_render)

set(CMAKE_CXX_STANDARD 17)




set(RENDER_SRCS
  ${CMAKE_SOURCE_DIR}/src/template.cc
  ${CMAKE_SOURCE_DIR}/src/manager.cc
  )

add_library(mrender ${RENDER_SRCS})

add_library(mrender::core ALIAS mrender)

target_link_libraries(mrender)

target_include_directories(mrender PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/json/include
  ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/argparse/include
  )

set(POSTER_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/parse.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/http.cc)

option(BUILD_CLI "Build the CLI program" ON)

if(BUILD_CLI)
  find_package(CURL)
  find_package(fmt)
  add_subdirectory(${CMAKE_SOURCE_DIR}/3rd_party/curlpp)
  add_executable(poster ${POSTER_SRCS})
  target_link_libraries(poster PUBLIC fmt::fmt mrender::core curl curlpp)
  target_include_directories(poster PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/curlpp/include
  )
endif()


