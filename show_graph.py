#!/usr/bin/python

import os
import subprocess
import matplotlib.pyplot as plt
import signal
import sys
from typing import List, Optional

# Define paths
cpp_file: str = 'water_simulation.cpp'
executable_path: str = './water_simulation'

# Compile the C++ program
def compile_cpp(cpp_file: str, executable_path: str) -> bool:
    compile_command: str = f'g++ -o {executable_path} {cpp_file}'
    print(f"Compiling {cpp_file}...")
    result: int = os.system(compile_command)
    if result != 0:
        print("Compilation failed.")
        return False
    print("Compilation succeeded.")
    return True

# Callback function to handle window close event
def on_close(event: Optional[plt.FigureManagerBase]) -> None:
    print("The plot window has been closed.")
    plt.ioff()  # Turn off interactive mode
    plt.close()  # Close the plot window
    sys.exit(0)

def signal_handler(sig: int, frame: Optional[object]) -> None:
    print("Interrupt received, stopping...")
    plt.ioff()  # Turn off interactive mode
    plt.close()  # Close the plot window
    sys.exit(sig)

def run_and_plot(executable_path: str) -> None:
    # Initialize lists to store the time, water height, and water input rate for plotting
    times: List[float] = []
    heights: List[float] = []
    input_rates: List[float] = []

    # Initialize the plot
    fig: plt.Figure
    ax: plt.Axes
    fig, ax = plt.subplots()
    line_height, = ax.plot([], [], 'r-', label='Water Height')  # Initialize with empty data
    ax.set_xlabel('Time (seconds)')
    ax.set_ylabel('Water Height (meters)')
    ax.set_title('Water Height Over Time')

    # Initialize a text object for the water input rate
    input_rate_text: plt.Text = ax.text(0.05, 0.95, '', transform=ax.transAxes, fontsize=12,
                                        verticalalignment='top')

    # Initialize target water height
    target_water_height: Optional[float] = None

    # Connect the close event to the callback function
    fig.canvas.mpl_connect('close_event', on_close)

    signal.signal(signal.SIGINT, signal_handler)

    proc: subprocess.Popen = subprocess.Popen(executable_path, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    try:
        for output_line in proc.stdout:
            # Read target water height from the C++ program output
            if "targetWaterHeight:" in output_line:
                target_water_height = float(output_line.split(": ")[1].strip())
                # Add target water height line to the plot
                ax.axhline(y=target_water_height, color='b', linestyle='--', label='Target Water Height')
                ax.legend()
                continue

            # Process other output lines
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

                # Update the text with the current water input rate
                input_rate_text.set_text(f'Water Input Rate: {current_rate:.2f} m³/s')

                plt.draw()
                plt.pause(0.01)  # Pause briefly to allow the plot to update

    except KeyboardInterrupt:
        print("Process interrupted by user.")

    finally:
        # Terminate the subprocess
        proc.terminate()
        proc.wait()
        plt.ioff()  # Turn off interactive mode
        plt.show(block=True)  # Block until the plot window is closed

# Compile and run
if compile_cpp(cpp_file, executable_path):
    run_and_plot(executable_path)
else:
    print("Compilation failed. Please check the error messages above.")
