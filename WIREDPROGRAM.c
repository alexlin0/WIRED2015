#pragma config(Motor,  port2,           leftwheel,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           forklift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           eeud,          tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           flappywing,    tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           eelr,          tmotorServoStandard, openLoop)
#pragma config(Motor,  port9,           rightwheel,    tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#if ( _TARGET == "VirtWorld" )
#pragma debuggerWindows("joystickSimple");
#include "JoystickDriver.c"
#endif

#define MAX_MOTOR_SPEED 127
#define DEADBAND 10

// variables
int speed_divisor ;
int flappy_wing_position ;
int last_speed_button_state ;
int forward_drive ;
int last_forward_drive_btn_state ;

void init_drive_parameters() //sets the speed of the motor
{
    //sets the speed of the motor to high
    speed_divisor = 1 ;
    //sets the initial button states to 0
    last_speed_button_state = 0 ;
    // checks to see if robot is moving forward
    forward_drive = 1 ;
    //sets the initial forward drive button state to 0
    last_forward_drive_btn_state = 0 ;
}

void change_drive_direction() //reverses the controls
{
    // sets button for the forward drive button state
    int current_forward_drive_btn_state = vexRT[Btn7D] ;
    // if statement checking if button is down
    if ( current_forward_drive_btn_state == 1 &&
         last_forward_drive_btn_state == 0 )
    {
        // checking to see if forward drive is in use
        if(forward_drive == 0)
        {
            //sets the forward drive to 1 switches controls
            forward_drive = 1 ;
        }
        else
        {
            //sets the forward drive to 0 doesn't switch controls
            forward_drive = 0 ;
        }
    }
    // sets the last button state to the current one
    last_forward_drive_btn_state = current_forward_drive_btn_state ;
}

void change_speed() //changes the motor speed
{
    int current_speed_button_state ;
#if ( _TARGET == "VirtWorld" ) //virtual world
    current_speed_button_state = joy1Pov(Pov0) ;
#else
    current_speed_button_state = vexRT[Btn7U] ;
#endif
    if( last_speed_button_state == 0 && current_speed_button_state == 1)
    {
        if (speed_divisor == 2 ) //changes speed of motor to slow
        {
          speed_divisor = 1; // changes  speed of motor to fast
        } else {
          speed_divisor = 2; // changes speed of motor to slow
        }
    }
    // sets last speed button to current speed button
    last_speed_button_state = current_speed_button_state ;
}

void drive() {                  // Code for driving the robot
#if ( _TARGET == "VirtWorld" )
    getJoystickSettings(joystick);
    motor[port10] = joystick.joy1_y2 / speed_divisor ;
    motor[port1] = -joystick.joy1_y1 / speed_divisor ;
#else
    if (forward_drive == 1)
    {
        if ( vexRT[Ch3] > DEADBAND || vexRT[Ch3] < -DEADBAND ) {
            // Controlling the left wheel using channel 3
            motor[leftwheel] = vexRT[Ch3] / speed_divisor ;
        } else {
            motor[leftwheel] = 0 ;
        }
        if ( vexRT[Ch2] > DEADBAND || vexRT[Ch2] < -DEADBAND ) {
            //Controlling the right wheel using channel 2
            motor[rightwheel] = -vexRT[Ch2] / speed_divisor ;
        } else {
            motor[rightwheel] = 0 ;
        }
    }
    else
    {
        if ( vexRT[Ch2] > DEADBAND || vexRT[Ch2] < -DEADBAND ) {
            // Reverse  the left wheel using channel 2
            motor[leftwheel] = -vexRT[Ch2] / speed_divisor ;
        }
        else {
            motor[leftwheel] = 0 ;
        }
        if ( vexRT[Ch3] > DEADBAND || vexRT[Ch3] < -DEADBAND ) {
            // Reverse the right wheel using channel 3
            motor[rightwheel] = vexRT[Ch3] / speed_divisor ;
        }
        else {
            motor[rightwheel] = 0 ;
        }
    }
#endif
}

//Code for the collection subsystem
void collection() {
#if ( _TARGET == "VirtWorld")
    //If Btn5U is pushed, the forklift should move up
    if(joy1Btn(Btn5) == 1)
    {
        //Set the motor speed to MAX_MOTOR_SPEED
        motor[port7] = MAX_MOTOR_SPEED;
    }
    //If Btn5D is pushed, the forklift should move down
    else if (joy1Btn(Btn7) == 1)
    {
        //Set the motor speed to -MAX_MOTOR_SPEED
        motor[port7] = -MAX_MOTOR_SPEED;
    }
    //If no button is pushed, then nothing should move
    else
    {
        //Set the motor speed to 0
        motor[port7] = 0;
    }
#else
    //If Btn5U is pushed, the forklift should move up
    if(vexRT[Btn5U] == 1)
    {
        //Set the motor speed to MAX_MOTOR_SPEED
        motor[forklift] = MAX_MOTOR_SPEED;
    }
    //If Btn5D is pushed, the forklift should move down
    else if (vexRT[Btn5D] == 1)
    {
        //Set the motor speed to -MAX_MOTOR_SPEED
        motor[forklift] = -MAX_MOTOR_SPEED;
    }
    //If no button is pushed, then nothing should move
    else
    {
        //Set the motor speed to 0
        motor[forklift] = 0;
    }
#endif
}

void init_flappy_wing(){
    flappy_wing_position = 0 ;
    motor[flappywing] = flappy_wing_position;
}

// Code for the Flappy wing
void flappy_wing(){
    //If Btn7R is pushed, deploy the wing
    if(vexRT[Btn7R] == 1)
    {
        //Set the motor speed to MAX_MOTOR_SPEED
        flappy_wing_position = -MAX_MOTOR_SPEED;
    }
    //If Btn7L is pushed, the wing should move left
    else if (vexRT[Btn7L] == 1)
    {
        //Set the motor speed to -MAX_MOTOR_SPEED
        flappy_wing_position = MAX_MOTOR_SPEED ;
    }
    motor[flappywing] = flappy_wing_position;
}

void arm_joint() {
    //If Btn6U is pushed, the arm should move up
    if(vexRT[Btn6U] == 1)
    {
        //Set the motor speed to MAX_MOTOR_SPEED
        motor[arm] = MAX_MOTOR_SPEED;
    }
    //If Btn6D is pushed, the arm should move down
    else if (vexRT[Btn6D] == 1)
    {
        //Set the motor speed to -MAX_MOTOR_SPEED
        motor[arm] = -MAX_MOTOR_SPEED;
    }
    else
    {
        //Set the motor speed to 0
        motor[arm] = 0;
    }
}

void end_effector()
{
#if ( _TARGET == "VirtWorld")
    //If Btn5U is pushed, the forklift should move up
    if(joy1Btn(Btn6) == 1)
    {
        //Set the motor speed to MAX_MOTOR_SPEED
        motor[port6] = MAX_MOTOR_SPEED;
    }
    //If Btn5D is pushed, the forklift should move down
    else if (joy1Btn(Btn8) == 1)
    {
        //Set the motor speed to -MAX_MOTOR_SPEED
        motor[port6] = -MAX_MOTOR_SPEED;
    }
    else  //If no button is pushed, then nothing should move
    {
        //Set the motor speed to 0
        motor[port6] = 0;
    }
#else
#if 0
    //If Btn8U is pushed, the end effector should move up
    if(vexRT[Btn8U] == 1)
    {
          //Set the motor spped to MAX_MOTOR_SPEED
        motor[eeud] = MAX_MOTOR_SPEED;
    }
    //If Btn8D is pushed, the end effector should move down
    else if (vexRT[Btn8D] == 1)
    {
          //Set the motor speed to -MAX_MOTOR_SPEED
        motor[eeud]= -MAX_MOTOR_SPEED;
    }
    else
    {
          //Set the motor speed 0
        motor[eelr] = 0;
    }

    //If Btn8R is pushed, the end effector should move right
    if(vexRT[Btn8R] == 1)
    {
          //Set the motor speed to MAX_MOTOR_SPEED
        motor[eelr] = MAX_MOTOR_SPEED;
    }
    //If Btn8L is pushed, then the end effector should move left
    else if (vexRT[Btn8L] == 1)
    {
          //Set the motor speed to -MAX_MOTOR_SPEED
        motor[eelr]= -MAX_MOTOR_SPEED;
    }
    else
    {
          //Set the motor speed to 0
        motor[eelr] = 0;
    }
#endif
#endif
}

#if 0
void nudge_left() {
#if ( _TARGET == "VirtWorld")
      if ( joy1Pov(Pov6) ) {
        motor[port10] = MAX_MOTOR_SPEED ;
        sleep(300) ;
        motor[port1] = -MAX_MOTOR_SPEED ;
        sleep(200) ;
        motor[port1] = 0 ;
        motor[port10] = -MAX_MOTOR_SPEED;
        sleep(320) ;
        motor[port1] = MAX_MOTOR_SPEED;
        sleep(100) ;
        motor[port10] = 0 ;
        motor[port1] = 0 ;
    }
#else
    if(vexRT[Btn8L] == 1) {
          motor[rightwheel] = MAX_MOTOR_SPEED ;
        sleep(300) ;
        motor[leftwheel] = -MAX_MOTOR_SPEED ;
        sleep(200) ;
        motor[leftwheel] = 0 ;
        motor[rightwheel] = -MAX_MOTOR_SPEED;
        sleep(320) ;
        motor[leftwheel] = MAX_MOTOR_SPEED;
        sleep(100) ;
        motor[rightwheel] = 0 ;
        motor[leftwheel] = 0 ;
    }
#endif
}

void nudge_right() {
#if ( _TARGET == "VirtWorld")
      if ( joy1Pov(Pov2) ) {
        motor[port1] = -MAX_MOTOR_SPEED ;
        sleep(300) ;
        motor[port10] = MAX_MOTOR_SPEED ;
        sleep(200) ;
        motor[port10] = 0 ;
        motor[port1] = MAX_MOTOR_SPEED;
        sleep(320) ;
        motor[port10] = -MAX_MOTOR_SPEED ;
        sleep(100) ;
        motor[port1] = 0 ;
        motor[port10] = 0 ;
    }
#else
    if(vexRT[Btn8R] == 1) {
          motor[leftwheel] = -MAX_MOTOR_SPEED ;
        sleep(300) ;
        motor[rightwheel] = MAX_MOTOR_SPEED ;
        sleep(200) ;
        motor[rightwheel] = 0 ;
        motor[leftwheel] = MAX_MOTOR_SPEED;
        sleep(320) ;
        motor[rightwheel] = -MAX_MOTOR_SPEED ;
        sleep(100) ;
        motor[leftwheel] = 0 ;
        motor[rightwheel] = 0 ;
    }
#endif
}
#endif

task main ()
{
      // call initialization functions
    init_flappy_wing() ;
    init_drive_parameters() ;

    // loop forever
    while (1)
    {
          // call drive routines
        change_speed();
        change_drive_direction();
        drive();

        // call collection and flappy wing routines
        collection();
        flappy_wing();

        // call arm routines
        arm_joint();
        end_effector();
    }
}
