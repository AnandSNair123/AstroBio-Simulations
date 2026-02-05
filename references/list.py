globals to be defined

  spawn-energy         ; the initial energy of bacteria at the starting
  acidity-starvation-bacteria-gain-from-food ; energy bacteria get for eating a single unit of nutrition under acidity conditions
  acetate-spawn-distance ; max distance till which the acetate molecule can go from the cell wall
  acetates-per-nutrient ; acetate molecules released per unit of nutrition
  energy-for-acetate-release ; energy spent to convert nutrition to acetate byproduct
  acidic-response-radius ; max distance till which the acetate molecule can affect acidity of the bacteria
  gravity-speed ; speed at which the acetate molecules sediment
  neutralize-radius ; max distance till which the acid resitance molecules can detect the acetate molecules
  AR-spawn-radius ;  max distance till which the acid resitance molecules can travel from the cell wall to neutralize the acetate molecules
  max-bacteria ; max peak of the growth curve
  cell-density ; total biomass of all bacteria (living/dead)
  time ; no. of ticks at each instant
  peak-time ; time it takes for the growth curve to peak
  lag? ; a boolean to keep track of the lag phase
  lag-time ; time period for which the lag phase lasts
  log-avg-growth-rate ; average growth rate of the bacteria in log phase
  current-bacteria-count ; no. of alive bacterias in the current tick
  previous-bacteria-count ; no. of alive bacterias in the previous tick
  mean-energy ; mean of normal distribution of energy
  std-dev-energy ; Standard deviation of normal distribution of energy
  bacteria-counts
  bacteria-derivative
  average-bacteria-derivative
  moving-average-window-size
  derivative-history



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Patch
  
   diffusion-rate       ; the rate at which nutrients diffuse



~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Bacteria


  max-energy           ; the maximum amount of energy a bacteria can have
  min-energy           ; the minimum amount of energy possible
  living-energy        ; the constant energy consumed by the bacteria to live
  reproduction-energy  ; the energy required for bacteria to reproduce
  co2-released         ; co2 released per unit nutrient-lvl consumption
  max-acidic-threshold ; No. of acetates in proximity it takes for bacteria to diei

# for future
  starving-energy      ; Energy below which the bacteria starves and starts metabolising more efficiently
  acidic-threshold     ; No. of acetates in proximity it takes for bacteria to react
  bacteria-size        ; size of the bacteria
  nutrient-consumption ; rate at which the bacteria consumes nutrients under normal conditions
  bacteria-gain-from-food ; energy bacteria get for eating a single unit of nutrition under normal conditions
  energy-starvation-nutrient-consumption ; rate at which the bacteria consumes nutrients under energy defeciency conditions
  energy-starvation-bacteria-gain-from-food ; energy bacteria get for eating a single unit of nutrition under energy defeciency conditions
  acidity-starvation-nutrient-consumption ; rate at which the bacteria consumes nutrients under acidity conditions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Environment

  net-co2              ; total co2 in the container
  initial-num-bacteria ; the number of bacteria in the sample at the beginning
  acetate-size         ; size of the acetate molecule
  AR-size              ; size of acid resistance molecules


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
