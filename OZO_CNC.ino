/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper
 * motor in alternating directions.
 */

#include <TMCStepper.h>


#define CS_PIN_1           7 // Chip select
#define CS_PIN_2           8
#define CS_PIN_3           9
#define ESTOP              1
#define STATUS_0           14
#define STATUS_1           15
#define DR_0_DIAG_0        16 //Use this
#define DR_0_DIAG_1        17
#define DR_1_DIAG_0        18 //Use this
#define DR_1_DIAG_1        19
#define DR_2_DIAG_0        20 //Use this
#define DR_2_DIAG_1        21
#define LED0               2
#define LED1               3
#define VACUUM             4
#define DOOR               5


#define R_SENSE 0.075f // Match to your driver


TMC5160Stepper driver_1(CS_PIN_1, R_SENSE);
TMC5160Stepper driver_2(CS_PIN_2, R_SENSE);
TMC5160Stepper driver_3(CS_PIN_3, R_SENSE);


void setup() {
  
  pinMode(STATUS_0, INPUT);
  pinMode(STATUS_1, INPUT);
  pinMode(DR_0_DIAG_0, INPUT);
  pinMode(DR_0_DIAG_1, INPUT);
  pinMode(DR_1_DIAG_0, INPUT);
  pinMode(DR_1_DIAG_1, INPUT);
  pinMode(DR_2_DIAG_0, INPUT);
  pinMode(DR_2_DIAG_1, INPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(VACUUM, OUTPUT);
  pinMode(DOOR, OUTPUT);

  Serial.begin(9600);
  SPI.begin();                    // SPI drivers

  //Drive 1==================================================================================================
  driver_1.begin();                 // SPI: Init CS pins and possible SW SPI pins

  //driver_1.toff(5);                 // Enables driver in software
  driver_1.rms_current(600);        // Set motor RMS current
  driver_1.microsteps(16);          // Set microsteps to 1/16th

//driver_1.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver_1.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
  driver_1.pwm_autoscale(true);     // Needed for stealthChop
  
  //Drive 2==================================================================================================
  driver_2.begin();

  //driver_2.toff(5);                 // Enables driver in software
  driver_2.rms_current(600);        // Set motor RMS current
  driver_2.microsteps(16);          // Set microsteps to 1/16th

//driver_2.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver_2.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
  driver_2.pwm_autoscale(true);     // Needed for stealthChop

  //Drive 3==================================================================================================
  driver_3.begin();

  //driver_3.toff(5);                 // Enables driver in software
  driver_3.rms_current(600);        // Set motor RMS current
  driver_3.microsteps(16);          // Set microsteps to 1/16th

//driver_3.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver_3.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
  driver_3.pwm_autoscale(true);     // Needed for stealthChop
}


void loop() {

  if((digitalRead(DR_0_DIAG_0)==LOW) || (digitalRead(DR_1_DIAG_0)==LOW) || (digitalRead(DR_2_DIAG_0)==LOW)) {
    digitalWrite(ESTOP, LOW);
    Serial.println("ESTOP!");
  } else {
    pinMode(ESTOP, INPUT_PULLUP);
    Serial.println("All Good.");
  }

}
