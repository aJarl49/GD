cmake_minimum_required(VERSION 3.26)
project(Heartburner LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(WINDOWS_LIBRARIES winmm)
set(DLL_NAME ${PROJECT_NAME}_game)
set(DIR_ASSETS_ORIGIN ${CMAKE_SOURCE_DIR}/assets)
set(DIR_ASSETS_DESTINATION $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
# Flag .EXE specific files
set(EXE_EXCLUSIVE
${CMAKE_SOURCE_DIR}/src/main.cpp
)
set(SHARED_RESOURCES
${CMAKE_SOURCE_DIR}/src/image.cpp
${CMAKE_SOURCE_DIR}/src/arena.cpp
)
set (SHARED_LIB_NAME ${PROJECT_NAME}_common)
# Create the file references
file(GLOB_RECURSE LIB_FILES "${CMAKE_SOURCE_DIR}/lib/*.lib")
file(GLOB_RECURSE DLL_FILES "${CMAKE_SOURCE_DIR}/lib/*.dll")
file(GLOB_RECURSE DLL_EXCLUSIVE "src/*.cpp")
list(REMOVE_ITEM DLL_EXCLUSIVE ${EXE_EXCLUSIVE})
#LIBRARY
add_library(${SHARED_LIB_NAME} STATIC ${SHARED_RESOURCES})
target_include_directories(${SHARED_LIB_NAME} PRIVATE include)
# EXE
add_executable(${PROJECT_NAME} ${EXE_EXCLUSIVE})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} 
PRIVATE 
${LIB_FILES}
${WINDOWS_LIBRARIES}
${SHARED_LIB_NAME})
# GAME DLL
add_library(${DLL_NAME} SHARED ${DLL_EXCLUSIVE})
target_include_directories(${DLL_NAME} PRIVATE include)
target_link_libraries(${DLL_NAME} 
PRIVATE 
${LIB_FILES}
${SHARED_LIB_NAME})
# Copy assets
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${DIR_ASSETS_ORIGIN} ${DIR_ASSETS_DESTINATION} VERBATIM
)
# Copy DLLs
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
${DLL_FILES}
"$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)
