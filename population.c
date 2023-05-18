#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Promting the user for the starting # of llamas
    int start;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);
    //Promting the user for the einding # of llamas
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);
    //How many years it will take to get to the goal?
    int years = 0;
    while (start < end)
    {
        //Every year, 1/3 of our current llamas are born; 1/4 pass away
        start = start + (start / 3) - (start / 4); //start += start/12;||start=start+start/12; do not work
        // Debugging:
        // printf ("start: %i\n", start);
        // printf ("Years: %i\n", years);
        // getchar();
        years++;
    }
    printf("Years: %i\n", years);
}
// check50 cs50/labs/2023/x/population
// style50 population.c
