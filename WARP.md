# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Project Overview

Biosim is a biotic growth simulation project that models bacterial colony growth dynamics over time. The simulation considers factors like nutrient availability, reproduction rates, and environmental conditions. The project is part of the SSPaCe Astrobiology Payload (SAP) initiative and is designed as an educational tool for understanding growth patterns in controlled environments.

**Status**: Project is under active development.

## Architecture

The codebase follows a modular C++ design with clear separation of concerns:

### Core Classes

- **`Environment`**: Manages the 3D spatial grid of nutrient patches, including nutrient distribution, acetate levels, CO2 concentration, and diffusion mechanics
- **`Bacterium` (Species.h)**: Individual organism class that handles movement, eating, reproduction, death, and adaptation behaviors
- **`Cluster`**: Main simulation controller that inherits from both Environment and Bacterium, manages populations of bacteria and orchestrates the simulation lifecycle

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

## Common Commands

### Build System (CMake)

```bash
# Initial setup (from project root)
mkdir -p build
cd build
cmake ..

# Build the project
make

# Build specific targets
make myproject_lib      # Build library only
make main.out          # Build main executable

# Clean build
make clean
```

### Run Simulation

```bash
# Run main simulation (from project root)
./bin/main.out

# Or from build directory
cd build && make main.out && ../bin/main.out
```

### Development Workflow

```bash
# Full build and run cycle
cd build && make && ../bin/main.out

# Check for build configuration changes
cd build && cmake .. && make
```

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

## Important Design Patterns

1. **Composition over Inheritance**: While Cluster inherits from Environment and Bacterium, the primary relationship is compositional (Cluster contains vectors of Bacterium objects)

2. **Template Method**: The simulation loop follows a consistent pattern across different run methods

3. **Factory Pattern**: Bacteria creation is handled through constructors with randomization options

## Python Integration

The project integrates with Python for visualization:
- `utils/plot.py` is called automatically after simulation
- Requires matplotlib, pandas, and pickle
- Virtual environment setup available in `venv/`
