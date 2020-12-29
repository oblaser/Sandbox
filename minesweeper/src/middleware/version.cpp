/*!

\author         Oliver Blaser

\date           27.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#include "version.h"

util::Version::Version()
    : major(0), minor(0), revision(0)
{
}

util::Version::Version(int major, int minor, int revision)
    : major(major), minor(minor), revision(revision)
{
}

inline int util::Version::getMajor() const
{
    return major;
}

inline int util::Version::getMinor() const
{
    return minor;
}

inline int util::Version::getRevision() const
{
    return revision;
}

int* util::Version::toArray(int* dest) const
{
    *dest = major;
    *(dest + 1) = minor;
    *(dest + 2) = revision;

    return dest;
}

std::string util::Version::toString() const
{
    return std::to_string(major) + '.' + std::to_string(minor) + '.' + std::to_string(revision);
}

bool util::operator<(const Version& left, const Version& right)
{
    if (left.major > right.major) return false;
    if (left.major < right.major) return true;

    if (left.minor > right.minor) return false;
    if (left.minor < right.minor) return true;

    if (left.revision > right.revision) return false;
    if (left.revision < right.revision) return true;

    return false;
}

bool util::operator>(const Version& left, const Version& right)
{
    if (left.major > right.major) return true;
    if (left.major < right.major) return false;

    if (left.minor > right.minor) return true;
    if (left.minor < right.minor) return false;

    if (left.revision > right.revision) return true;
    if (left.revision < right.revision) return false;

    return false;
}

bool util::operator<=(const Version& left, const Version& right)
{
    return !(left > right);
}

bool util::operator>=(const Version& left, const Version& right)
{
    return !(left < right);
}

bool util::operator==(const Version& left, const Version& right)
{
    if ((left.major == right.major) &&
        (left.minor == right.minor) &&
        (left.revision == right.revision))
    {
        return true;
    }

    return false;
}

bool util::operator!=(const Version& left, const Version& right)
{
    return !(left == right);
}
