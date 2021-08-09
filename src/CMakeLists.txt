cmake_minimum_required(VERSION 3.10)

project(PNP)

set(camke_cxx_flags "${camke_cxx_flags} -std=c++11")


find_package(OpenCV REQUIRED)

# show the message of OpenCV
message(STATUS "OpenCV library status:")
message(STATUS "    version: 	${OpenCV_VERSION}")
message(STATUS "    headers: 	${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libraries: 	${OpenCV_LIBS}")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/contours_tree)
include_directories(${PROJECT_SOURCE_DIR}/displace)
include_directories(${PROJECT_SOURCE_DIR}/find_centre)
include_directories(${PROJECT_SOURCE_DIR}/hsv_Color_pre)
include_directories(${PROJECT_SOURCE_DIR}/kalmanFliter)
include_directories(${PROJECT_SOURCE_DIR}/solvepnp)

SET( PROJECT_BINARY_DIR  ${PROJECT_SOURCE_DIR}/../build)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

aux_source_directory(./ DIR_SRC)

add_executable(PNP ${DIR_SRC})

target_link_libraries(PNP ${OpenCV_LIBS})
target_link_libraries(PNP HSV)
target_link_libraries(PNP findContours)
target_link_libraries(PNP Dis)
target_link_libraries(PNP contours_tree)
target_link_libraries(PNP KALMAN)
target_link_libraries(PNP pnp)