cmake_minimum_required(VERSION 3.17)
set(PROJECT iz_1)
project(${PROJECT})
set(CMAKE_CXX_STANDARD 14)

################################
# Files
set (HEADERS
        Errors/error_codes.h
        Errors/error_message.h
        Exchange_of_currency/currency.h
        Exchange_of_currency/currency_pair.h
        Exchange_of_currency/array_of_currencies.h
        Exchange_of_currency/offer.h
        Exchange_of_currency/array_of_offers.h
        Exchange_of_currency/currency_exchange_rates.h
        Task_manager/task_manager.h)

set (SOURCES
        Errors/error_message.c
        Exchange_of_currency/currency_pair.c
        Exchange_of_currency/array_of_currencies.c
        Exchange_of_currency/offer.c
        Exchange_of_currency/array_of_offers.c
        Exchange_of_currency/currency_exchange_rates.c
        Task_manager/task_manager.c)


##############################
# Release
set(RELEASE_FLAGS "-std=c++14 -Wall  -Werror -pedantic")

# Debug
set(DEBUG_FLAGS "-std=c++14 -Wall -pedantic -g3")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")


#Choice target
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("BUILD_TYPE -- DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS}")
    add_executable (${PROJECT}
            ${HEADERS}
            main.c
            ${SOURCES})

elseif (CMAKE_BUILD_TYPE MATCHES Test)
    message("BUILD_TYPE -- TEST")
    add_subdirectory(googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_FLAGS} -g -Wall")

    add_executable(${PROJECT}
            ${HEADERS}
            Tests/test.cpp
            Tests/unit_tests.cpp
            ${SOURCES})

    target_link_libraries(${PROJECT}
            gtest
            gtest_main
            )
    add_test(run_tests run_tests)

elseif (CMAKE_BUILD_TYPE MATCHES Release)
    message("BUILD_TYPE -- TEST")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_FLAGS}")
    add_executable (${PROJECT}
            ${HEADERS}
            main.c
            ${SOURCES})

endif ()
target_include_directories(${PROJECT} PRIVATE "${PROJECT_SOURCE_DIR}")
