# Gnuplot graph generation script
# Gregory Kuhlmann, 2002

# Color output
set terminal postscript eps color solid "Helvetica" 24

# Black & White output
#set terminal postscript eps monochrome dashed "Helvetica" 24

# Output file
set output "./graph.eps"

# Appearance
set style data lines
set border 3
set xtics nomirror
set ytics nomirror
set multiplot

# Axes
set xrange [0:]
set xlabel "Training Time (hours)"

set yrange [0:]
set ylabel "Episode Duration (seconds)"

# Plot Data
plot \
"example.out", \
