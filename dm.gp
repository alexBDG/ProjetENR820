#!/usr/bin/gnuplot

set key box reverse
set key title "Courbes"

set xlabel 'Time (s)'

set ylabel 'dm (kg)'


set autoscale x
set autoscale y



plot "solution_dt_0.000100_Carburant_Heptane.dat" u 1:7 title "dm"

pause -1
