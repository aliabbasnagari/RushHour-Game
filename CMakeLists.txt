cmake_minimum_required(VERSION 3.10)
project(Rushhour CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(UNIX AND NOT APPLE)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

add_executable(Rushhour game.cpp util.cpp)

target_include_directories(Rushhour PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(Rushhour PRIVATE
    OpenGL::GL
    GLUT::GLUT
    GLEW::GLEW
)

if(UNIX AND NOT APPLE)
    # Older FindGLUT modules don't transitively pull in X11, which GLUT
    # needs at link time (undefined references like XGetWindowAttributes).
    find_package(X11 REQUIRED)
    target_link_libraries(Rushhour PRIVATE ${X11_LIBRARIES})
endif()

# highscores.txt is read/written next to the executable's working directory.
configure_file(${CMAKE_SOURCE_DIR}/highscores.txt ${CMAKE_BINARY_DIR}/highscores.txt COPYONLY)

if(WIN32)
    # Prebuilt runtime DLLs shipped in the repo (no system package on Windows).
    foreach(dll freeglut.dll glew32.dll)
        add_custom_command(TARGET Rushhour POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_SOURCE_DIR}/${dll}" "$<TARGET_FILE_DIR:Rushhour>"
        )
    endforeach()
endif()

add_custom_target(run
    COMMAND Rushhour
    DEPENDS Rushhour
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    USES_TERMINAL
)
