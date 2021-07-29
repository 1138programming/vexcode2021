using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern smartdrive Drivetrain;
extern motor leftMotorA; 
extern motor leftMotorB; 
extern motor rightMotorA; 
extern motor rightMotorB; 
extern motor Intake;
extern motor Lift;
extern motor Arm;
extern inertial TurnGyroSmart; 
extern controller Controller1;
extern vision VisionSensor;
extern signature VisionSensor__SIG_1;
extern signature VisionSensor__SIG_2;
extern signature VisionSensor__SIG_3;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );