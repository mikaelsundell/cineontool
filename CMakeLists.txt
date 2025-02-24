# Copyright 2022-present Contributors to the cineontool project.
# SPDX-License-Identifier: BSD-3-Clause
# https://github.com/mikaelsundell/cineontool

cmake_minimum_required (VERSION 3.23)
set (project_name "cineontool")

project ("${project_name} project")

find_package (RawToAces CONFIG REQUIRED)

add_executable (${project_name} "cineontool.cpp")
target_link_libraries (${project_name}
    PRIVATE
        RawToAces::RawToAces_util2
)

set_property (TARGET ${project_name} PROPERTY CXX_STANDARD 14)

add_custom_command (
    TARGET ${project_name}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts
        $<TARGET_FILE_DIR:${project_name}>/fonts
)

add_custom_command (
    TARGET ${project_name}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${project_name}>/resources
)

install (TARGETS ${project_name}
    RUNTIME DESTINATION bin
)

install (DIRECTORY ${CMAKE_SOURCE_DIR}/fonts
    DESTINATION bin
)

install (DIRECTORY ${CMAKE_SOURCE_DIR}/resources
    DESTINATION bin
)
