#!/usr/bin/python

import os
import subprocess
import matplotlib.pyplot as plt
import signal
import sys
from typing import List, Optional

main_cpp: str = 'main.cpp'
water_simulation_cpp: str = 'src/water_simulation.cpp'
executable_path: str = './water_simulation'

target_height: float = 7500.0
maxPoolHeight: float = 9000.0

# Prompt user for target height
try:
    target_height: float = float(input("Enter the target water height (in meters from 0 to 9000): "))
    if (target_height > maxPoolHeight or target_height < 0):
        target_height = 7500.0;
        print("target height is to high set it to default 7500 meters.")
except ValueError:
    print("Invalid input. Using default target height of 7500 meters.")
    
try:
    target_water_height: float = float(input("Enter the water input change per iteration: "))
except ValueError:
    print("Invalid input. Using default input change per iteration 0.7.")
    
# Compile the program
def compile_cpp(main_cpp: str, executable_path: str, water_simulation_cpp: str) -> bool:

    compile_command: str = f'g++ {main_cpp} {water_simulation_cpp} -o {executable_path}'
    print(f"Compiling {main_cpp}...")
    result: int = os.system(compile_command)
    if result != 0:
        print("Compilation failed.")
        return False
    print("Compilation succeeded.")
    return True

# for handling window close event
def on_close(event: Optional[plt.FigureManagerBase]) -> None:
    print("The plot window has been closed.")
    plt.ioff()  
    plt.close()  
    sys.exit(0)

# for ctrl + c
def signal_handler(sig: int, frame: Optional[object]) -> None:
    print("Interrupt received, stopping...")
    plt.ioff()  
    plt.close()  
    sys.exit(sig)

def run_and_plot(executable_path: str, target_height: float, target_water_height: float) -> None:
    times: List[float] = []
    heights: List[float] = []
    input_rates: List[float] = []

    # Initialize the plot
    fig: plt.Figure
    ax: plt.Axes
    fig, ax = plt.subplots()
    line_height, = ax.plot([], [], 'r-', label='Water Height')
    ax.set_xlabel('Time (seconds)')
    ax.set_ylabel('Water Height (meters)')
    ax.set_title('Water Height Over Time')

    # Initialize a text object for the water input rate
    input_rate_text: plt.Text = ax.text(0.05, 0.95, '', transform=ax.transAxes, fontsize=12,
                                        verticalalignment='top')

    # Adding target water height line to the plot
    ax.axhline(y=target_height, color='b', linestyle='--', label='Target Water Height')
    ax.legend()

    # Connect the close event to the callback function
    fig.canvas.mpl_connect('close_event', on_close)

    signal.signal(signal.SIGINT, signal_handler)

    # Run the C++ executable and pass the target height
    proc: subprocess.Popen = subprocess.Popen(
        executable_path,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    try:
        # Pass the target height to the water_simulation.cpp program
        proc.stdin.write(f"{target_height}\n")
        proc.stdin.flush()
        
        proc.stdin.write(f"{target_water_height}\n")
        proc.stdin.flush()

        for output_line in proc.stdout:
            if "targetWaterHeight:" in output_line:
                continue  # Skip the line setting the target height

            if "Current time:" in output_line:
                parts: List[str] = output_line.split(", ")
                time_str: str = parts[0].split(": ")[1].split()[0]
                height_str: str = parts[1].split(": ")[1].split()[0]
                # Water input rate
                rate_str: str = parts[2].split(": ")[1].split()[0] if len(parts) > 2 else '0.0'

                current_time: float = float(time_str)
                current_height: float = float(height_str)
                current_rate: float = float(rate_str)

                times.append(current_time)
                heights.append(current_height)
                input_rates.append(current_rate)

                # Update the plot
                line_height.set_xdata(times)
                line_height.set_ydata(heights)
                ax.relim()
                ax.autoscale_view()

                input_rate_text.set_text(f'Water Input Rate: {current_rate:.2f} m³/s')

                plt.draw()
                plt.pause(0.01)  # Pause to allow the plot to update

    except KeyboardInterrupt:
        print("Process interrupted by user.")

    finally:
        # Terminate the subprocess
        print(f"Final water input rate: {current_rate:.2f} m³/s")
        proc.terminate()
        proc.wait()
        plt.ioff()  
        plt.show(block=True)  
  

# Compile and run
if compile_cpp(main_cpp, executable_path, water_simulation_cpp):
    run_and_plot(executable_path, target_height, target_water_height)
else:
    print("Compilation failed. Please check the error messages above.")
