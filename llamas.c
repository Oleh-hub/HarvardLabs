// llamas we have a population of n llamas.
//  Each year, n / 3 new llamas are born, and n / 4 llamas pass away.
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long start_size = 0;
    long goal_size = 0;

    while (start_size < 12)
        start_size = get_long("Start size of llamas: ");

    while (goal_size < start_size)
        goal_size = get_long("Goal size of llamas: ");

    int need_years = 0;
    long interm_size = start_size;
        while (interm_size < goal_size)
        {
            // interm_size = interm_size + (interm_size / 3) - (interm_size / 4);
            interm_size += interm_size / 12;
            need_years ++ ;
        }
        printf ("for this change %i year(s) needed\n", need_years);
    }
