cmake_minimum_required(VERSION 3.17)
set(PROJECT iz_2)
project(${PROJECT})
set(CMAKE_CXX_STANDARD 14)

################################
# Files
set (SOURCES
        Errors/error_message.c
        Recommendation_system/int_array.c
        Recommendation_system/data.c
        Recommendation_system/objects_rating.c
        Task_manager/task_manager.c)


##############################
# Release
set(RELEASE_FLAGS " -Wall -pthread")

# Debug
set(DEBUG_FLAGS " -Wall -pedantic -g3 -pthread")


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")


add_compile_options(-pthread)

option(STATIC "Static library" ON)
option(SHARED "Shared library" ON)

if (STATIC MATCHES ON)
    add_library(parallel STATIC
            Recommendation_system/parallel.c
            Recommendation_system/parallel.h
            
            Recommendation_system/objects_rating.c
            )
    target_include_directories(parallel PRIVATE "${PROJECT_SOURCE_DIR}")
endif()

if (SHARED MATCHES ON)
    include(GenerateExportHeader)
    add_library(lineal SHARED
            Recommendation_system/lineal.c
            Recommendation_system/lineal.h
            Recommendation_system/objects_rating.c
            )
    target_include_directories(lineal PRIVATE "${PROJECT_SOURCE_DIR}")
endif()



#Choice target
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("BUILD_TYPE -- DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS}")
    add_executable (${PROJECT}
            main.c
            ${SOURCES})

    target_link_libraries(${PROJECT}
            parallel lineal)

elseif (CMAKE_BUILD_TYPE MATCHES Test)
    message("BUILD_TYPE -- TEST")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_FLAGS} -g -Wall -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RELEASE_FLAGS} -g -fprofile-arcs -ftest-coverage")

    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")


    include(DownloadProject.cmake)
    download_project(PROJ                googletest
            GIT_REPOSITORY      https://github.com/google/googletest.git
            GIT_TAG             master
            ${UPDATE_DISCONNECTED_IF_AVAILABLE}
            )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

    add_executable(${PROJECT}
            Tests/test.cpp
            Tests/unit_tests.cpp
            ${SOURCES})

    target_link_libraries(${PROJECT}
            gtest
            gmock_main
           # gcov
            parallel lineal
            )
    add_test(run_tests run_tests)

elseif (CMAKE_BUILD_TYPE MATCHES Release)
    message("BUILD_TYPE -- TEST")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_FLAGS}")
    add_executable (${PROJECT}
            main.c
            ${SOURCES})

endif ()
target_include_directories(${PROJECT} PRIVATE "${PROJECT_SOURCE_DIR}")
