/*!

\author         Oliver Blaser

\date           27.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _MIDDLEWARE_VERSION_H_
#define _MIDDLEWARE_VERSION_H_

#include <string>

namespace util
{
    class Version
    {
    public:
        Version();
        Version(int major, int minor, int revision);

        inline int getMajor() const;
        inline int getMinor() const;
        inline int getRevision() const;

        int* toArray(int* dest) const;
        std::string toString() const;

        friend bool operator<(const Version& left, const Version& right);
        friend bool operator>(const Version& left, const Version& right);
        friend bool operator<=(const Version& left, const Version& right);
        friend bool operator>=(const Version& left, const Version& right);
        friend bool operator==(const Version& left, const Version& right);
        friend bool operator!=(const Version& left, const Version& right);

    private:
        int major;
        int minor;
        int revision;
    };
}

#endif // _MIDDLEWARE_VERSION_H_
