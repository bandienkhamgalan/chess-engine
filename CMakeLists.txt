cmake_minimum_required(VERSION 3.4.3)

project(ChessEngine)
set(ChessEngine_VERSION_MAJOR 0)
set(ChessEngine_VERSION_MINOR 0)

enable_testing()
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(Boost_USE_STATIC_LIBS       OFF)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.61.0 REQUIRED COMPONENTS unit_test_framework)
include_directories(${PROJECT_SOURCE_DIR}/inc ${Boost_INCLUDE_DIRS})

set(SUTs Board FENParser Game Helpers Location Piece Player SimpleSquare SimpleSquareFactory)
foreach(SUT ${SUTs})
	list(APPEND SUTSrc "test/Test${SUT}.cpp")
	list(APPEND Src "src/${SUT}.cpp")
endforeach()
set(Mocks SquareFactory Piece FENParserDelegate FENParser Board)
foreach(Mock ${Mocks})
	list(APPEND MockSrc "src/mocks/${Mock}.cpp")
endforeach()

add_executable(ChessTest "test/TestMain.cpp" ${SUTSrc} ${MockSrc} ${Src})
target_link_libraries(ChessTest ${Boost_LIBRARIES})
set_target_properties(ChessTest PROPERTIES COMPILE_FLAGS "-Wno-c++11-extensions -Wall -Werror -std=c++11 -stdlib=libc++")

add_test(NAME ChessTest COMMAND ChessTest --report_level=short)