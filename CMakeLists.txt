cmake_minimum_required(VERSION 3.16)

project(ArkPaintingConverter VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5 components
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)

# Enable Qt's MOC (Meta-Object Compiler)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/drawingarea.cpp
    src/colorchooser.cpp
    src/ditherbase.cpp
    src/floyd_steinberg.cpp
    src/jarvisjudiceninke.cpp
    src/sierra.cpp
)

# Header files
set(HEADERS
    src/mainwindow.h
    src/drawingarea.h
    src/colorchooser.h
    src/ditherbase.h
    src/matrix.h
    src/floyd_steinberg.h
    src/jarvisjudiceninke.h
    src/sierra.h
    src/tpainting.h
    src/config_path_manager.h
)

# UI files (if using Qt Designer)
set(UI_FILES
   src/mainwindow.ui
)

# Resource files (Qt resource system)
#set(RESOURCES
#   resources.qrc
#)

# External resource directories
set(RESOURCE_DIRS
    icons
    data
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
#    ${RESOURCES}
)

# Link Qt5 libraries
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)

# Linux-specific settings
if(UNIX AND NOT APPLE)
    # Set RPATH for shared libraries
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH TRUE
        INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
    )
    
    # Enable debug symbols in debug builds
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${PROJECT_NAME} PRIVATE -g)
    endif()
endif()

# Define resource installation paths
set(RESOURCE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}")

# Copy resource directories to build directory for development
foreach(RESOURCE_DIR ${RESOURCE_DIRS})
    if(EXISTS "${CMAKE_SOURCE_DIR}/${RESOURCE_DIR}")
        file(COPY "${CMAKE_SOURCE_DIR}/${RESOURCE_DIR}" 
             DESTINATION "${CMAKE_BINARY_DIR}")
    endif()
endforeach()

# Installation rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Install resource directories
foreach(RESOURCE_DIR ${RESOURCE_DIRS})
    if(EXISTS "${CMAKE_SOURCE_DIR}/${RESOURCE_DIR}")
        install(DIRECTORY "${CMAKE_SOURCE_DIR}/${RESOURCE_DIR}"
                DESTINATION "${RESOURCE_INSTALL_DIR}")
    endif()
endforeach()

# Install desktop entry file (for Linux desktop integration)
if(EXISTS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.desktop")
    install(FILES "${PROJECT_NAME}.desktop"
            DESTINATION share/applications)
endif()

# Install application icon
if(EXISTS "${CMAKE_SOURCE_DIR}/icons/${PROJECT_NAME}.xpm")
    install(FILES "icons/${PROJECT_NAME}.xpm"
            DESTINATION share/pixmaps)
endif()

# Create uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)
