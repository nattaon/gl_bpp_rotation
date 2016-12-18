cmake_minimum_required(VERSION 2.8)
project( OpenGLBpp )

if(CMAKE_CONFIGURATION_TYPES)
    message("Multi-configuration generator")
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" 
	CACHE STRING "My multi config types" FORCE)
else()
    message("Single-configuration generator")
endif()

# Qt library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package (VTK REQUIRED) #for QT5_WRAP_CPP command 

# OpenGL & GLEW library
find_package(OpenGL)
#find_package(GLUT REQUIRED)

file(GLOB  project_SOURCES *.cpp)
file(GLOB  project_HEADERS *.h)

file(COPY "glut32.lib" DESTINATION "./")

QT5_WRAP_CPP (project_HEADERS_MOC   mainwindow.h glwidget.h) #Q_OBJECT
QT5_WRAP_UI  (project_FORMS_HEADERS mainwindow.ui)

# executable
ADD_EXECUTABLE  (OpenGLBpp 
${project_SOURCES} 
${project_HEADERS} 
${project_FORMS_HEADERS} 
${project_HEADERS_MOC})
#include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
qt5_use_modules(OpenGLBpp Widgets OpenGL)
target_link_libraries(OpenGLBpp ${QT_LIBRARIES} ${OPENGL_LIBRARIES})# 


