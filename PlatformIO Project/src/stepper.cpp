#include <stepper.h>
//                               1   3   2   4
AccelStepper stepper1(Fullstep, 12, 13, 21, 17);

void init_stepper() {
  stepper1.setMaxSpeed(1000);     // set the maximum speed
  stepper1.setSpeed(200);         // set initial speed
  stepper1.setAcceleration(50);   // set acceleration
  stepper1.setCurrentPosition(0); // set position
}

void open_door(){
    float moveRev = 60*SteppDegree;
    stepper1.moveTo(-moveRev);
    stepper1.runToPosition();
}

void close_door(){
    float moveRev = 60*SteppDegree;
    stepper1.moveTo(moveRev);
    stepper1.runToPosition();
}