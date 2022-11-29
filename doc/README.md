# Documentation
## Team Fried Pi

### Goal
Our goal is to create a small robot car using a Raspberry Pi as a central processing unit. The main components will be using line sensors to follow the road, ultrasonic sensors to detect front/back objects, and motors to move the car.

## Components
* Chassis
* Sensors
  * TCRT5000 Reflective Optical Sensors
  * HCSRO4 (Echo sensor)
* Raspberry Pi Hat
  * WaveShare Motor Drive Hat
* Motors

### Tasks

#### Plan
- [ ] Regular Diagram
- [ ] Circuit Diagram

#### Hardware
- [ ] Build the Car
  - [ ] Assemble Parts
    - [x] Chassis
      - [x] Motors
      - [ ] Sensor
      - [ ] Pi
      
#### Software
- [ ] Main File
  - [ ] Working Main File
  - [ ] Can interact with Drivers
    - [ ] Sensors
    - [ ] Motors
- [ ] Drivers
  - [ ] Sensors
    - [ ] Line Sensors
      - [ ] Data are accessible
    - [ ] Echo Sensors
      - [ ] Data are accessible
  - [ ] Motors

## Progress Track
11/09 - **Raf** -> Added starter code for the main program, a skeleton code for pulling data from sensors, and a documentation file (notes.txt).
11/12 - **David** -> Updated the Pi's software, added GitHub login token for convenience, and installed vim for a better working environment. Found that we weren't provided with new GPIO wires.
11/15 - **David** -> Created and shared documentation in Google Docs
11/16 - **David & Christian** -> Assembled the wheels to the chassis, wired the wheels to a single Motorhat by daisy-chaining them, and ran the motor script from the previous assignment.
11/16 - **Raf & Marc** -> Started implementing the sensor interface and added motor driver code to use.
11/28 - **David** -> Changed project structure.  Source files don't need to be in the main directory.
