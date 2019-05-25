#!/usr/bin/gnuplot

set key box reverse
set key title "Courbes"

set xtics 10
set xrange [0:30.]
set x2range [0:30.]
set xlabel 'Temps (s)'

set ytics 0.2
set yrange [0:1.1]
set ylabel 'r²/r0²'

set y2tics 20
set y2range [270:350]
set y2label 'Ts (K)'

set ytics nomirror
set y2tics nomirror


plot "solution_dt_0.000100_Carburant_Heptane.dat" u 1:5 axes x1y1  title "Rayon", "solution_dt_0.000100_Carburant_Heptane.dat" u 1:3 axes x2y2  title "Température"

pause -1
