# Copyright (c) 2017-2018 Serguei Kalentchouk et al. All rights reserved.
# Use of this source code is governed by an MIT license that can be found in the LICENSE file.
cmake_minimum_required(VERSION 3.9)

# Define project
project(input-form-dialog)

# Set properties
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

# To find Qt, add the installation prefix of Qt5 to CMAKE_PREFIX_PATH or set Qt5_DIR
# to a directory containing one of the above files.
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Create library target
add_library(InputFormDialog SHARED src/InputFormDialog.h src/InputFormDialog.cpp)
target_link_libraries(InputFormDialog Qt5::Core Qt5::Widgets)
