######### CMAKE VERSION ########################
cmake_minimum_required(VERSION 3.16)
set(This test)

######### PROJECT NAME #########################
project(${This} C CXX)

######### FOLDERS ##############################
include_directories("Car_StateMachine/")

######### SOURCES ##############################
file(GLOB SOURCES "test.c*"
                  "Car_StateMachine/*.c*"
)

######### OTHERS ###############################
add_executable(${This} ${SOURCES})