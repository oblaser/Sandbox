/*

author:     Oliver Blaser

date c:     21.10.2020
date e:     24.10.2020

*/

#ifndef _PROJECT_H_
#define _PROJECT_H_

#ifdef WIN32
#define PRJ_LINUX 0
#define PRJ_WIN32 1
#else
#define PRJ_LINUX 1
#define PRJ_WIN32 0
#endif

#ifdef _DEBUG
#define PRJ_DEBUG 1
#else
#define PRJ_DEBUG 0
#endif

#endif // _PROJECT_H_
