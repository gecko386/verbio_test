cmake_minimum_required (VERSION 3.1)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()


project (number_translator)

add_executable(number_translator 	src/number_translator.cpp
									src/Token.cpp
									src/NumericParser.cpp)
