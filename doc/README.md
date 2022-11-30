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
- [ ] Regular Diagram - Not Started
- [ ] Circuit Diagram - Not Started

#### Hardware
- [x] Build the Car 11/29
  - [x] Assemble Parts 11/29
    - [x] Chassis 11/15
      - [x] Motors 11/15
      - [x] Sensor 11/29
      - [x] Pi 11/15
- [ ] Polish - Not started
  - [ ] Cable management - Not started
  - [ ] Stabilize - Not started
    - [ ] Pi - Not started
    - [ ] Battery - Not started
    - [ ] Breadboard - Not started
    - [ ] Sensors - Currently, it is using tapes 11/29
      
#### Software
- [ ] Main File - Possible change needed
  - [x] Working Main File - Tested on 11/29
  - [x] Can interact with Drivers - 11/29
    - [x] Sensors - Mounted on 11/29
    - [x] Motors - Mounted on 11/29
- [ ] Drivers - In progress
  - [ ] Sensors - Buggy state
    - [ ] Line Sensors - In progress
      - [ ] (Bug) It isn't interacting with the motors yet.
      - [ ] Data are accessible (Worth checking) - Not started
    - [ ] Echo Sensors - In progress
      - [ ] Data are accessible (worth checking) - Not started
  - [ ] Motors - Buggy state
      - [ ] (BUG) One of the wheels is spinning in the opposite direction at the initial state.
        - [ ] MotorDriver might be implemented incorrectly (Worth checking) - Not started
      - [ ] Turning left/right correctly - Not started
  - [ ] Integration Test - Not ready to start
    - [ ] Line sensors can directly affect motors - Need Sensors to work properly first
    - [ ] Echo Sensors can directly affect motors - Need Sensors to work properly first

## Progress Track
11/09 - **Raf** -> Added starter code for the main program, a skeleton code for pulling data from sensors, and a documentation file (notes.txt).  
11/12 - **David** -> Updated the Pi's software, added GitHub login token for convenience, and installed vim for a better working environment. Found that we weren't provided with new GPIO wires.  
11/15 - **David** -> Created and shared documentation in Google Docs  
11/16 - **David & Christian** -> Assembled the wheels to the chassis, wired the wheels to a single Motorhat by daisy-chaining them, and ran the motor script from the previous assignment.  
11/16 - **Raf & Marc** -> Started implementing the sensor interface and added motor driver code to use.  
11/28 - **David** -> Changed project structure.  Source files don't need to be in the main directory.  
11/29 - **David** -> Moved documentation files to doc directory. Added a README file in doc for documentation.  
11/29 - **Christian, David, Raf** -> We tried to build our prototype today. Currently, our wheels are parts where one side of the wheels works correctly while the other one moves the opposite. Lastly, we added sensors to our car but there is a bug that causes to not interact with the wheels
