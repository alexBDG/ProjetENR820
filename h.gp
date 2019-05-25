#!/usr/bin/gnuplot

set key box reverse
set key title "Courbes"

set xlabel 'Time (s)'

set ylabel 'h (W/m.K)'


set autoscale x
set autoscale y



plot "solution_dt_0.000100_Carburant_Heptane.dat" u 1:8 title "h"

pause -1
