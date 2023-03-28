#include <kipr/wombat.h>
//functions
void claw_close(); //claw close
void claw_open(); //claw open
void claw_still(); //claw in original position
void claw_move(); //claw in turned position
void startup(); //startup for the robot to know where he is located
void moving_forward(); // moves forward, (distance, speed)
void turning_one(); //turn around with one wheel (1 = right / 0 = left)
void turning_two(); //turn around with two wheel (1 = right / 0 = left)
void chain_step_up(); // chain goes one step up (distance)
void chain_step_down(); // chain goes one step down (distance)
void chain(); // chain goes up and down (1 = oben/0 = unten, distance)
void turning(); // turn the car with a speficic angle 
void wait();
void commando_fish_catched(); // Initiates the Reverse Engineering tool

//declaring Values 
int rw = 0; //right wheel "motors 0"
int lw = 1; //left wheel "motors 1"
int rch = 2; //right chain motor "motor 2"
int lch = 3; //left chain motor "motor 3"
int claw = 0; //claw gripper "servo 0"
int clas = 1; //claw turner "servo 1"
int bs = 0; // back sensor "analog 0"


int main()
{ 
  
   

    
    
  
	
  
  // wait_for_light(0);
  // shut_down_in(115);
 
  
     
    claw_close();
    claw_still();
     commando_fish_catched();

    
    moving_forward(85, 45);  

    claw_open();
    claw_move();
    moving_forward(16, 40);  
    commando_fish_catched();
    claw_open();
    claw_move();
    claw_still();
    turning_two(0);
    chain(0, 10);
    msleep(1000);
    moving_forward(10, 10);
    moving_forward(50, 50);
    turning_two(0);
    moving_forward(20, 20);
    
    
	 
    


    





    return 0;
}

void commando_fish_catched()
{
    claw_move();
    claw_close();
    chain_step_up(9);
    claw_still();
    motor(0, -10);
    motor(1, -30);
    msleep(2000);
    ao();
    motor(0,  20);
    motor(1,  10);
    msleep(700);
    ao();
    claw_move();
    chain_step_up(11);
    claw_still();
    motor(0, 18);
    motor(1, 10);
    msleep(3000);
    ao();
    claw_move();
    chain_step_up(11);
    claw_still();
    motor(0, 27);
    motor(1, 17);
    msleep(2000);
    ao();
    claw_open();
    claw_move();


}


void claw_open()
{
    enable_servos(); 
    set_servo_position(0, 2047);
    msleep(1000);
    disable_servos();
}  
void claw_close()
{
    enable_servos();
    set_servo_position(0, 20);
    msleep(1000);
    disable_servos();
}
void startup()
{
    while ( analog(0) > 2000)
    {
        motor(rw, -30);
        motor(lw, -30);   	
        ao();
    }

}

void moving_forward(int laenge, int geschwindigkeit)
{
    motor(rw, geschwindigkeit);
    motor(lw, geschwindigkeit);
    msleep(100*laenge);
    ao();
}

void claw_still()
{	

    enable_servos();
    set_servo_position(1, 1850);
    msleep(1000);
    disable_servos();
}
void claw_move()
{

    enable_servos();
    set_servo_position(1, 0);
    msleep(1000);
    disable_servos();
}
void turning_one(int richtung)
{ // hier bewegt sich nur ein Rad 
    //bei eins fC$hrt er rechts
    if (richtung < 1)
    { mrp(1, 700, 6000);
     msleep(10000);
    }
    //bei zwei fC$hrt er links
    if (richtung >= 1)
    { mrp(0, 500, 3250);
     msleep(20000);
    }     
    ao();
} 
void turning_two(int richtung)
{ //hier bewegen sich zwei RC$der
    //bei eins fC$hrt es rechts
    if (richtung < 1)
    { mrp(1, 1500, -1250);
     mrp(0, 1500, 1150);
     msleep(1200);
    }
    //bei 0 fC$hrt es links
    if (richtung >= 1)
    { mrp(1, 1500, 1200);
     mrp(0, 1500, -1150);
     msleep(1000);
    }
    ao();
} 

void chain_step_up(int up)
{
    motor(2,  80);
    motor(3, -80);
    msleep(200*up);
    ao();
}
void chain_step_down()
{
    motor(2,  -80);
    motor(3,   80);
    msleep(2000);
    ao();
}

void chain(int richtung, int distance)
{   //bei zwei fC$hrt es nach unten
    if(richtung < 1)
    {
        motor(2,  -70);
        motor(3,   70);
        msleep(2000*distance);
    }
    //bei eins fC$hrt es nach oben
    if(richtung >= 1)
    {
        motor(2,   30);
        motor(3,  -30);
        msleep(1000*distance);
    }
    ao();
}

void turning (int ankle)
{
    motor(0, 21*ankle);
    motor(1, 3*ankle);
    msleep(2000);
    ao();
}



