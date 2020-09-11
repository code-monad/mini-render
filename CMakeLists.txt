cmake_minimum_required(VERSION 3.5)
project(mini_render)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL)
find_package(fmt)

if(APPLE)
  add_subdirectory(${CMAKE_SOURCE_DIR}/3rd_party/curlpp)
endif()

set(RENDER_SRCS
  ${CMAKE_SOURCE_DIR}/src/http.cc
  ${CMAKE_SOURCE_DIR}/src/template.cc
  ${CMAKE_SOURCE_DIR}/src/render.cc
  ${CMAKE_SOURCE_DIR}/src/parse.cc
  ${CMAKE_SOURCE_DIR}/src/manager.cc
  )

add_library(mrender ${RENDER_SRCS})

add_library(mrender::core ALIAS mrender)

target_link_libraries(mrender
  PUBLIC curl curlpp fmt::fmt)

target_include_directories(mrender PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/3rd_party/json/include
  ${CMAKE_SOURCE_DIR}/3rd_party/argparse/include
  )
add_executable(poster ${CMAKE_SOURCE_DIR}/src/main.cc)

target_link_libraries(poster PUBLIC mrender::core)



install(TARGETS poster mrender
  RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin
  LIBRARY DESTINATION lib)
