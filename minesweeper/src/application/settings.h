/*!

\author         Oliver Blaser

\date           28.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _APPLICATION_SETTINGS_H_
#define _APPLICATION_SETTINGS_H_

#include <string>

namespace application
{
    class Settings
    {
    public:
        Settings();
        ~Settings();

        int getFieldWidth() const;
        int getFieldHeight() const;
        float getRelNMines() const;

        void setFieldWidth(int value);
        void setFieldHeight(int value);
        void setRelNMines(float value);

        friend bool operator==(const Settings& left, const Settings& right);
        friend bool operator!=(const Settings& left, const Settings& right);

    private:
        int fieldWidth;
        int fieldHeight;
        float relNMines;
    };

    namespace settingsFile
    {
        const std::string defaultFileName = "settings.mswdat";

        //! @brief Reads the file in to the object.
        //! @param fileName 
        //! @param[out] settings Object to write the file data into. If the file read fails, the default ctor is applied to the object.
        //! @return Zero on success.
        int load(const std::string& fileName, Settings& settings);

        //! @brief Writes the object to the file.
        //! @param fileName 
        //! @param settings 
        //! @return Zero on success.
        int save(const std::string& fileName, const Settings& settings);
    }
}

#endif // _APPLICATION_SETTINGS_H_
