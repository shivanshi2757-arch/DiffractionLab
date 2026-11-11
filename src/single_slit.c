#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "single_slit.h"

void single_slit_simulation(void)
{
    double wavelength_nm;
    double slit_width_mm;
    double screen_distance;
    double wavelength;
    double slit_width;

    printf("\n================================\n");
    printf("     SINGLE-SLIT DIFFRACTION\n");
    printf("================================\n");

    printf("\nEnter wavelength (nm): ");
    if (scanf("%lf", &wavelength_nm) != 1 || wavelength_nm <= 0)
    {
        printf("Invalid wavelength.\n");
        return;
    }

    printf("Enter slit width (mm): ");
    if (scanf("%lf", &slit_width_mm) != 1 || slit_width_mm <= 0)
    {
        printf("Invalid slit width.\n");
        return;
    }

    printf("Enter screen distance (m): ");
    if (scanf("%lf", &screen_distance) != 1 || screen_distance <= 0)
    {
        printf("Invalid screen distance.\n");
        return;
    }

    /*
       Convert to SI units
    */
    wavelength = wavelength_nm * 1e-9;
    slit_width = slit_width_mm * 1e-3;

    if (wavelength > slit_width)
    {
        printf("\nError: Wavelength cannot be greater than slit width.\n");
        return;
    }

    /*
       Physics:
       I = I0 [sin(beta) / beta]^2

       beta = pi * a * sin(theta) / lambda

       First minimum:
       a sin(theta) = lambda
    */

    double theta = asin(wavelength / slit_width);

    double first_minimum =
        screen_distance * tan(theta);

    printf("\n--------------------------------\n");
    printf("Single-Slit Diffraction Result\n");
    printf("--------------------------------\n");

    printf("Wavelength       : %.2f nm\n", wavelength_nm);
    printf("Slit width       : %.4f mm\n", slit_width_mm);
    printf("Screen distance  : %.2f m\n", screen_distance);

    printf("\nFirst diffraction minimum: %.4f mm\n",
           first_minimum * 1000.0);

    printf("\nPhysics used:\n");
    printf("Intensity: I = I0 [sin(beta)/beta]^2\n");
    printf("beta = pi*a*sin(theta)/lambda\n");
    printf("First minimum: a sin(theta) = lambda\n");

    /*
       Open data file
    */
    FILE *file = fopen("data/single_slit.dat", "w");

    if (file == NULL)
    {
        printf("\nError: Could not create data file.\n");
        return;
    }

    /*
       Generate intensity data
    */
    double graph_range = first_minimum * 2.5;

    for (int i = -400; i <= 400; i++)
    {
        double x =
            (i / 400.0) * graph_range;

        double sin_theta =
            x / sqrt(x * x +
                     screen_distance * screen_distance);

        double beta =
            (M_PI * slit_width * sin_theta)
            / wavelength;

        double intensity;

        /*
           At beta = 0,
           sin(beta)/beta -> 1
        */
        if (fabs(beta) < 1e-12)
        {
            intensity = 1.0;
        }
        else
        {
            double ratio =
                sin(beta) / beta;

            intensity =
                ratio * ratio;
        }

        fprintf(file, "%.6f %.6f\n",
                x * 1000.0,
                intensity);
    }

    fclose(file);

    printf("\nData generated successfully.\n");

    /*
       Create GNUplot script
    */
    FILE *plot =
        fopen("plot_single_slit.gp", "w");

    if (plot == NULL)
    {
        printf("Error: Could not create GNUplot script.\n");
        return;
    }

    fprintf(plot,
            "set terminal pngcairo size 1200,700\n");

    fprintf(plot,
            "set output 'graphs/single_slit.png'\n");

    fprintf(plot,
            "set title 'Single-Slit Diffraction Pattern'\n");

    fprintf(plot,
            "set xlabel 'Screen Position (mm)'\n");

    fprintf(plot,
            "set ylabel 'Relative Intensity'\n");

    fprintf(plot,
            "set grid\n");

    fprintf(plot,
            "set key top right\n");

    fprintf(plot,
            "set border linewidth 1.5\n");

    fprintf(plot,
            "plot 'data/single_slit.dat' using 1:2 "
            "with lines linewidth 2 "
            "title 'Single-Slit Diffraction'\n");

    fclose(plot);

    /*
       Run GNUplot
    */
    int result =
        system("gnuplot plot_single_slit.gp");

    if (result == 0)
    {
        printf("Graph generated successfully.\n");

        /*
           Automatically open graph
        */
        system("start \"\" \"graphs\\single_slit.png\"");
    }
    else
    {
        printf("Error: GNUplot could not generate the graph.\n");
    }
}