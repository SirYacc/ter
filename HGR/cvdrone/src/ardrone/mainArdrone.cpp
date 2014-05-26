#include "ardrone.h"
// --------------------------------------------------------------------------
// main(Number of arguments, Argument values)
// Description : This is the entry point of the program.
// Return value : SUCCESS:0 ERROR:-1
// --------------------------------------------------------------------------

using namespace std;

int runArdrone(void)
{
    // AR.Drone class
    ARDrone ardrone;

    // Initialize
    if (!ardrone.open()) {
        printf("Failed to initialize.\n");
        return -1;
    }

    // Battery
    battery = ardrone.getBatteryPercentage();

    int tmpOrder = -99;
    int nbLabelPos = 8;
    int occLabelPos[nbLabelPos];
    list<int> listOrder(5,-1);


float vx = 0.0, vy = 0.0, vz = 0.0, vr = 0.0;

    while (1) {
        usleep(33000);

        imgFromKarmen = ardrone.getImage();

        battery = ardrone.getBatteryPercentage();
        tmpOrder = -99;

        for (int i = 0; i < nbLabelPos; i++)
            occLabelPos[i] = 0;

        // Key input
        //       int key = cvWaitKey(0);
        //        if (key == 0x1b) break; //TODO

        // Get an image

        // Move
        vx = 0.0;
        vy = 0.0;
        vz = 0.0;
        vr = 0.0;

        if(order == 100){
            orderName  = "Land";
            ardrone.landing();   // Land
            newOrder = false;
        }
        else{
            if(newOrder){
                newOrder = false;
                listOrder.pop_front();
                listOrder.push_back(order);
            }

            for (list<int>::iterator it=listOrder.begin(); it != listOrder.end(); ++it){
                if(*it >= 0 && *it < nbLabelPos)
                    occLabelPos[*it]++;
            }

            for (int i = 0; i < nbLabelPos; i++){
                if(occLabelPos[i] >= 3){
                    tmpOrder = i;
                    break;
                }
            }


            switch (tmpOrder) {
            case 0 :
                orderName = "Up";
                vz = 1.0;
                break;
            case 1 :
                orderName  = "Down";
                vz = -1.0;
                break;
            case 2 :
                orderName  = "Left";
                vy = 1.0;
                break;
            case 3 :
                orderName  = "Right";
                vy = -1.0;
                break;
            case 4 :
                orderName  = "Land";
                ardrone.landing();   // Land
                break;
            case 5 :
                if (ardrone.onGround()){
                    orderName  = "Take Off";
                    ardrone.takeoff();    // Take-off
                }
                break;
            case 6 :
                orderName  = "Forward";
                vx = 1.0;
                break;
            case 7 :
                orderName  = "Backward";
                vx = -1.0;
                break;
            default :
                orderName  = "Nothing";
                break;
            }

            ardrone.move3D(vx, vy, vz, vr);
            vx = 0.0;
            vy = 0.0;
            vz = 0.0;
            vr = 0.0;
        }
    }
    // See you
    ardrone.close();

    return 0;
}
