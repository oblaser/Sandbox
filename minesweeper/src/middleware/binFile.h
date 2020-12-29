/*!

\author         Oliver Blaser

\date           28.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#include <cstdint>
#include <string>

namespace middleware
{
    class binFile
    {
    public:
        binFile() = delete;
        binFile(const binFile& bf) = delete;

        //! @brief Creates an instance with a specified filename
        //! @param file The filename
        binFile(const std::string& file);
        
        ~binFile();

        std::string getFileName() const;

        //! @brief Reads the file content in to the data buffer
        //! @param data Pointer to buffer
        //! @param dataLen Size of the data buffer
        //! @return Number of bytes read or 0 on io exception
        size_t read(uint8_t* data, size_t dataLen) const;

        //! @brief Writes a byte buffer to the file
        //! @param data Pointer to buffer
        //! @param writeNBytes Number of bytes to write
        //! @return Non zero on error
        int write(const uint8_t* data, size_t writeNBytes) const;

    private:
        std::string fileName;
    };
}
