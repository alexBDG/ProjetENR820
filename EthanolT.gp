#!/usr/bin/gnuplot

set xlabel 'Temps (s)'

set multiplot

unset key
set ylabel 'Ts (K)'
plot "solution_dt_0.000001_Carburant_Ethanol.dat" u 1:3 w l

pause -1
