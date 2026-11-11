#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "n_slit.h"

void n_slit_simulation(void)
{
    double wavelength_nm;
    double slit_width_mm;
    double slit_separation_mm;
    double screen_distance;
    int number_of_slits;

    double wavelength;
    double slit_width;
    double slit_separation;

    printf("\n================================\n");
    printf("        N-SLIT DIFFRACTION\n");
    printf("================================\n");

    printf("\nEnter wavelength (nm): ");
    if (scanf("%lf", &wavelength_nm) != 1 ||
        wavelength_nm <= 0)
    {
        printf("Invalid wavelength.\n");
        return;
    }

    printf("Enter slit width (mm): ");
    if (scanf("%lf", &slit_width_mm) != 1 ||
        slit_width_mm <= 0)
    {
        printf("Invalid slit width.\n");
        return;
    }

    printf("Enter slit separation (mm): ");
    if (scanf("%lf", &slit_separation_mm) != 1 ||
        slit_separation_mm <= 0)
    {
        printf("Invalid slit separation.\n");
        return;
    }

    printf("Enter number of slits: ");
    if (scanf("%d", &number_of_slits) != 1 ||
        number_of_slits < 2)
    {
        printf("Number of slits must be at least 2.\n");
        return;
    }

    printf("Enter screen distance (m): ");
    if (scanf("%lf", &screen_distance) != 1 ||
        screen_distance <= 0)
    {
        printf("Invalid screen distance.\n");
        return;
    }

    /*
       Convert to SI units
    */
    wavelength = wavelength_nm * 1e-9;
    slit_width = slit_width_mm * 1e-3;
    slit_separation = slit_separation_mm * 1e-3;

    /*
       N-Slit Diffraction:

       I = I0 [sin(beta)/beta]^2
           [sin(N*alpha)/sin(alpha)]^2

       beta  = pi*a*sin(theta)/lambda
       alpha = pi*d*sin(theta)/lambda

       a = slit width
       d = slit separation
       N = number of slits
    */

    printf("\n--------------------------------\n");
    printf("N-Slit Diffraction Result\n");
    printf("--------------------------------\n");

    printf("Wavelength       : %.2f nm\n",
           wavelength_nm);

    printf("Slit width       : %.4f mm\n",
           slit_width_mm);

    printf("Slit separation  : %.4f mm\n",
           slit_separation_mm);

    printf("Number of slits  : %d\n",
           number_of_slits);

    printf("Screen distance  : %.2f m\n",
           screen_distance);

    printf("\nPhysics used:\n");

    printf("I = I0 [sin(beta)/beta]^2 "
           "[sin(N*alpha)/sin(alpha)]^2\n");

    printf("beta = pi*a*sin(theta)/lambda\n");

    printf("alpha = pi*d*sin(theta)/lambda\n");

    /*
       Open data file
    */
    FILE *file =
        fopen("data/n_slit.dat", "w");

    if (file == NULL)
    {
        printf("\nError: Could not create data file.\n");
        return;
    }

    /*
       Generate intensity data
    */
    double graph_range =
    screen_distance * wavelength / slit_separation * 5.0;

    for (int i = -500; i <= 500; i++)
    {
        double x =
            (i / 500.0) * graph_range;

        /*
           sin(theta) from screen geometry
        */
        double sin_theta =
            x / sqrt(x * x +
                     screen_distance *
                     screen_distance);

        /*
           Single-slit envelope parameter
        */
        double beta =
            (M_PI *
             slit_width *
             sin_theta)
            / wavelength;

        /*
           Multi-slit interference parameter
        */
        double alpha =
            (M_PI *
             slit_separation *
             sin_theta)
            / wavelength;

        double single_slit_factor;

        /*
           Calculate single-slit envelope
        */
        if (fabs(beta) < 1e-12)
        {
            single_slit_factor = 1.0;
        }
        else
        {
            double ratio =
                sin(beta) / beta;

            single_slit_factor =
                ratio * ratio;
        }

        /*
           Calculate N-slit interference factor
        */
        double multi_slit_factor;

        if (fabs(alpha) < 1e-12)
        {
            multi_slit_factor =
                number_of_slits *
                number_of_slits;
        }
        else
        {
            double ratio =
                sin(number_of_slits *
                    alpha)
                / sin(alpha);

            multi_slit_factor =
                ratio * ratio;
        }

        /*
           Normalize intensity
           so that maximum intensity
           is approximately 1.
        */
        double intensity =
            single_slit_factor *
            multi_slit_factor /
            (number_of_slits *
             number_of_slits);

        fprintf(file,
                "%.6f %.6f\n",
                x * 1000.0,
                intensity);
    }

    fclose(file);

    printf("\nData generated successfully.\n");

    /*
       Create GNUplot script
    */
    FILE *plot =
        fopen("plot_n_slit.gp", "w");

    if (plot == NULL)
    {
        printf("Error: Could not create GNUplot script.\n");
        return;
    }

    fprintf(plot,
            "set terminal pngcairo size 1200,700\n");

    fprintf(plot,
            "set output 'graphs/n_slit.png'\n");

    fprintf(plot,
            "set title 'N-Slit Diffraction Pattern'\n");

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
            "plot 'data/n_slit.dat' using 1:2 "
            "with lines linewidth 2 "
            "title 'N-Slit Diffraction'\n");

    fclose(plot);

    /*
       Run GNUplot
    */
    int result =
        system("gnuplot plot_n_slit.gp");

    if (result == 0)
    {
        printf("Graph generated successfully.\n");

        /*
           Automatically open graph
        */
        system("start \"\" \"graphs\\n_slit.png\"");
    }
    else
    {
        printf("Error: GNUplot could not generate the graph.\n");
    }
}