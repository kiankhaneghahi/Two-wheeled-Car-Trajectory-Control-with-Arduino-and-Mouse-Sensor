#include <Stepper.h>

const int stepsPerRevolution = 200;  
Stepper myStepper1(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper2(stepsPerRevolution,  4, 3, 5, 6);
 static double xdist = 0;
 static double ydist = 0;
void setup()
{
  Serial.begin(9600); 
}
double geterror(double xin, double yin, double xfinal, double yfinal)
{
  double error = 0;
  error = pow((xin - xfinal), 2) + pow((yin - yfinal), 2);
  return pow(error, 0.5) ;
}
void setmotor(double theta)
{
 
   myStepper2.step(theta/1.8);
   myStepper1.step(theta/1.8);
   }
void gotoxy(double x, double y)
{
 String mx;
 String my;
 double xnow;
 double ynow;
   
  

  CheckTimeout();
  /*theta = atan(( ynow - y) /(xnow - x));
  setmotor(theta);
  while(((xnow - x )> .05)||((x - xnow )> .05)) 
  { myStepper1.setSpeed(120);
   myStepper2.setSpeed(120); 
//myStepper2.move(120); 
   h ++;   
   if(h == 20)
   {//Serial.print("cant");
      break;
      
   }
  } */
  
}
void aproachX(double newX, double newY){
   String mx;
 String my;
 double Xpos;
 double Ypos;
unsigned long stampX, stampY;   
  
   mx = Serial.readStringUntil('\n');
   Xpos = abs(mx.toDouble());
  Serial.print("X=");
  Serial.println(Xpos, DEC);
  Serial.print('\n');
  my = Serial.readStringUntil('\n');
  Ypos = abs(my.toDouble());
  Serial.print("Y=");
  Serial.print(Ypos, DEC); 
  Serial.print('\n');
  if(abs(Xpos - newX)< .5)
  return;
  if(abs(Ypos - newY)< .5)
  return;
 int Xdir = Xpos<newX ? 1 : -1;

  myStepper2.step(Xdir);        // move one step in the Xdir direction.


  Xpos += Xdir;               // update Xpos.

  stampX = millis();          // stamp actual time.
   int Ydir = Ypos<newY ? 1 : -1;

  myStepper1.step(Ydir);        // move one step in the Ydir direction.

  Ypos += Ydir;               // update Ypos.

  stampY = millis();      // stamp actual time.


  }



//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------

//Check for inactivity and turn off the steppers coils to save battery.

void CheckTimeout(){
  unsigned long stampX, stampY;

  if((millis() - stampY) > 1000){   //Turn Off StepperY coils.

  myStepper1.setSpeed(120);
   myStepper2.setSpeed(120); 

  }    

}
void Runn(double xin, double yin, double xfinal, double yfinal)// double(*function)(double))
{
  double error = 1;
  int count = 1;
  
    myStepper1.setSpeed(120);
   myStepper2.setSpeed(120); 
  double e = geterror(xin, yin, xfinal, yfinal) ;
  while ( e > .5)
  {  
    
    myStepper1.setSpeed(120);
    myStepper2.setSpeed(120); 
    double  epsilion = .05;
    xin = xin + epsilion;
    yin = 2;  
   aproachX(xin, yin);
    count ++;
    e = geterror(xin, yin, xfinal, yfinal);
 
    //aproachX(xin ,yin);

  CheckTimeout();
    if( count == 2000)
    {
      
    break ;
    
    }
   
  }
  
 
}
void loop()
{
    
   
 Runn(0, 0, 2000, 2000);
 for(int s=0; s<200; s++)
 {
 myStepper1.step(1);
 myStepper2.step(-1);
 }

}
