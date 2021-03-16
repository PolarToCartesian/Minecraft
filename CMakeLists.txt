CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

PROJECT(Minecraft VERSION 0.0.1)

SET(CMAKE_CXX_STANDARD		      17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

FIND_PACKAGE(Vulkan REQUIRED FATAL_ERROR)

ADD_DEFINITIONS(-DUNICODE -D_UNICODE)

FILE(GLOB_RECURSE MinecraftCommon_SRC
    "${PROJECT_SOURCE_DIR}/common/*.h"
    "${PROJECT_SOURCE_DIR}/common/*.hpp"
    "${PROJECT_SOURCE_DIR}/common/*.cpp"
    "${PROJECT_SOURCE_DIR}/common/*.c"
)

FILE(GLOB_RECURSE MinecraftClient_SRC
	"${PROJECT_SOURCE_DIR}/client/*.h"
	"${PROJECT_SOURCE_DIR}/client/*.hpp"
	"${PROJECT_SOURCE_DIR}/client/*.cpp"
	"${PROJECT_SOURCE_DIR}/client/*.c"
)

FILE(GLOB_RECURSE MinecraftServer_SRC
	"${PROJECT_SOURCE_DIR}/server/*.h"
	"${PROJECT_SOURCE_DIR}/server/*.hpp"
	"${PROJECT_SOURCE_DIR}/server/*.cpp"
	"${PROJECT_SOURCE_DIR}/server/*.c"
)

ADD_EXECUTABLE(MinecraftClient "${MinecraftClient_SRC}" "${MinecraftCommon_SRC}")
ADD_EXECUTABLE(MinecraftServer "${MinecraftServer_SRC}" "${MinecraftCommon_SRC}")

SET(PNG_BUILD_ZLIB    ON)
SET(ZLIB_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/dependencies/zlib" "${CMAKE_CURRENT_BINARY_DIR}/dependencies/zlib")

ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/dependencies/zlib")
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/dependencies/glfw")
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/dependencies/plog")
ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/dependencies/libpng")

ADD_DEPENDENCIES(MinecraftClient zlib png_static glfw plog)
ADD_DEPENDENCIES(MinecraftServer zlib png_static glfw plog)

TARGET_LINK_LIBRARIES(MinecraftClient zlib png_static glfw "${Vulkan_LIBRARIES}")
TARGET_LINK_LIBRARIES(MinecraftServer zlib png_static glfw "${Vulkan_LIBRARIES}")

SET(Minecraft_Additional_Include_Dirs
    "${CMAKE_CURRENT_BINARY_DIR}/dependencies/glfw" 
	"${CMAKE_CURRENT_BINARY_DIR}/dependencies/zlib"
	"${CMAKE_CURRENT_BINARY_DIR}/dependencies/libpng"

    "${PROJECT_SOURCE_DIR}/"
	"${PROJECT_SOURCE_DIR}/dependencies/Vulkan-Headers/include"
	"${PROJECT_SOURCE_DIR}/dependencies/zlib"
	"${PROJECT_SOURCE_DIR}/dependencies/libpng"
	"${PROJECT_SOURCE_DIR}/dependencies/plog/include"
	"${PROJECT_SOURCE_DIR}/dependencies/mathfu/include"
)

TARGET_INCLUDE_DIRECTORIES(MinecraftClient PUBLIC "${Minecraft_Additional_Include_Dirs}")
TARGET_INCLUDE_DIRECTORIES(MinecraftServer PUBLIC "${Minecraft_Additional_Include_Dirs}")

SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MinecraftClient)

SET_PROPERTY(TARGET MinecraftClient PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
SET_PROPERTY(TARGET MinecraftServer PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")