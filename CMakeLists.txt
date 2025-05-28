cmake_minimum_required(VERSION 3.16)
project(tree_hugger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib)

include_directories(include)

set(TREE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/tree.h
)
add_library(tree)
target_sources(tree
 PRIVATE
  ${TREE_SOURCES}
  )
target_include_directories(tree
 PRIVATE
 ${INCLUDE}
 include
)

set(STACK_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/stack.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/stack.h
)
add_library(stack)
target_sources(stack
 PRIVATE
  ${STACK_SOURCES}
  )
target_include_directories(stack
 PRIVATE
 ${INCLUDE}
 ${raylib_INCLUDE_DIRS}
 )

set(TREE_HUGGER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/tree_hugger.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/tree_hugger.h
)
add_library(tree_hugger)
target_sources(tree_hugger
 PRIVATE
  ${TREE_HUGGER_SOURCES}
  )
target_include_directories(tree_hugger
 PRIVATE
 ${INCLUDE}
 include
 ${raylib_INCLUDE_DIRS}
)
target_link_libraries(tree_hugger
  tree
  stack
)

set(MAIN_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
  )
add_executable(main)
target_sources(main
 PRIVATE
  ${MAIN_SRC}
)
target_include_directories(main
 PRIVATE
 ${INCLUDE}
 include
 ${raylib_INCLUDE_DIRS}
)
target_link_libraries(main
  tree_hugger
  tree
  stack
)

