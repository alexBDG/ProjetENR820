#!/usr/bin/gnuplot

set xlabel 'Temps (s)'

set multiplot

set key box
set key title "Carburant"
set ylabel 'Ts (K)'
plot "solution_dt_0.000001_Carburant_Essence.dat" u 1:3 title "Essence", "solution_dt_0.000001_Carburant_Ethanol.dat" u 1:3 title "Ethanol"

pause -1
