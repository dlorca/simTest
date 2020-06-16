## ---------------------------------------------------------
##  simTest | src/CMakeLists.txt
##
##  CMake build script.
##   * Author: David Lorca
##   * Creation date: 02 - Feb - 2020
## ---------------------------------------------------------

SET(SRC   DetectorConstruction.cpp
          EventAction.cpp
          PrimaryGeneration.cpp
          RunAction.cpp
          SteppingAction.cpp)

add_library(${CMAKE_PROJECT_NAME} OBJECT ${SRC})
