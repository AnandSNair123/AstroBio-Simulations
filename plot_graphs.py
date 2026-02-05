import pandas as pd
import matplotlib.pyplot as plt
import os

# --- CONFIGURATION ---
# IMPORTANT: This must match the filename in your main.cpp
# If you changed it to "evolution.csv" in C++, change it here too!
CSV_FILE = "results/trial1.csv" 

def main():
    if not os.path.exists(CSV_FILE):
        print(f"Error: Could not find '{CSV_FILE}'.")
        print("Make sure you have run the simulation first!")
        return

    # 1. Read the Data
    try:
        data = pd.read_csv(CSV_FILE)
        # Clean column names (remove whitespace just in case)
        data.columns = data.columns.str.strip()
    except Exception as e:
        print(f"Error reading CSV: {e}")
        return

    # 2. Setup the Plotting Grid (2x2)
    fig, axs = plt.subplots(2, 2, figsize=(14, 10))
    fig.suptitle(f'Simulation Results: Evolution & Resources', fontsize=16)

    # --- PLOT 1: EVOLUTIONARY STRAINS (The Mutation Graph) ---
    # This replaces the generic population graph with the specific breakdown
    if 'Normal' in data.columns:
        axs[0, 0].plot(data['TimeElapsed'], data['Normal'], label='Normal', color='green', alpha=0.6)
        axs[0, 0].plot(data['TimeElapsed'], data['Type++'], label='Type ++ (Super)', color='gold', linewidth=2.5)
        axs[0, 0].plot(data['TimeElapsed'], data['Type+-'], label='Type +-', color='blue', alpha=0.8)
        axs[0, 0].plot(data['TimeElapsed'], data['Type-+'], label='Type -+', color='orange', alpha=0.8)
        axs[0, 0].plot(data['TimeElapsed'], data['Type--'], label='Type -- (Weak)', color='red', linestyle='dashed', alpha=0.8)
        
        axs[0, 0].set_title('Evolutionary Competition (Strains)')
        axs[0, 0].set_xlabel('Time (s)')
        axs[0, 0].set_ylabel('Population Count')
        axs[0, 0].legend(loc='upper left')
        axs[0, 0].grid(True, alpha=0.3)
    else:
        print("Warning: Mutation columns not found in CSV. Run the simulation again with the new code.")

    # --- PLOT 2: NUTRIENTS ---
    axs[0, 1].plot(data['TimeElapsed'], data['TotalNutrient'], color='gold', linewidth=2)
    axs[0, 1].set_title('Total Nutrient Levels')
    axs[0, 1].set_xlabel('Time (s)')
    axs[0, 1].set_ylabel('Nutrient Units')
    axs[0, 1].grid(True, alpha=0.3)

    # --- PLOT 3: ACETATE (TOXICITY) ---
    axs[1, 0].plot(data['TimeElapsed'], data['TotalAcetate'], color='brown', linewidth=2)
    axs[1, 0].set_title('Total Acetate (Waste) Accumulation')
    axs[1, 0].set_xlabel('Time (s)')
    axs[1, 0].set_ylabel('Acetate Units')
    axs[1, 0].grid(True, alpha=0.3)

    # --- PLOT 4: NET CO2 ---
    axs[1, 1].plot(data['TimeElapsed'], data['NetCO2'], color='gray', linewidth=2)
    axs[1, 1].set_title('Net CO2 Produced')
    axs[1, 1].set_xlabel('Time (s)')
    axs[1, 1].set_ylabel('CO2 Units')
    axs[1, 1].grid(True, alpha=0.3)

    # 3. Show the graphs
    plt.tight_layout()
    print("Displaying graphs... (Close the window to exit)")
    plt.show()

if __name__ == "__main__":
    main()