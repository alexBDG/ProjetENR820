#!/usr/bin/gnuplot

set key box reverse
set key title "Courbes"

set xlabel 'Time (s)'

set ylabel 'T (K)'


set autoscale x
set autoscale y



plot "solution_dt_0.000001_Carburant_Ethanol.dat" u 1:3 title "T"

pause -1
