/****************************************************************************** 
Auto-reversing Robocylinder using a look-up table for speed vs distance 
to correct for the inherent nonlinearity of a magnetic field vs. distance.
SparkFun ROB-12779 steppert controller; "Step" is IO2; "Direction" is IO3.
Cylinder 10 mm/rev; 200 full steps/rev; 1600 microsteps/rev; 
6.25 microns/microstep.
******************************************************************************/
//Distances in microsteps (6.25 microns/microstep)
int dist = 4800; //Normal travel distance (35 mm)
int maxdist = 16500; //Maximum travel (>100 mm; used to home cylinder)
int offsetdist = 8400; //Operating offset from full retract position

//Times (in microseconds)
int slowstep = 350; //Step period at minimum speed
int maxstep = 64; //Step period at maximum speed
int steptime; //Current step period
int y;

int x; //Step counter

// Lookup Table for speed vs mm from full extension
int spd[] = {2962, 2868, 2774, 2680, 2586, 2492, 2398, 2304, 2210, 2116, 2022, 1928, 1834, 1740, 1646, 1552, 1457, 1363, 1269, 1175, 1081, 987, 893, 799, 705, 611, 517, 423, 329, 235, 141};
void setup() {
//Setup the stepper motor interface
pinMode(2, OUTPUT); //"Step" output is IO2
pinMode(3, OUTPUT); //"Direction" output is IO3

//Setup the blue LED to show the direction
pinMode(13, OUTPUT); //Set the blue LED driver (IO13) as an output
digitalWrite(13, LOW); //Blue LED shows direction (ON = extending)

//Retract cylinder to stop
digitalWrite(3, HIGH); //Retract
steptime = slowstep; //Start at low speed
for(x=1; x<maxdist; x++) //Step counter
  {
  digitalWrite(2,HIGH); //Step
  delayMicroseconds(steptime);
  digitalWrite(2,LOW);
  if (steptime > maxstep) steptime = steptime-1; //Accelerate
  }
//Advance cylinder to operate point
delay(500); //Pause
digitalWrite(3, !digitalRead(3)); //Reverse direction
digitalWrite(13, HIGH); //Switch blue LED
steptime = slowstep;
for(x=1; x<dist+offsetdist; x++)
  {
  digitalWrite(2,HIGH);
  delayMicroseconds(steptime);
  digitalWrite(2,LOW);
  if (steptime > maxstep) steptime = steptime-1;
  }
delay(2000); //Pause 2 seconds
}
void loop() { //Run the cylinder back and forth
digitalWrite(13, digitalRead(3)); //Switch blue LED
digitalWrite(3, !digitalRead(3)); //Reverse direction
for(x=1; x<dist; x++) //Retraction step counter
  {
  digitalWrite(2,HIGH); //Step
  delayMicroseconds(spd[(x+x+1)/320]-10);
  digitalWrite(2,LOW);
  }
digitalWrite(13, digitalRead(3)); //Switch blue LED
digitalWrite(3, !digitalRead(3)); //Reverse direction
for(x=dist; x>1; x--) //Extension step counter
  {
  digitalWrite(2,HIGH); //Step
  delayMicroseconds(spd[(x+x+1)/320]-10);
  digitalWrite(2,LOW);
  }
}
