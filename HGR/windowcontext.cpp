#include "windowcontext.h"
#include "Windows/mywindow.h"

WindowContext::WindowContext(MyWindow *win )
    : currentState(new DefaultWindowState()),
      window(win)
{
}

void WindowContext::setState(AbstractWindowState *state ) {
    this->currentState = state;
}

void WindowContext::execute(Mat &cameraFeed ) {
    currentState->execute( *this, cameraFeed );
}

MyWindow *WindowContext::getWindow( void ) {
    return window;
}
