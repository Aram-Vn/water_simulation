# Water Simulation with PID Controller

- [Preview](#preview)
- [Overview](#overview)
- [Requirements](#requirements)
- [Setup Instructions](#setup-instructions)
- [PID Controller Tuning Parameters](#pid-controller-tuning-parameters)
  - [Tuning Guidelines](#tuning-guidelines)
- [Usage](#usage)
- [Functionality](#functionality)
- [Classes](#classes)

# Preview

<div align="center">
  <a href="https://github.com/user-attachments/assets/5ed1c79a-ed21-42be-b15e-7be55c82a487">
    <img src="https://github.com/user-attachments/assets/5ed1c79a-ed21-42be-b15e-7be55c82a487" width="32%" alt="Screenshot 1">
  </a>
  <a href="https://github.com/user-attachments/assets/316a1d95-4713-493a-885a-df8fc1b3c3fa">
    <img src="https://github.com/user-attachments/assets/316a1d95-4713-493a-885a-df8fc1b3c3fa" width="32%" alt="Screenshot 2">
  </a>
  <a href="https://github.com/user-attachments/assets/248bfe3d-5a07-48d5-97d4-982290982d80">
    <img src="https://github.com/user-attachments/assets/248bfe3d-5a07-48d5-97d4-982290982d80" width="32%" alt="Screenshot 3">
  </a>
</div>


# Overview

This project simulates the dynamics of water height in a pool over time, adjusting the water input rate to reach a target water height. The simulation is based on **Torricelli's Law**, which describes the speed of fluid flowing out of an orifice under the force of gravity.

Additionally, a **PID Controller** is used to dynamically adjust the water input rate to maintain the desired water height over time, ensuring that the system responds effectively to disturbances or changes in the water height.

The project consists of:

- **A C++ program** that simulates the water height and implements the `PID controller`.

- **A Python script** that compiles the C++ program, runs it, and visualizes the results using matplotlib.
Torricelli's Law is applied in this project to calculate the water output rate, using the formula:

<div align="center">
  <img src="https://github.com/user-attachments/assets/218d8648-2ab5-4c72-ae9c-1c08d276719c" width="500" height="auto" alt="sudoku">
</div>

Where:

- `Q` is the flow rate of water (m^3/s),
- `A` is the cross-sectional area of the outlet(m^2),
- `g` is the gravitational acceleration (9.81 m/s²),
- `h` is the current water height in the pool (m).


# Requirements

- *C++ Compiler:* Ensure you have g++ or any compatible C++ compiler installed.
- *Python:* Python 3.x
- Install the required Python packages listed in requirements.txt:

# Setup Instructions

1. Clone the Repository

```bash
git clone git@github.com:Aram-Vn/water_simulation_PID_controller.git
cd water_simulation
```

2.Create and Activate a Virtual Environment

It's recommended to use a virtual environment to manage your Python dependencies. Here's how to set one up:

On Linux/MacOS:

```bash
python3 -m venv venv
source venv/bin/activate
```

On Windows:

```bash
python -m venv venv
venv\Scripts\activate
```

3. Install Dependencies
Once the virtual environment is activated, install the required Python packages using `pip`:

```bash
pip install -r requirements.txt
```

4. Compile the C++ Program (optional)

Before running the simulation, ensure the C++ program is compiled. You can do this manually or let the Python script handle it.

```bash
mkdir build
cd build 
cmake ..
cmake --build .
./water_simulation # run
```

5. Run the Python Script
Execute the Python script to compile the C++ program (if not already compiled), run the simulation, and visualize the results:

```bash
python show_graph.py
```

# PID Controller Tuning Parameters

**The PID controller** used in this simulation has three key parameters:

- `Proportional Gain (kp)`: This parameter determines the reaction to the current error. Increasing kp will make the controller respond more aggressively to the error, but setting it too high can cause the system to oscillate or become unstable.

- `Integral Gain (ki)`: This parameter adjusts the response based on the accumulated error over time. It helps eliminate steady-state error by integrating the error term, but excessive ki can lead to an unstable system with oscillations.

- `Derivative Gain (kd)`: This parameter predicts the future trend of the error based on its rate of change. It provides damping to the system and can help reduce overshoot and oscillations. However, too high a value can make the system overly sensitive to noise.

## Tuning Guidelines

1. Start with kp: Begin by setting ki and kd to zero and adjust kp to get a reasonable response. Aim for a balance between responsiveness and stability.

2. Add ki Slowly: Gradually increase ki to reduce any steady-state error. Be cautious of introducing too much integral action, as it can lead to oscillations.

3. Tune kd: Finally, adjust kd to minimize overshoot and improve the stability of the response.

4. Adjusting Parameters
You can modify the PID parameters in the C++ code to see their effect on the simulation. Refer to the source files for parameter definitions and consider running multiple simulations to find the optimal settings for your specific scenario.

# Usage

1. Run the Python Script

Execute the Python script to compile the C++ program (if not already compiled), run the simulation, and visualize the results:

```bash
python show_graph.py
```

2. Interact with the Plot

- *Close the Plot Window:* The plot window can be closed manually, and the script will handle the event gracefully.
- *Interrupt Execution:* You can stop the script by pressing `Ctrl + C`.

# Functionality

- The C++ program simulates water height in a pool based on predefined constants and dynamically adjusts the water input rate to maintain a target height.

- The Python script compiles the C++ code if needed, executes the compiled program, reads its output, and plots the water height and input rate in real-time using `matplotlib`.

# Classes

`Classes`

- `The WaterSimulation class` is responsible for simulating the dynamics of water height in a pool. It uses a PID controller to dynamically adjust the water input rate to reach and maintain a target water height.

- **Methods**: 
  - `static WaterSimulation* getInstance(double inputTargetWaterHeight, double kp, double ki, double kd)`

    Retrieves the singleton instance of WaterSimulation. If the instance does not exist, it cols private constructor which initializes a WaterSimulation instance with a specified target water height and PID parameters (proportional gain **kp**, integral gain **ki**, and derivative gain **kd**).

    - Parameters
      - `inputTargetWaterHeight`: The desired water height to be maintained.
      - `kp`: Proportional gain for the PID controller. default value is 1.0
      - `ki`: Integral gain for the PID controller. default value is 0.1
      - `kd`: Derivative gain for the PID controller. default value is 0.01

    - **Returns**: A pointer to the singleton WaterSimulation instance.

  - `void runSimulation()`
    - Executes the water simulation. It continuously adjusts the water input rate using the PID controller and outputs the current simulation state (time, water height, and input rate) to the console.
    - The simulation runs until the maximum simulation time is reached.
