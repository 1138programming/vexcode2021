/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Jul 5 2020                                            */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    6, 10, 1, 20, 21
// LIntake              motor         12              
// VisionSensor         vision        13              
// Controller1          controller                    
// lLift             motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// ################################ DEFINE TASKS ###############################
int tMyTasks();
int tDrive();
int tPrintCPUScreen();
int tPrintControlScreen();

// Drive Functions
void fTurnLeft(double dDegrees, double dVelocity);
void fTurnRight(double dDegrees, double dVelocity);
void fPIDTurn(double dDegrees, double cU, double cD);

// Vision function
void fVision(int iObjectCase, int iTimeOut);
// General functions
void fResetAllMotors();

// Define Global Variables
double dDrivePwr = 1; // multiplier for drive speed
double dDriveTrq = 1; // multiplier for drive torque
double dDriveTurnPwr = 0.4; //multiplier for turning speed
bool bDriveBrake; // true if the usercontrol is breaking the drive

int iRangeFinderState; // use to control range finder task state
int iVisionState; // use to toggle vision assist on and off
int iVisionObject = 1; // determine which object to seek
int iVisionCenter = 158; // define center of vision sensor screen
int iVisionOffset = 15; // use to define vision sensor offset value

// ######################## Define Auton function #############################
int iAutoNum = 1;
void test();


/*---------------------------------------------------------------------------*/
/*                              Pre-Autonomous Task                          */
/*---------------------------------------------------------------------------*/
void pre_auton( void ){
  task StartPrintCPUScreenTak(tPrintCPUScreen);
  vexcodeInit();

  // set drive to 100%
  Drivetrain.setDriveVelocity(100, percent);
  Arm.setVelocity(75,percent); 
  Intake.setVelocity(75,percent); 
  Lift.setVelocity(100,percent); 

  // start auto tasks here
  task StartMyTasks(tMyTasks);  // Start My Tasks
  task StartDriveTask(tDrive);
  task StartPrintControlScreenTak(tPrintControlScreen);
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous Task                              */
/*---------------------------------------------------------------------------*/
void autonomous( void ){
  switch (iAutoNum){
    case 1:
      test();
    case 2:
      //function
    case 3:
      //function
    case 4:
      //function
    case 5:
      //function
    case 6:
      test();
      //function
  }
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/
void usercontrol( void ){
  // reset all motors velocity and torque
  fResetAllMotors();
  
  while (1){
// test Vision Sensor
    // if(Controller1.ButtonDown.pressing()){
    //   iVisionState =1;
    // }
    if(Controller1.ButtonRight.pressing()){
      if (iAutoNum == 6){
        iAutoNum = 1;
        vex::task::sleep(250);
      }
      else {
        iAutoNum++;
        vex::task::sleep(250);
      }
    }
    if(Controller1.ButtonUp.pressing()){
      if (iAutoNum == 1){
        test();
      }
      else if (iAutoNum == 2){
      }
      else if (iAutoNum == 3){
      }
      else if (iAutoNum == 4){
        //function
      }
      else if (iAutoNum == 5){
        //function
      }
      else if (iAutoNum == 6){
        test();
      }
    }

    // ################### Arm Control ###############################################
    if (abs(Controller1.Axis2.value())>5){
      Arm.spin(forward, 50, percent);
    }
    else if(Controller1.ButtonB.pressing()){
      Arm.spin(reverse, 50, percent);
    }
    else {
      Arm.stop(brake);
    }
    
    // ################### Intake Control ###############################################
    if(Controller1.ButtonL2.pressing()){
      Intake.spin(forward, 75, percent);
    }
    else if(Controller1.ButtonL1.pressing()){
      Intake.spin(reverse, 75, percent);
    }
    else {
      Intake.stop(brake);
    }

    // ################### Lift Control ###############################################
    if(Controller1.ButtonR1.pressing()){
      Lift.spin(forward, 100, percent);
      
    }
    else if(Controller1.ButtonR2.pressing()){
      Lift.spin(reverse, 100, percent);
    }
    else {
      Lift.stop(hold);
    }
    
    // Sleep for 25 msec to conserve resource
    vex::task::sleep(25);
  }
}

// ###################### DO NOT MODIFY  ##################################
int main(){ // Main will set up the competition functions and callbacks.
  pre_auton();
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );

  while(1){
    task::sleep(100);
  }    
}
// #########################################################################

// ###################### USER DEFINED TASKS ##################################
int tMyTasks(){ // Manage user automated tasks
  while (1){
    // ### Vision tasks ###    
    if (iVisionState == 1){
      switch (iVisionObject){
      case 1: // perform task if desire object is the first defined, which is orange
        VisionSensor.takeSnapshot(1);
    }
    // Turn robot to object
      if (VisionSensor.largestObject.exists){
        if (VisionSensor.largestObject.centerX > iVisionCenter + iVisionOffset){
          Drivetrain.turn(right);
        }
        else if (VisionSensor.largestObject.centerX < iVisionCenter + iVisionOffset){
          Drivetrain.setTurnVelocity(100, percent);
          Drivetrain.turn(left);
        }
        else{
          Drivetrain.setStopping(brake);
        }
      }
    }
    // Sleep for 25 milesec to free up resource for other tasks
    vex::task::sleep(25);
  }
}

// ######################## MANAGE DRIVE FUNCTIONS ################################## 
int tDrive(){
  while(1){ 
  // Activate drive motors
  if (abs(Controller1.Axis4.value())>5 || abs(Controller1.Axis3.value())>5){
    bDriveBrake = true;
    iVisionState = 10; // turns off vision code

    leftMotorA.spin(forward, ((Controller1.Axis4.value()*dDriveTurnPwr  +  Controller1.Axis3.value()))*dDrivePwr, percent);
    leftMotorB.spin(forward, ((Controller1.Axis4.value()*dDriveTurnPwr  +  Controller1.Axis3.value()))*dDrivePwr, percent);
    rightMotorA.spin(forward,((-Controller1.Axis4.value()*dDriveTurnPwr +  Controller1.Axis3.value()))*dDrivePwr, percent);
    rightMotorB.spin(forward, ((-Controller1.Axis4.value()*dDriveTurnPwr +  Controller1.Axis3.value()))*dDrivePwr, percent); 
    }
    else if (bDriveBrake == true){
      leftMotorA.stop(brake);
      leftMotorB.stop(brake);
      rightMotorA.stop(brake);
      rightMotorB.stop(brake);
    }

  vex::task::sleep(25);
  }
}


// ########################## CPU SCREEN PRINT ########################################
int tPrintCPUScreen(){
//  Brain.Screen.render(true,false); //enable double buffering for smoother drawing
int xTouchPos, yTouchPos;
int ilife = 0;
int iScreenNum = 0; // 0-Menu
  while (1){
    Brain.Screen.clearScreen();
    if (Brain.Screen.pressing() == true){
      xTouchPos = Brain.Screen.xPosition();
      yTouchPos = Brain.Screen.yPosition(); 
      if ( (xTouchPos>380) && (xTouchPos<430) && (yTouchPos<40)){
        ilife--;
      }
      else if ( (xTouchPos>430) && (yTouchPos<40) ){
        ilife++;
      }
    }
    if (iScreenNum == 0){
      Brain.Screen.drawRectangle(0, 0, 480, 40); Brain.Screen.drawRectangle(380, 0, 50, 40); Brain.Screen.drawRectangle(430, 0, 50, 40);
      Brain.Screen.setCursor(1,2); Brain.Screen.setFont(monoL); Brain.Screen.print("MENU"); 
      Brain.Screen.setCursor(1,27); Brain.Screen.print("<"); Brain.Screen.setCursor(1,31); Brain.Screen.print(">"); 
      Brain.Screen.setCursor(3,2); Brain.Screen.setFont(monoM); Brain.Screen.print("X Position: "); Brain.Screen.setCursor(3,14); Brain.Screen.print(xTouchPos); 
      Brain.Screen.setCursor(4,2); Brain.Screen.print("Y Position: "); Brain.Screen.setCursor(4,14); Brain.Screen.print(yTouchPos); 
      Brain.Screen.setCursor(5,2); Brain.Screen.print(iAutoNum); 
    }
    Brain.Screen.render();
    task::sleep(500);        
  }
}

// ########################## CONTROLLER SCREEN PRINT ########################################
int tPrintControlScreen(){
  inertial TurnGyroSmart = inertial(PORT21);
//  Brain.Screen.render(true,false); //enable double buffering for smoother drawing
  while (1){
    //                                                           12345678901234567890      
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1); Controller1.Screen.print(TurnGyroSmart.rotation(degrees)*1.015);    
    Controller1.Screen.setCursor(2,1);  
    Controller1.Screen.setCursor(3,7); Controller1.Screen.print(iAutoNum);
    // switch (iAutoNum){
    //   case 1:
    //     Controller1.Screen.print("Skills");
    //   case 2:
    //     Controller1.Screen.print("2");
    //   case 3:
    //     Controller1.Screen.print("3");
    //   case 4:
    //     Controller1.Screen.print("4");
    //   case 5:
    //     Controller1.Screen.print("5");
    //   case 6:
    //     Controller1.Screen.print("Test");
    // }
    task::sleep(1000);      
  }
}

// ########################## USER DEFINED FUNCTIONS ###################################
// Below are user defined functions to assist with auto and other activities

void fPIDDrive(double dInches){
  leftMotorA.resetRotation();
  leftMotorB.resetRotation();
  rightMotorA.resetRotation();
  rightMotorB.resetRotation();
  double currentInches = leftMotorA.rotation(rev)*4*3.14159265359;
  double error = dInches - currentInches; 
  double prevError; 
  double pC = 3; 
  double dC = 1; 
  int counter = 0; 
  int v1, feedForward; 
  if (error > 0) { 
    v1 = 12;
  }
  else {
    v1 = -12;
  }
  while (currentInches < 1 && currentInches > -1){
    currentInches = leftMotorA.rotation(rev)+leftMotorB.rotation(rev)+rightMotorA.rotation(rev)+rightMotorB.rotation(rev)*3.14159265359; 
    rightMotorB.spin(forward, v1, percent); 
    leftMotorA.spin(forward, v1, percent);
    leftMotorB.spin(forward, v1, percent);
    rightMotorA.spin(forward, v1, percent);
    vex::task::sleep(10);
  }
  while (counter <= 15){
    currentInches = leftMotorA.rotation(rev)+leftMotorB.rotation(rev)+rightMotorA.rotation(rev)+rightMotorB.rotation(rev)*3.14159265359; 
    if ((currentInches > (dInches - 0.5)) && (currentInches < (dInches + 0.5))){
      counter++;
    }
    else {
      counter = 0; 
    }
    if (error > 0) { 
      feedForward = 4;
    }
    else {
      feedForward = -4;
    }
    error = dInches - currentInches; 
    prevError = error; 
    leftMotorA.spin(forward, feedForward + ((error*pC) + (prevError-error)*dC), percent);
    leftMotorB.spin(forward, feedForward + ((error*pC) + (prevError-error)*dC), percent);
    rightMotorA.spin(forward, feedForward + ((error*pC) + (prevError-error)*dC), percent);
    rightMotorB.spin(forward, feedForward + ((error*pC) + (prevError-error)*dC), percent); 
    vex::task::sleep(10);
  }
  leftMotorA.stop(brake);
  leftMotorB.stop(brake);
  rightMotorA.stop(brake);
  rightMotorB.stop(brake);
}

void fPIDTurn(double dDegrees, double P, double D){
  double error = dDegrees - TurnGyroSmart.rotation(degrees)*1.015; 
  double prevError;
  int counter = 0; 
  while (counter <= 25){
    if ((TurnGyroSmart.rotation(degrees)*1.015 > (dDegrees - 1.5)) && (TurnGyroSmart.rotation(degrees)*1.015 < (dDegrees + 1.5))){
      counter++;
    }
    else {
      counter = 0; 
    }
    prevError = error; 
    error = dDegrees - TurnGyroSmart.rotation(degrees)*1.015; 
    Drivetrain.turn(right, (error*P)+(prevError-error)*D, vex::velocityUnits::pct);
    vex::task::sleep(10);
  }
  Drivetrain.stop(brake);
}

// call this function to reset all motor to default
void fResetAllMotors(){
  // reset velocity for all motor
  Drivetrain.setDriveVelocity(dDrivePwr*100,percent); 

  Lift.setVelocity(100,percent); 
  Intake.setVelocity(100,percent); 
}

// ############################## AUTONAMOUS FUNCTIONS ###################################
void test() {
  fPIDDrive(50);
}