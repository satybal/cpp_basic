cmake_minimum_required(VERSION 3.5)

project(03.guess_the_number)

add_executable(guess_the_number
    guess_the_number.cpp
	check_value.cpp
	check_value.h
	random_value.cpp
	random_value.h
	high_scores.cpp
	high_scores.h
)

set_target_properties(guess_the_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
