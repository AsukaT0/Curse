cmake_minimum_required(VERSION 3.12)
project(MyLibrary)
set(CMAKE_CXX_STANDARD 23)
set(SOURCES
        src/File/File.cpp
        src/File/Archiver.cpp
        src/File/ConfigLoader.cpp src/Utils/Utils.cpp src/Utils/Stopwatch.cpp src/Controllers/SqliteController.cpp include/Utils/SwitcherString.h src/Net/Client/SClient.cpp src/Net/Server/SServer6.cpp src/Net/NetUtils.cpp include/Net/NetUtils.h)
add_library(MyLibrary SHARED ${SOURCES})


find_package (SQLite3)
if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (${PROJECT_NAME}  ${SQLITE3_LIBRARIES} -lsqlite3)
endif (SQLITE3_FOUND)

find_package(LibArchive REQUIRED)
include_directories(${LIBARCHIVE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBARCHIVE_LIBRARIES} -larchive )

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} -lboost_filesystem )

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})