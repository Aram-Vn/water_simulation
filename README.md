# Water Simulation Project

- [Preview](#preview)
- [Overview](#overview)
- [Requirements](#requirements)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)
- [Functionality](#functionality)

# Preview

<div align="center">
  <img src="https://github.com/user-attachments/assets/7e7612a8-904f-4145-9601-b6a54b481766" width="500" height="auto" alt="sudoku">
</div>

# Overview

This project simulates the dynamics of water height in a pool over time, adjusting the water input rate to reach a target water height. The simulation is based on **Torricelli's Law**, which describes the speed of fluid flowing out of an orifice under the force of gravity. 
It includes a C++ program that performs the simulation and a Python script that compiles the C++ program, runs it, and visualizes the results using Matplotlib.

`Torricelli's Law` is applied in this project to calculate the water output rate, using the formula:

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
git clone git@github.com:Aram-Vn/water_simulation.git
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
❯ g++ main.cpp src/water_simulation.cpp -o water_simulation_program
./water_simulation # run
```

5. Run the Python Script
Execute the Python script to compile the C++ program (if not already compiled), run the simulation, and visualize the results:

```bash
python show_graph.py
```

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
