/*

\author         Oliver Blaser
\date           01.07.2021
\copyright      GNU GPLv3 - Copyright (c) 2021 Oliver Blaser

*/

#ifndef APP_H
#define APP_H

#include "wxHelper.h"

#include "main.h"

class App : public wxApp
{
public:
    App();
    ~App();

    bool OnInit();

private:
    frames::Main* mainForm = nullptr;
};

#endif // APP_H
