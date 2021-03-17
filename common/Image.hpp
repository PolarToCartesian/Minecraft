#pragma once

#include <common/Header.hpp>

namespace mc {

    enum class Image2DFileType : mc::u8 {
        PNG, JPG
    }; // enum class Image2DFileType

    template <typename T>
    class Image2D {
    protected:
        using PIX_T = mathfu::Vector<T, 4>;

        mc::u32 m_width = 0, m_height = 0;

        std::vector<PIX_T> m_pixels;

    public:
        FORCE_INLINE Image2D() noexcept = default;

        FORCE_INLINE Image2D(const mc::u32 width, const mc::u32 height) noexcept
            : m_width(width), m_height(height), m_pixels(static_cast<u64>(width)*height)
        {  }

        FORCE_INLINE mc::u32 GetWidth()  const noexcept { return this->m_width;  }
        FORCE_INLINE mc::u32 GetHeight() const noexcept { return this->m_height; }

        FORCE_INLINE const PIX_T* Data() const noexcept { return this->m_pixels.data(); }
        FORCE_INLINE       PIX_T* Data()       noexcept { return this->m_pixels.data(); }

        FORCE_INLINE       PIX_T& operator[](const mc::u64 i)       noexcept { return this->m_pixels[i]; }
        FORCE_INLINE const PIX_T& operator[](const mc::u64 i) const noexcept { return this->m_pixels[i]; }

        FORCE_INLINE       PIX_T& operator()(const mc::u32 x, const mc::u32 y)       noexcept { return this->m_pixels[y * this->m_width + x]; }
        FORCE_INLINE const PIX_T& operator()(const mc::u32 x, const mc::u32 y) const noexcept { return this->m_pixels[y * this->m_width + x]; }
    }; // class Image

    class Image2Du8 : public Image2D<mc::u8> {
    public:
        Image2Du8(const char* const filename, const mc::Image2DFileType& filetype, bool& bError) noexcept;
    }; // class Image2Du8

}; // namespace mc