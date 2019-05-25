#!/usr/bin/gnuplot

set key box reverse
set key title "Courbes"

set xlabel 'Time (s)'

set ylabel 'r²/r0²'

set y2label 'Ts (K)'

set autoscale x
set autoscale y
set autoscale y2


plot "solution_dt_0.000100_Carburant_Heptane.dat" u 1:5 axes x1y1 title "Rayon", "solution_dt_0.000100_Carburant_Heptane.dat" u 1:3 axes x2y2 title "Température"

pause -1
