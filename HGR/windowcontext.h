#ifndef WINDOWCONTEXT_H
#define WINDOWCONTEXT_H

#include "WindowStates/abstractwindowstate.h"
#include "WindowStates/defaultwindowstate.h"

class AbstractWindow;

using namespace std;

class WindowContext
{
private:
    AbstractWindowState *currentState;
    AbstractWindow *window;

public:
    WindowContext( AbstractWindow *win );

    void setState( AbstractWindowState *state );
    void execute( Mat &cameraFeed );
    AbstractWindow *getWindow ( void );
};

#endif // WINDOWCONTEXT_H
