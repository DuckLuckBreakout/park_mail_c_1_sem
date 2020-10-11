cmake_minimum_required(VERSION 3.17)
set(PROJECT iz_1)
project(${PROJECT})
set(CMAKE_CXX_STANDARD 14)

################################
# Files
set (HEADERS
        Errors/error_codes.h
        Errors/error_message.h
        ExchangeOfCurrency/Currency.h
        ExchangeOfCurrency/CurrencyPair.h
        ExchangeOfCurrency/ArrayOfCurrencies.h
        ExchangeOfCurrency/Offer.h
        ExchangeOfCurrency/ArrayOfOffers.h
        ExchangeOfCurrency/CurrencyExchangeRates.h
        TaskManager/task_manager.h)

set (SOURCES
        Errors/error_message.c
        ExchangeOfCurrency/CurrencyPair.c
        ExchangeOfCurrency/ArrayOfCurrencies.c
        ExchangeOfCurrency/Offer.c
        ExchangeOfCurrency/ArrayOfOffers.c
        ExchangeOfCurrency/CurrencyExchangeRates.c
        TaskManager/task_manager.c)


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
