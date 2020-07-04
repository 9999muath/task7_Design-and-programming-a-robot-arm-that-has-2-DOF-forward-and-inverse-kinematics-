#include <Servo.h>
Servo motor_A;
Servo motor_B;
float O1 ;       // angle motor_A in degree
float O2 ;       // angle motor_B in degree
float rad_O1;    // angle motor_A in Radian
float rad_O2;    // angle motor_A in Radian
float L1;        // length Arm1
float L2;        // length Arm1
float x;
float y;
float pi = 3.14159265359;


void setup() {
  motor_A.attach(11);
  motor_B.attach(3);
  Serial.begin(9600);
  
 Serial.println("Enter the length(L1) in centimeter ");
 while(Serial.available()==0){}
 L1=Serial.parseFloat();
 Serial.print("your length (L1) = "); 
 Serial.println(L1);
   
 Serial.println("Enter the length(L2) in centimeter ");
 while(Serial.available()==0){}
 L2=Serial.parseFloat();
 Serial.print("your length (L2) = "); 
 Serial.println(L2);
 
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
   }

void loop() {

 if (Serial.available())  {
 
    char ch = Serial.read();
    if (ch == '1'){                //Forwad kinematics Case  
                     
  Serial.println("Enter the angle (motor_A) in degree ");
  while(Serial.available()==0){}
  O1=Serial.parseFloat();
  Serial.print("your angle (motor_A) = "); 
  Serial.println(O1);
  
  Serial.println("Enter the angle (motor_B) in degree ");
  while(Serial.available()==0){}
  O2=Serial.parseFloat();
  Serial.print("your angle (motor_B) = "); 
  Serial.println(O2);
                          //convert degree to radian
  rad_O1 = (O1*pi)/180;    
  rad_O2 = (O2*pi)/180;

  motor_A.write(O1); 
  motor_B.write(O2);
  
  x = L1 * cos(rad_O1) +L2 * cos(rad_O1 + rad_O2);
  y = L1 * sin(rad_O1) +L2 * sin (rad_O1 + rad_O2);
                          //Print data 
 Serial.print("x = "); 
 Serial.println(x);
 Serial.print("y = "); 
 Serial.println(y);
 Serial.print("motor_A moved to angle  "); 
 Serial.println(O1);
 Serial.print("motor_B moved to angle "); 
 Serial.println(O2);
 
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
 }
 
else if(ch == '0')
                        //inverse kinematics case
      {Serial.println("Enter the value X ");
      while(Serial.available()==0){}
      x=Serial.parseFloat();
      Serial.print("your X = "); 
      Serial.println(x);
      
      Serial.println("Enter the value Y ");
      while(Serial.available()==0){}
      y=Serial.parseFloat();
      Serial.print("your Y = "); 
      Serial.println(y);
                                    //calculation
      rad_O2 = acos((sq(x)+ sq(y) - sq(L1) - sq(L2)) / (2*L1*L2));
      rad_O1= atan(y / x) - atan((L2*sin(rad_O2)) / (L1+ L2*cos(rad_O2)));
                           //convert degree to radian
      O1= (rad_O1*180)/pi;
      O2= (rad_O2*180)/pi;
      
      motor_A.write(O1); 
      motor_B.write(O2);
                                                // Print data 
 Serial.print("motor_A moved to angle  "); 
 Serial.println(O1);
 Serial.print("motor_B moved to angle "); 
 Serial.println(O2);
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
 }
 
 else {Serial.println("EROR!! Enter (0) OR (1) ONLY ");
 Serial.println("Enter Number (1) to Forward kinematics or (0) to inverse kinematics");
 }
 }
 }
