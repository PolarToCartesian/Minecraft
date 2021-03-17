#pragma once

#define VULKAN_HPP_NO_EXCEPTIONS     // vulkan.hpp
#define VULKAN_HPP_ASSERT			 // vulkan.hpp

#ifdef _WIN32
#	define VK_USE_PLATFORM_WIN32_KHR // vulkan.hpp
#	define GLFW_EXPOSE_NATIVE_WIN32  // glfw3native.h
#endif

#ifdef _MSC_VER
#   define FORCE_INLINE __forceinline
#	define _CRT_SECURE_NO_WARNINGS
#else
#   define FORCE_INLINE inline
#endif

#include <array>
#include <limits>
#include <vector>
#include <cstdio>
#include <memory>
#include <thread>
#include <chrono>
#include <sstream>
#include <fstream>
#include <optional>
#include <iostream>
#include <algorithm>
#include <functional>

#include <zlib.h>

#include <png.h>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

#include <vulkan/vulkan.hpp>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <mathfu/vector.h>
#include <mathfu/matrix.h>
#include <mathfu/quaternion.h>

#define MINECRAFT_VERSION VK_MAKE_VERSION(0, 0, 0)

#define REPORT_ERROR   PLOG_ERROR
#define REPORT_WARNING PLOG_WARNING
#define REPORT_RELEASE PLOG_INFO
#define REPORT_DEBUG   PLOG_DEBUG

#ifdef _WIN32
#	define DISPLAY_BOX_ERROR(msg) MessageBoxA(NULL, msg, "Minecraft Error: ", MB_ICONERROR);
#else
#	define DISPLAY_BOX_ERROR(msg)
#endif

#define ABORT(msg)            \
	std::cerr << msg << '\n'; \
	REPORT_ERROR << msg;      \
	DISPLAY_BOX_ERROR(msg);   \
	std::exit(-1);            \

#define ASSERT(predicate, msg)  \
    if (!(predicate)) {         \
		ABORT(msg);             \
    }

#ifdef _DEBUG
#	define DO_DEBUG(x) x
#else
#	define DO_DEBUG(x) 
#endif

namespace mc {

	typedef float         f32; static_assert(sizeof(f32) == 4, "f32 is not 32 bits");
	typedef double        f64; static_assert(sizeof(f64) == 8, "f64 is not 64 bits");
	typedef std::int8_t   i8;  static_assert(sizeof(i8)  == 1, "i8  is not 8  bits");
	typedef std::int16_t  i16; static_assert(sizeof(i16) == 2, "i16 is not 16 bits");
	typedef std::int32_t  i32; static_assert(sizeof(i32) == 4, "i32 is not 32 bits");
	typedef std::int64_t  i64; static_assert(sizeof(i64) == 8, "i64 is not 64 bits");
	typedef std::uint8_t  u8;  static_assert(sizeof(u8)  == 1, "u8  is not 8  bits");
	typedef std::uint16_t u16; static_assert(sizeof(u16) == 2, "u16 is not 16 bits");
	typedef std::uint32_t u32; static_assert(sizeof(u32) == 4, "u32 is not 32 bits");
	typedef std::uint64_t u64; static_assert(sizeof(u64) == 8, "u64 is not 64 bits");

}; // namespace mc