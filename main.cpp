#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor MotorGroup8MotorA = motor(PORT8, ratio18_1, true);
motor MotorGroup8MotorB = motor(PORT9, ratio18_1, false);
motor_group MotorGroup8 = motor_group(MotorGroup8MotorA, MotorGroup8MotorB);

motor Motor7 = motor(PORT7, ratio18_1, true);

motor MotorGroup10MotorA = motor(PORT10, ratio18_1, false);
motor MotorGroup10MotorB = motor(PORT11, ratio18_1, true);
motor_group MotorGroup10 = motor_group(MotorGroup10MotorA, MotorGroup10MotorB);

controller Controller1 = controller(primary);
motor LeftDriveSmart = motor(PORT18, ratio18_1, false);
motor RightDriveSmart = motor(PORT19, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 368.29999999999995, 330.2, mm, 1);




// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
#pragma endregion VEXcode Generated Robot Configuration

// Include the V5 Library
#include "vex.h"

/*
Motorgruop ten is the grabbers
Motorgroup 8 is the shooter
Moto7 seven is the track
*/
  
// Allows for easier use of the VEX Library
using namespace vex;

// Shooter sect
void startShooter() {
  MotorGroup8.spin(forward);
  Motor7.spin(forward, 30, volt);
}

void stopShooter() {
  MotorGroup8.stop();
  Motor7.stop();
}

// Toggle track func
/* static */ bool tracktogglebool = false;
void toggleTrack() {
  if (tracktogglebool == true) {
    Motor7.spin(forward);
    tracktogglebool = false;
    Controller1.rumble(rumbleShort);
  }

  else if (tracktogglebool == false) {
    Motor7.stop();
    tracktogglebool = true;
    Controller1.rumble(rumbleShort);
  }
}

void initControl() {
  // L1 is to start/stop shooter
  Controller1.ButtonL1.pressed(startShooter);
  Controller1.ButtonL1.released(stopShooter);

  // L2 is to toggle the track
  Controller1.ButtonL2.pressed(toggleTrack);
}

int main() {
  wait(15, msec);
  // post event registration

  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);

  // If this doesn't work move into the main loop
  initControl();

  // Start up main loop
  bool loop = true;
  while (loop) {}
}
