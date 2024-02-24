cmake_minimum_required(VERSION 3.14)
project(Ch19_Containers)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCE_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/header)
set(SOURCE_SOLUTION1 ${CMAKE_CURRENT_SOURCE_DIR}/solution1)
set(SOURCE_SOLUTION2 ${CMAKE_CURRENT_SOURCE_DIR}/solution2)
set(SOURCE_SOLUTION3 ${CMAKE_CURRENT_SOURCE_DIR}/solution3)
set(SOURCE_SOLUTION4 ${CMAKE_CURRENT_SOURCE_DIR}/solution4)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(Time_Library)
add_subdirectory(${SOURCE_SOLUTION1})
add_subdirectory(${SOURCE_SOLUTION2})
add_subdirectory(${SOURCE_SOLUTION3})
add_subdirectory(${SOURCE_SOLUTION4})

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${HEADER_DIR}/*.hpp ${HEADER_DIR}/*.h)

add_executable(
	${PROJECT_NAME}
	${SOURCES}
	${HEADERS}
)

target_include_directories(
	${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/header
	../
)
target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
  Time_Library
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()