#!/bin/python3

import matplotlib.pyplot as plt
import pandas as pd
import sys
import pickle


# === Load CSV File ===
file = sys.argv[1]
file = "../results/" + file
df = pd.read_csv(file)
df.columns = df.columns.str.strip()
respath = "../results/" + file.split("/")[-1].split(".")[0]


# === Plot 1: Total Bacteria and Alive Bacteria vs. Time ===
fig_bacteria, ax1 = plt.subplots(figsize=(16, 12))
ax1.plot(df["TimeElapsed"], df["AliveBacteria"], label="Alive Bacteria",
         marker="o", linewidth=1)
ax1.plot(df["TimeElapsed"], df["TotalBacteria"], label="Total Bacteria",
         marker="s", linewidth=1)
ax1.set_xlabel("Time Elapsed")
ax1.set_ylabel("Bacteria Count")
ax1.set_title("Total and Alive Bacteria vs. Time Elapsed")
ax1.legend()
ax1.grid()

filename = respath + "-bacteria.pkl"
with open(filename, "wb") as f:
    print(f"Pickle of Bacteria graph saved. Filename : {filename}")
    pickle.dump(fig_bacteria, f)


# === Plot 2: Total Nutrient vs. Time ===
fig_nutrient, ax2 = plt.subplots(figsize=(8, 6))
ax2.plot(df["TimeElapsed"], df["TotalNutrient"], label="Total Nutrient",
         color="green", marker="o", linewidth=1)
ax2.set_xlabel("Time Elapsed")
ax2.set_ylabel("Total Nutrient Level")
ax2.set_title("Total Nutrient Level vs. Time Elapsed")
ax2.grid()

filename = respath + "-nutrient.pkl"
with open(filename, "wb") as f:
    print(f"Pickle of Bacteria graph saved. Filename : {filename}")
    pickle.dump(fig_nutrient, f)


# === Plot 3: Net CO2 vs. Time ===
fig_co2, ax3 = plt.subplots(figsize=(8, 6))
ax3.plot(df["TimeElapsed"], df["NetCO2"], label="Net CO2", color="red",
         marker="o", linewidth=1)
ax3.set_xlabel("Time Elapsed")
ax3.set_ylabel("Net CO2 Level")
ax3.set_title("Net CO2 Level vs. Time Elapsed")
ax3.grid()

filename = respath + "-co2.pkl"
with open(filename, "wb") as f:
    print(f"Pickle of Bacteria graph saved. Filename : {filename}")
    pickle.dump(fig_co2, f)


# === Show All Figures ===
plt.tight_layout()
plt.show()
