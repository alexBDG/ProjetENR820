#!/usr/bin/gnuplot

set key box reverse
set key title "Courbes"

set xlabel 'Time (s)'

set ylabel 'm (kg)'


set autoscale x
set autoscale y



plot "solution_dt_0.000100_Carburant_Heptane.dat" u 1:4 title "m"

pause -1
