//==============================================================================
#include "CApp.h"

//==============================================================================
CApp::CApp()
{
    Surf_Display = NULL;
    isTyping = false;
    Running = true;
}

//------------------------------------------------------------------------------
int CApp::OnExecute()
{
    if(OnInit() == false)
    {
        return -1;
    }

    SDL_Event Event;

    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    if(OnCleanup() == false)
    {
        return -2;
    }

    return 0;
}

//==============================================================================
int main(int argc, char* argv[])
{
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
