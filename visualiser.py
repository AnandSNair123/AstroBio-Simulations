import pygame
import csv
import sys
import time

# --- CONFIGURATION ---
WIDTH, HEIGHT = 500, 500  # Window size
GRID_SIZE = 50            # Simulation grid size (50x50)
CELL_SIZE = WIDTH // GRID_SIZE
FILENAME = "results/vis_data.csv" # Data file to read

# --- COLORS ---
BLACK = (0, 0, 0)
GREEN = (0, 255, 0)       # Alive Bacteria
RED = (255, 0, 0)         # Dead Bacteria
YELLOW = (255, 255, 0)    # Nutrients
BROWN = (139, 69, 19)     # Acetate

def main():
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("SSPACE Bacteria Simulation (Top-Down View)")
    clock = pygame.time.Clock()

    print(f"Loading data from {FILENAME}...")
    frames = {}
    
    try:
        with open(FILENAME, 'r') as f:
            reader = csv.reader(f)
            # Format: Frame, Type (0=Nutrient, 1=Acetate, 2=Alive, 3=Dead), X, Y, Value
            for row in reader:
                if not row: continue
                frame = int(row[0])
                if frame not in frames: frames[frame] = []
                frames[frame].append({
                    'type': int(row[1]),
                    'x': int(row[2]),
                    'y': int(row[3]),
                    'val': float(row[4])
                })
    except FileNotFoundError:
        print("Error: Could not find 'results/vis_data.csv'. Run the C++ simulation first!")
        sys.exit()

    print(f"Loaded {len(frames)} frames. Starting visualization...")

    frame_idx = 0
    max_frame = max(frames.keys()) if frames else 0
    running = True

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # 1. Clear Screen
        screen.fill(BLACK)

        # 2. Get data for current frame
        if frame_idx in frames:
            data = frames[frame_idx]
            
            # Draw Environment (Nutrients/Acetate) first
            for item in data:
                rect = (item['x'] * CELL_SIZE, item['y'] * CELL_SIZE, CELL_SIZE, CELL_SIZE)
                
                # --- FIX: DRAWING NUTRIENTS (Yellow) ---
                # Check for > 1.0 (instead of 100) to see diffused nutrients
                if item['type'] == 0 and item['val'] > 1.0: 
                    
                    # Boost intensity: Multiply by 5 to make faint 'fog' visible
                    # (e.g., value 10 becomes alpha 50, value 50 becomes alpha 250)
                    intensity = min(255, int(item['val'] * 5)) 
                    
                    s = pygame.Surface((CELL_SIZE, CELL_SIZE))
                    s.set_alpha(intensity)
                    s.fill(YELLOW)
                    screen.blit(s, (item['x'] * CELL_SIZE, item['y'] * CELL_SIZE))

                # --- FIX: DRAWING ACETATE (Brown) ---
                elif item['type'] == 1 and item['val'] > 1.0:
                    intensity = min(255, int(item['val'] * 10))
                    s = pygame.Surface((CELL_SIZE, CELL_SIZE))
                    s.set_alpha(intensity)
                    s.fill(BROWN)
                    screen.blit(s, (item['x'] * CELL_SIZE, item['y'] * CELL_SIZE))

            # Draw Bacteria on top
            for item in data:
                center = (int(item['x'] * CELL_SIZE + CELL_SIZE/2), int(item['y'] * CELL_SIZE + CELL_SIZE/2))
                if item['type'] == 2: # Alive
                    pygame.draw.circle(screen, GREEN, center, CELL_SIZE // 2 - 1)
                elif item['type'] == 3: # Dead
                    pygame.draw.circle(screen, RED, center, CELL_SIZE // 2 - 1)

        # Update Display
        pygame.display.flip()
        
        # Advance Frame
        if frame_idx < max_frame:
            frame_idx += 1
            # Check if we should hold the frame for a bit (speed control)
            time.sleep(0.08) 
        else:
            # Loop back or stop
            time.sleep(2)
            frame_idx = 0

    pygame.quit()

if __name__ == "__main__":
    main()