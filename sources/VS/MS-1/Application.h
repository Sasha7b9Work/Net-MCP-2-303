// 2022/04/27 11:10:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#define WIN32_LEAN_AND_MEAN
#include "wx/wx.h"


class Application : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE;

    static Application *Self() { return self; }

    void Update();

private:
    void Init();

    static Application *self;
};
