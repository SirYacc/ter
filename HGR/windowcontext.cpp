#include "windowcontext.h"
#include "Windows/abstractwindow.h"

WindowContext::WindowContext(AbstractWindow *win )
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

AbstractWindow *WindowContext::getWindow( void ) {
    return window;
}
