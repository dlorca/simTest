## ---------------------------------------------------------
##  simTest | app/CMakeLists.txt
##
##  CMake build script.
##   * Author: David Lorca
##   * Creation date: 05 - Feb - 2019
## ---------------------------------------------------------

add_executable(simTest simTest.cpp $<TARGET_OBJECTS:${CMAKE_PROJECT_NAME}>)
target_include_directories(simTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(simTest ${Geant4_LIBRARIES})
install(TARGETS simTest RUNTIME DESTINATION bin)
