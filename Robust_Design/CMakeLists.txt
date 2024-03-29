cmake_minimum_required(VERSION 3.14)
project(Robust_Design)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	${PROJECT_NAME}
	src/CleanHeader.cpp
	src/Test_Robust_Design.cpp
	src/Widget.cpp
)

target_include_directories(
	${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/header
	../
)
target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
)

include(GoogleTest)
# gtest_discover_tests(${PROJECT_NAME})