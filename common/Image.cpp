#include <common/Image.hpp>

namespace mc {

    Image2Du8::Image2Du8(const char* const filename, const mc::Image2DFileType& filetype, bool& bError) noexcept {
        FILE* fp = std::fopen(filename, "rb");

        if (!fp) goto error;

        switch (filetype) {
        case mc::Image2DFileType::PNG:
        {
            // Check Signature
            u64 pngSignature; std::fread(&pngSignature, 1, 8, fp);
            if (!png_check_sig((png_const_bytep)(&pngSignature), 8)) goto error;

            png_struct* png_read = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            if (!png_read) goto error;

            png_info* png_info = png_create_info_struct(png_read);
            if (!png_info) { png_destroy_read_struct(&png_read, &png_info, NULL); goto error; }

            setjmp(png_jmpbuf(png_read));
            png_init_io(png_read, fp);
            png_set_sig_bytes(png_read, 8);
            png_read_info(png_read, png_info);

            // Get the right buffer layout
            const png_byte colorType = png_get_color_type(png_read, png_info);
            const png_byte bitDepth  = png_get_bit_depth (png_read, png_info);

            if (bitDepth == 16)
                png_set_strip_16(png_read);

            if (colorType == PNG_COLOR_TYPE_PALETTE)
                png_set_palette_to_rgb(png_read);
            
            if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
                png_set_expand_gray_1_2_4_to_8(png_read);
            
            if (colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_PALETTE)
                png_set_filler(png_read, 0xFF, PNG_FILLER_AFTER);
            
            if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
                png_set_gray_to_rgb(png_read);

            png_read_update_info(png_read, png_info);

            // Fetch image propreties and fetch witdh & height
            this->m_width  = png_get_image_width(png_read, png_info);
            this->m_height = png_get_image_height(png_read, png_info);
            this->m_pixels.resize((u64)this->m_width * this->m_height);
            
            // Read image to buffer
            std::vector<png_bytep> rowPointers(this->m_height);
            for (u32 i = 0; i < this->m_height; ++i)
                rowPointers[i] = reinterpret_cast<png_bytep>(this->m_pixels.data() + i * this->m_width);

            png_read_image(png_read, rowPointers.data());
            png_destroy_read_struct(&png_read, &png_info, NULL);
            break;
        }
        case mc::Image2DFileType::JPG:
        {
            goto error;
            break;
        }
        default:
        {
            goto error;
        }
        }

        //success:
            { bError = false; return; }

        error:
            { bError = true;  return; }
    }

}; // namespace mc