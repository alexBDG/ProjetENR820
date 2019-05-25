#!/usr/bin/gnuplot

set xlabel 'Temps (s)'

set multiplot

unset key
set ylabel 'd (m)'
plot "solution_dt_0.000001_Carburant_Essence.dat" u 1:2 w l

pause -1
