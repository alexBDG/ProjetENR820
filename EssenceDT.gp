#!/usr/bin/gnuplot

###set terminal qt size 800,500

###set xtics 10
###set xrange [0:30.]
set xlabel 'Temps (s)'


set multiplot

set size 0.7,0.5
set origin 0.0,0.5
unset key
###set ytics 0.2
###set yrange [0:1.1]
set ylabel 'd²/d0²'
plot "solution_dt_0.001000_Carburant_Essence.dat" u 1:5 w l title "dt = 10E-3", "solution_dt_0.000100_Carburant_Essence.dat" u 1:5 w l title "dt = 10E-4", "solution_dt_0.000010_Carburant_Essence.dat" u 1:5 w l title "dt = 10E-5", "solution_dt_0.000001_Carburant_Essence.dat" u 1:5 w l title "dt = 10E-6"

set size 0.7,0.5
set origin 0.0,0.0
unset key
###set ytics 20
###set yrange [270:350]
set ylabel 'Ts (K)'
plot "solution_dt_0.001000_Carburant_Essence.dat" u 1:3 w l title "dt = 10E-3", "solution_dt_0.000100_Carburant_Essence.dat" u 1:3 w l title "dt = 10E-4", "solution_dt_0.000010_Carburant_Essence.dat" u 1:3 w l title "dt = 10E-5", "solution_dt_0.000001_Carburant_Essence.dat" u 1:3 w l title "dt = 10E-6"

set size 0.3,0.4
set origin 0.7,0.45
set key box reverse bottom center
set key title "Pas de temps"
set border 0
unset tics
unset xlabel
unset ylabel
set yrange [0:1]
plot 2 w l title "dt = 10E-3", 2 w l title "dt = 10E-4", 2 w l title "dt = 10E-5", 2 w l title "dt = 10E-6"


pause -1
