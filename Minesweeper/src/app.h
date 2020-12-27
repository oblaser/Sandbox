/*!

\author         Oliver Blaser

\date           21.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#ifndef _APP_H_
#define _APP_H_

#include "forms/wxHelper.h"

#include "forms/main.h"

class app : public wxApp
{
public:
    app();
    ~app();

    virtual bool OnInit();

private:
    forms::main* mainForm = nullptr;
};

#endif // _APP_H_
