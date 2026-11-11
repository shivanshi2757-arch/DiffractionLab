# DiffractionLab – Interactive Diffraction Simulator

DiffractionLab is a C-based interactive physics simulation project that models diffraction patterns produced by a single slit and multiple slits.

The project combines numerical physics calculations with GNUplot to generate diffraction data and automatically create graphical representations of the intensity distribution.

## Features

- Single-slit diffraction simulation
- N-slit diffraction simulation
- User-defined wavelength
- User-defined slit width
- User-defined slit separation for N-slit diffraction
- User-defined number of slits
- User-defined screen distance
- Numerical intensity calculation
- `.dat` data-file generation
- Automatic GNUplot graph generation
- PNG graph output
- Automatic opening of generated graphs
- Modular C program structure

## Project Structure

```text
DiffractionLab/
├── README.md
├── src/
│   ├── main.c
│   ├── single_slit.c
│   ├── single_slit.h
│   ├── n_slit.c
│   └── n_slit.h
├── data/
│   ├── single_slit.dat
│   └── n_slit.dat
├── graphs/
│   ├── single_slit.png
│   └── n_slit.png
├── plot_single_slit.gp
├── plot_n_slit.gp
└── diffractionlab.exe
```

## Physics Used

### 1. Single-Slit Diffraction

The intensity distribution is given by:

\[
I = I_0\left(\frac{\sin\beta}{\beta}\right)^2
\]

where

\[
\beta = \frac{\pi a\sin\theta}{\lambda}
\]

Here:

- \(I\) = intensity at a point on the screen
- \(I_0\) = maximum central intensity
- \(a\) = slit width
- \(\lambda\) = wavelength
- \(\theta\) = diffraction angle

The condition for the first minimum is:

\[
a\sin\theta = \lambda
\]

For small angles:

\[
y_1 \approx \frac{\lambda L}{a}
\]

where \(L\) is the screen distance.

### 2. N-Slit Diffraction

For N identical slits, the intensity is modeled as:

\[
I = I_0
\left(\frac{\sin\beta}{\beta}\right)^2
\left(\frac{\sin(N\alpha)}{\sin\alpha}\right)^2
\]

where

\[
\beta = \frac{\pi a\sin\theta}{\lambda}
\]

and

\[
\alpha = \frac{\pi d\sin\theta}{\lambda}
\]

Here:

- \(N\) = number of slits
- \(a\) = slit width
- \(d\) = slit separation
- \(\lambda\) = wavelength
- \(\theta\) = diffraction angle

The program normalizes the N-slit intensity by \(N^2\) so that the plotted intensity has a convenient relative scale.

## Software and Tools

- C programming language
- GCC compiler
- GNUplot
- Visual Studio Code
- Windows
- MSYS2 UCRT64

## How to Compile

Open the terminal inside the DiffractionLab project directory and run:

```bash
gcc src/main.c src/single_slit.c src/n_slit.c -o diffractionlab.exe -lm
```

## How to Run

```bash
./diffractionlab.exe
```

On Windows PowerShell:

```powershell
.\diffractionlab.exe
```

The program displays a menu:

```text
================================
       DIFFRACTION LAB
================================
1. Single-Slit Diffraction
2. N-Slit Diffraction
3. Exit
```

## Example Inputs

### Single-Slit

```text
Wavelength: 600 nm
Slit width: 0.1 mm
Screen distance: 1 m
```

The program calculates the first diffraction minimum and generates the corresponding intensity graph.

### N-Slit

```text
Wavelength: 600 nm
Slit width: 0.1 mm
Slit separation: 0.5 mm
Number of slits: 5
Screen distance: 1 m
```

The program generates an N-slit diffraction pattern containing sharp principal maxima.

## Output

The simulator generates numerical data files:

```text
data/single_slit.dat
data/n_slit.dat
```

and graphical output:

```text
graphs/single_slit.png
graphs/n_slit.png
```

GNUplot is used to convert the calculated numerical data into PNG graphs.

## Working Principle

The overall workflow of DiffractionLab is:

```text
User Input
    ↓
Unit Conversion
    ↓
Physics Calculation
    ↓
Intensity Calculation
    ↓
Data File Generation
    ↓
GNUplot
    ↓
PNG Graph
    ↓
Automatic Graph Opening
```

## Learning Objectives

This project demonstrates:

- Application of wave-optics equations
- Numerical computation using C
- Floating-point calculations
- Unit conversion
- Mathematical functions such as `sin()`, `sqrt()`, `asin()`, and `fabs()`
- File handling in C
- Modular programming using header and source files
- Data visualization using GNUplot
- Integration of C programs with external plotting software

## Future Scope

Possible improvements include:

- Comparison of diffraction patterns for different values of N
- Interactive parameter control
- Automatic comparison between 2-slit, 3-slit, 5-slit, and 10-slit systems
- More detailed graph annotations
- Calculation of fringe positions
- GUI-based interface
- Export of simulation results to additional formats

## Conclusion

DiffractionLab provides a computational demonstration of single-slit and N-slit diffraction. By combining physics equations, numerical calculations, C programming, and GNUplot visualization, the project provides an interactive way to study how wavelength, slit dimensions, slit separation, and the number of slits affect diffraction patterns.