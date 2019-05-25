#!/usr/bin/gnuplot

set xlabel 'Temps (s)'

set multiplot

set key box
set key title "Carburant"
set ylabel 'd²/d0²'
plot "solution_dt_0.000001_Carburant_Essence.dat" u 1:5 title "Essence", "solution_dt_0.000001_Carburant_Ethanol.dat" u 1:5 title "Ethanol"

pause -1
