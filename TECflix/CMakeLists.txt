cmake_minimum_required(VERSION 3.14)
project(TECflix)

set(CMAKE_CXX_STANDARD 14)
FIND_PACKAGE(FLTK REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
find_package (Threads)

add_executable(TECflix main.cpp estructuras/LinkedList.h estructuras/Node.h objects/Movie.cpp objects/Movie.h libray/csv.h objects/movieManager.cpp objects/movieManager.h guiIncludes.h)
target_link_libraries (TECflix ${CMAKE_THREAD_LIBS_INIT})
FLTK_WRAP_UI(TECflix ui.fl)
TARGET_LINK_LIBRARIES(TECflix ${FLTK_LIBRARIES})
TARGET_LINK_LIBRARIES(TECflix ${OPENGL_LIBRARIES})
set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(TECflix ${CURL_LIBRARIES})