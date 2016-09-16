cmake_minimum_required(VERSION 3.4.3)

project(ChessEngine)
set(ChessEngine_VERSION_MAJOR 0)
set(ChessEngine_VERSION_MINOR 0)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMakeModules)

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.61.0 REQUIRED COMPONENTS unit_test_framework)
include_directories(${PROJECT_SOURCE_DIR}/inc ${Boost_INCLUDE_DIRS})

set(SUTs Board FENParser Game Helpers Location Piece Player SimpleSquare SimpleSquareFactory KnightMoveLogic)
foreach(SUT ${SUTs})
	list(APPEND SUTSrc "test/Test${SUT}.cpp")
	list(APPEND Src "src/${SUT}.cpp")
endforeach()

set(Mocks SquareFactory Piece FENParserDelegate FENParser Board PieceMoveLogic)
foreach(Mock ${Mocks})
	list(APPEND MockSrc "src/mocks/${Mock}.cpp")
endforeach()

add_executable(ChessTest "test/TestMain.cpp" ${SUTSrc} ${MockSrc} ${Src})
target_link_libraries(ChessTest ${Boost_LIBRARIES})
if(APPLE)
	find_library(clang_rt NAMES clang_rt.profile_osx PATHS "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/7.3.0/lib/darwin/")
	target_link_libraries(ChessTest ${clang_rt})
endif()
set_target_properties(ChessTest PROPERTIES COMPILE_FLAGS "-Wno-c++11-extensions -Wall -Werror -std=c++1z -stdlib=libc++ -g -O0 -fprofile-arcs -ftest-coverage")

add_custom_target(_clean COMMAND rm -rf ${PROJECT_SOURCE_DIR}/build/*)
add_custom_target(_test COMMAND ${PROJECT_SOURCE_DIR}/ChessTest --report_level=short)

include(CodeCoverage)
SETUP_TARGET_FOR_COVERAGE(codecoverage ${PROJECT_SOURCE_DIR}/ChessTest coverage)