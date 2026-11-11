set terminal pngcairo size 1200,700
set output 'graphs/single_slit.png'
set title 'Single-Slit Diffraction Pattern'
set xlabel 'Screen Position (mm)'
set ylabel 'Relative Intensity'
set grid
set key top right
set border linewidth 1.5
plot 'data/single_slit.dat' using 1:2 with lines linewidth 2 title 'Single-Slit Diffraction'
