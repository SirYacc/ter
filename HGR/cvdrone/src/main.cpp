#include "ardrone/ardrone.h"

// --------------------------------------------------------------------------
// main(Number of arguments, Argument values)
// Description  : This is the entry point of the program.
// Return value : SUCCESS:0  ERROR:-1
// --------------------------------------------------------------------------
int main(int argc, char **argv)
{
    // AR.Drone class
    ARDrone ardrone;

    // Initialize
    if (!ardrone.open()) {
        printf("Failed to initialize.\n");
        return -1;
    }

    // Battery
    printf("Battery = %d%%\n", ardrone.getBatteryPercentage());

    // Instructions
    printf("***************************************\n");
    printf("*       CV Drone sample program       *\n");
    printf("*           - How to Play -           *\n");
    printf("***************************************\n");
    printf("*                                     *\n");
    printf("* - Controls -                        *\n");
    printf("*    'Space' -- Takeoff/Landing       *\n");
    printf("*    'Up'    -- Move forward          *\n");
    printf("*    'Down'  -- Move backward         *\n");
    printf("*    'Left'  -- Turn left             *\n");
    printf("*    'Right' -- Turn right            *\n");
    printf("*    'Q'     -- Move upward           *\n");
    printf("*    'A'     -- Move downward         *\n");
    printf("*                                     *\n");
    printf("* - Others -                          *\n");
    printf("*    'C'     -- Change camera         *\n");
    printf("*    'Esc'   -- Exit                  *\n");
    printf("*                                     *\n");
    printf("***************************************\n\n");

    while (1) {
        // Key input
        int key = cvWaitKey(33);
printf(" key : %d \n",key);
        if (key == 0x1b) break;

        // Update
        if (!ardrone.update()) break;

        // Get an image
        IplImage *image = ardrone.getImage();

        // Take off / Landing 
        if (key == 1048608) {

            if (ardrone.onGround()) ardrone.takeoff();
            else                    ardrone.landing();
        }

        // Move
        double vx = 0.0, vy = 0.0, vz = 0.0, vr = 0.0;
        if (key == 1113939) vx =  1.0;
        if (key == 1113937) vx = -1.0;
        if (key == 0x250000) vr =  1.0;
        if (key == 0x270000) vr = -1.0;
        if (key == 'q')      vz =  1.0;
        if (key == 'a')      vz = -1.0;
        ardrone.move3D(vx, vy, vz, vr);

        // Change camera
        static int mode = 0;
        if (key == 'c') ardrone.setCamera(++mode%4);

        // Display the image
        cvShowImage("camera", image);
    }

    // See you
    ardrone.close();

    return 0;
}
