# biotic_growth_simulation

This project aims to simulate the growth of biotic colonies over time, modeling 
factors like nutrient availability, reproduction rates, and environmental 
conditions. The simulation is implemented in C++ and aims to provide an 
educational tool for understanding dynamics and growth patterns in a controlled 
environment.
**Status**: Project is under active development.
The design process is underway for simulating bacterial breeds, but can be 
implemented for other species in the future.
_Made for SSPaCe Astrobiology Payload (SAP)_

## Table of Contents
- [Architecture](#architecture)
- [Aimed Features](#features)
- [Installation](#installation)
- [License](#license)
- [Common Commands](#commonCommands)


## Aimed Features

### Dynamic growth modeling: 
Simulate how biotic colonies grow based on nutrient availability.

### Environmental factors: 
Adjust temperature, pH, and nutrient distribution to see how they affect 
growth.

### Data visualization: 
Graphs and visual output for understanding biotic population changes over 
time.


## Project Structure

```
├── src/           # Core implementation files
├── include/       # Header files
├── apps/          # Application entry points (main.cpp)
├── bin/           # Compiled executables
├── results/       # Simulation output (CSV files, plots)
├── utils/         # Python plotting utilities
├── scripts/       # Windows batch scripts
└── build/         # CMake build directory
```


## Architecture

The codebase follows a modular C++ design with clear separation of concerns:

### Core Classes

- **`Environment`**: Manages the 3D spatial grid of nutrient patches, including
nutrient distribution, acetate levels, CO2 concentration, and diffusion
mechanics
- **`Bacterium` (Species.h)**: Individual organism class that handles movement,
eating, reproduction, death, and adaptation behaviors
- **`Cluster`**: Main simulation controller that inherits from both Environment
and Bacterium, manages populations of bacteria and orchestrates the simulation
lifecycle

### Key Inheritance Relationships

- `Cluster` inherits from `Environment` (public) and `Bacterium` (protected)
- This design allows Cluster to manage both environmental conditions and bacterial behaviors

### Simulation Flow

1. Initialize environment with configurable 3D grid (default 50x50x50 patches)
2. Populate with initial bacteria at random positions with random energy levels
3. Run simulation loop:
   - Each bacterium performs: move → eat → potentially reproduce → live/die
   - Environment handles nutrient diffusion and chemical level updates
   - Track population metrics and environmental changes
4. Export results to CSV and generate visualizations


## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/biotic-growth-simulation.git
   cd biotic-growth-simulation


2. To compile the code, run this command in the terminal
   g++ -O3 -I include apps/main.cpp src/Cluster.cpp src/Environment.cpp src/Random.cpp src/Species.cpp -o bin/main.out.exe
3. To run the code, first change directory using
   cd bin
   Then run the simulation using
   .\main.out.exe
4. To see the graphs, run "plot graphs.py".
5. To see the animation, run "visualiser.py".
### Development Workflow

```bash
# Full build and run cycle
cd build && make && ../bin/main.out

# Check for build configuration changes
cd build && cmake .. && make
```


## Data Output and Visualization

- Simulations generate CSV files in `results/` with columns: TimeElapsed, AliveBacteria, TotalBacteria, NetCO2, TotalNutrient, TotalAcetate
- Python visualization script (`utils/plot.py`) automatically generates three plots:
  - Bacteria population over time
  - Nutrient levels over time  
  - CO2 levels over time
- Plots are saved as pickle files for later analysis


## Key Configuration Parameters

### Environment Parameters
- Grid size (default: 50x50x50 patches)  
- Initial nutrient levels
- Temporal resolution (simulation time step)
- Diffusion constants

### Bacterial Parameters (in Species.h)
- Energy thresholds (min: 0, max: 500, reproduction: 300)
- Movement speed (1.0 μm/s)
- Consumption rates
- Acidic tolerance limits


## Development Notes

### Memory Management
- Uses dynamic allocation for bacteria during reproduction
- Proper cleanup implemented in simulation loops
- Vectors manage bacteria populations automatically

### Threading/Concurrency
- Currently single-threaded simulation
- Real-time console output during simulation using ANSI escape codes

### File I/O
- CSV output for data analysis
- Exception handling for file operations
- Results automatically saved to `results/` directory


## Important Design Conventions

1. **Composition over Inheritance**: The primary relationship is compositional.
Inheritance should be avoided. All instances of inheritance being used should be
changed.

2. **Template Method**: The simulation loop follows a consistent pattern across
different run methods

3. **Factory Pattern**: Bacteria creation is handled through constructors 
with randomization options

4. The project integrates with Python for visualization:
- `utils/plot.py` is called automatically after simulation
- Requires matplotlib, pandas, and pickle
- Virtual environment setup available in `venv/`


## License

Copyright (c) 2024 [Indian Institute of Space Science and Technology]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
