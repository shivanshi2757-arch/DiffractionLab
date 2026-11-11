set terminal pngcairo size 1200,700
set output 'graphs/n_slit.png'
set title 'N-Slit Diffraction Pattern'
set xlabel 'Screen Position (mm)'
set ylabel 'Relative Intensity'
set grid
set key top right
set border linewidth 1.5
plot 'data/n_slit.dat' using 1:2 with lines linewidth 2 title 'N-Slit Diffraction'
