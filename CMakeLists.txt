cmake_minimum_required(VERSION 2.8.4)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    Server.cpp
    Server.h
    Worker.cpp
    Worker.h
    HttpHandler.cpp
    HttpHandler.h
    FileSystem.cpp
    FileSystem.h
    HttpResponse.cpp
    HttpResponse.h
    HttpRequest.cpp
    HttpRequest.h
    )

add_executable(Server ${SOURCE_FILES})