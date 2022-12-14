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
- [x] Regular Diagram - 12/13
- [x] Circuit Diagram - 12/13

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
    - [ ] Breadboard - 12/28
    - [x] Sensors - Currently, it is using tapes 11/29
      
#### Software
- [x] Main File - Possible change needed
  - [x] Working Main File - Tested on 11/29
  - [x] Can interact with Drivers - 11/29
    - [x] Sensors - Mounted on 11/29
    - [x] Motors - Mounted on 11/29
- [x] Drivers - In progress
  - [x] Sensors - 12/5
    - [x] Line Sensors - 12/5
      - [x] (Bug) It isn't interacting with the motors yet.
      - [x] Data are accessible (Worth checking) - 12/5
    - [x] Echo Sensors - 12/5
      - [x] Data are accessible (worth checking) - 12/5
  - [x] Motors - 12/5
      - [x] (BUG) One of the wheels is spinning in the opposite direction at the initial state.
        - [x] MotorDriver might be implemented incorrectly (Worth checking) - Not started
      - [x] Turning left/right correctly - 12/12
  - [x] Integration Test - Not ready to start
    - [x] Line sensors can directly affect motors - 11/28
    - [x] Echo Sensors can directly affect motors - 11/28

## Progress Track
11/09 - **Raf** -> Added starter code for the main program, a skeleton code for pulling data from sensors, and a documentation file (notes.txt).  
11/12 - **David** -> Updated the Pi's software, added GitHub login token for convenience, and installed vim for a better working environment. Found that we weren't provided with new GPIO wires.  
11/15 - **David** -> Created and shared documentation in Google Docs  
11/16 - **David & Christian** -> Assembled the wheels to the chassis, wired the wheels to a single Motorhat by daisy-chaining them, and ran the motor script from the previous assignment.  
11/16 - **Raf & Marc** -> Started implementing the sensor interface and added motor driver code to use.  
11/28 - **David** -> Changed project structure.  Source files don't need to be in the main directory.  
11/29 - **David** -> Moved documentation files to doc directory. Added a README file in doc for documentation.  
11/29 - **Christian, David, Raf** -> We tried to build our prototype today. Currently, our wheels are parts where one side of the wheels works correctly while the other one moves the opposite. Lastly, we added sensors to our car but there is a bug that causes to not interact with the wheels
12/05 - David -> Reworked sensor in develop branch. It is has proper thread handling including stopping the program. Currently missing the implementation of thread functions. Main compiles but haven't tested yet going to do that soon
12/12 - Raf, Christian, Marc -> created the logic for moving the car.
12/13 - Raf, Christian, Marc -> Final changes and presentation.
12/13 - Raf, Christian, Marc, David -> Documentation.
