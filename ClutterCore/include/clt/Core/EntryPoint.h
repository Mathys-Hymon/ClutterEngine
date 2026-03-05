#pragma once
#include "Application/Application.h"

#ifdef CLUTTER_PLATFORM_WINDOWS

extern clt::Application* clt::CreateApplication(clt::ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    clt::ApplicationCommandLineArgs args;
    args.Count = argc;
    args.Args = argv;

    // Creation
    auto app = clt::CreateApplication(args);

    // Loop
    app->Run();

    // Destructor
    delete app;

    return 0;
}

#endif