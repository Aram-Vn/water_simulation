# Water Simulation Project

This project simulates the dynamics of water height in a pool over time, adjusting the water input rate to reach a target water height. It includes a C++ program that performs the simulation and a Python script that compiles the C++ program, runs it, and visualizes the results using Matplotlib.

# Requirements

- *C++ Compiler:* Ensure you have g++ or any compatible C++ compiler installed.
- *Python:* Python 3.x
- Install the required Python packages listed in requirements.txt:

```bash
pip install -r requirements.txt
```

# Usage

1. Run the Python Script

Execute the Python script to compile the C++ program (if not already compiled), run the simulation, and visualize the results:

```bash
python water_simulation.py
```

2. Interact with the Plot

- *Close the Plot Window:* The plot window can be closed manually, and the script will handle the event gracefully.
- *Interrupt Execution:* You can stop the script by pressing `Ctrl + C`.