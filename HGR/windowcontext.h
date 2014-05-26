#ifndef WINDOWCONTEXT_H
#define WINDOWCONTEXT_H

#include "WindowStates/abstractwindowstate.h"
#include "WindowStates/defaultwindowstate.h"

class MyWindow;

using namespace std;

class WindowContext
{
private:
    AbstractWindowState *currentState;
    MyWindow *window;

public:
    WindowContext( MyWindow *win );

    void setState( AbstractWindowState *state );
    void execute( Mat &cameraFeed );
    MyWindow *getWindow ( void );
};

#endif // WINDOWCONTEXT_H
