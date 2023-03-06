#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// structs
typedef struct
{
    bool is_duty;
    char *duty_type;
}
duty_block;

typedef struct
{
    duty_block all_duty_blocks[16];
    char *name;
}
individual_schedule;


// global arrays & variables, the size is limited to 16 to ensure sufficient slots
// for each duty type & its respective hours.
char *all_duty_types[16];
int all_duty_hours[16];

// ANSI Color Codes
#define W_UNDERLINE "\e[4;37m"  // Underlined White text
#define GREEN "\e[0;32m"  // Regular text
#define YELLOW "\e[1;33m"  // Bold
#define RESET "\e[0m"

// function prototyping
int get_duties(void);
void get_names(int strength, individual_schedule whole_schedule[]);
void plan_schedule(int strength, individual_schedule whole_schedule[], int total_duties);
void print_schedule(int strength, individual_schedule whole_schedule[]);
int random_int(int lower, int upper);


// main() gets the duty types & its respective values from the user. The strength (total number of people) is assigned from
// the user & their respective names. The schedule is then planned & printed to the terminal.
int main(void)
{

    int total_duties = get_duties();

    int strength = get_int("Total People:");

    individual_schedule whole_schedule[strength];

    get_names(strength, whole_schedule);

    plan_schedule(strength, whole_schedule, total_duties);

    print_schedule(strength, whole_schedule);

}


// get_duties() asks the user for the total types of duties. The for-loop asks the user for the duty type and its respective
// hours, repeating for the total of the types of duty.
int get_duties(void)
{
    int total_duties = get_int("How many duties?:");

    for (int i = 0; i < total_duties; i++)
    {
        all_duty_types[i] = get_string("Duty Name:");
        all_duty_hours[i] = get_int("Total hours for this duty:");
    }

    printf("+--------------------------+\n");

    return total_duties;
}



// get_names() using the strength previously asked by the user, asks the user for each name part of this strength.
void get_names(int strength, individual_schedule whole_schedule[])
{
    for (int i = 0; i < strength; i++)
    {
       whole_schedule[i].name = get_string("Enter Name:");
    }
}


// plan_schedule() uses multiple for-loops to plan the schedule. i_length represents the total possible slots for each person.
void plan_schedule(int strength, individual_schedule whole_schedule[], int total_duties)
{
    int i_length = 16;

// This for-loop assigns a default value to each slot in the array to prevent segmentation faults from occuring.
    for (int a = 0; a < strength; a++)
    {
        for(int b = 0; b < i_length; b++)
        {
            whole_schedule[a].all_duty_blocks[b].is_duty = false;
            whole_schedule[a].all_duty_blocks[b].duty_type = "BREAK";
        }
    }


// This for-loop plans the duty schedule for the hours of 2000 to 2100hrs. The person decided for duty is chosen
// randomly & given a random duty. The person's duty_type, is_duty is then assigned its respective value. The
// total duty_hours for this respective duty is subtracted by one.
    for (int i = 0; i < 4; i++)
    {
        int random = random_int(0 , strength);
        int random_duty = random_int(0 , total_duties);

        whole_schedule[random].all_duty_blocks[0].duty_type = all_duty_types[random_duty];
        whole_schedule[random].all_duty_blocks[0].is_duty = true;
        all_duty_hours[random_duty] --;

    }


// This for-loop plans the duty schedule for the hours of 0700 to 0900hrs. The person decided for duty is chosen
// randomly & given a random duty. The person's duty_type, is_duty is then assigned its respective value. The
// total duty_hours for this respective duty is subtracted by one.
    for (int j = 0; j < 4; j++)
    {
        int random = random_int(0 , strength);

        whole_schedule[random].all_duty_blocks[3].duty_type = all_duty_types[0];
        whole_schedule[random].all_duty_blocks[3].is_duty = true;
        all_duty_hours[0] --;

        whole_schedule[random].all_duty_blocks[4].duty_type = all_duty_types[0];
        whole_schedule[random].all_duty_blocks[4].is_duty = true;
        all_duty_hours[0] --;

    }



// This for-loop plans the duty schedule for the hours of 1700 to 1900hrs. The person decided for duty is chosen
// randomly & given a random duty. The person's duty_type, is_duty is then assigned its respective value. The
// total duty_hours for this respective duty is subtracted by one.
    for (int k = 0; k < 4; k++)
    {
        int random = random_int(0 , strength);

        whole_schedule[random].all_duty_blocks[14].duty_type = all_duty_types[0];
        whole_schedule[random].all_duty_blocks[14].is_duty = true;
        all_duty_hours[0] --;

        whole_schedule[random].all_duty_blocks[15].duty_type = all_duty_types[0];
        whole_schedule[random].all_duty_blocks[15].is_duty = true;
        all_duty_hours[0] --;

    }



// This nested for-loop plans the duty schedule for the remaining hours. The person decided for duty is chosen randomly &
// given a random duty. The person's duty_type, is_duty is then assigned its respective value. Thetotal duty_hours for
//  this respective duty is subtracted by one. To determine the appropriate amount of breaks, if the currenthour is greater
// than 0900 with a probability of 50%, the current person will receive a break if they had a duty 4 hours ago or a
// consecutive 2 hours of duty.
    for (int l = 0; l < strength; l++)
    {
        for (int p = 2; p < i_length; p++)
        {

            if ((p > 4)  && random_int(0, 1))
            {
                if (((whole_schedule[l].all_duty_blocks[p - 4].is_duty)))
                {
                    whole_schedule[l].all_duty_blocks[p].duty_type = "BREAK";
                    continue;
                }

                if (((whole_schedule[l].all_duty_blocks[p - 1].is_duty)) && ((whole_schedule[l].all_duty_blocks[p - 2].is_duty)))
                {
                    whole_schedule[l].all_duty_blocks[p].duty_type = "BREAK";
                    continue;
                }

            }
            int random_duty = random_int(0 , total_duties);
            whole_schedule[l].all_duty_blocks[p].duty_type = all_duty_types[random_duty];
            whole_schedule[l].all_duty_blocks[p].is_duty = true;
            all_duty_hours[random_duty]--;
        }
    }

    for (int g = 0; g < strength; g++)
    {
        for(int f = 0; f < i_length; f++)
        {
            if (whole_schedule[g].all_duty_blocks[f].duty_type == NULL)
            {
                 whole_schedule[g].all_duty_blocks[f].duty_type = "BREAK";
            }
        }
    }
}



// print_schedule() prints the schedule. This nested for-loop prints the name, and the respective schedule for this person
// for the 24hr period.
void print_schedule(int strength, individual_schedule whole_schedule[])
{
    int i_length = 16;

    // prints the row for the times for each slot
    printf(W_UNDERLINE"%-10s"RESET, "   TIMINGS");
    printf(W_UNDERLINE"  ||2000  |2100  ||____|____|____|____|____|____|0600  |0700  |0800  |0900  |1000  |1100  |1200  |1300  |1400  |1500  |1600  |1700  |1800  |1900  |"RESET);
    printf("\n");

    for (int l = 0; l < strength; l++)
    {
        printf("%-8s", whole_schedule[l].name);
        printf("    ||");
        for (int p = 0; p < i_length; p++)
        {
            // case for the slot that starts at 2100, signifying the last slot for the day
            if (p == 1)
            {
                if (!(strcmp(whole_schedule[l].all_duty_blocks[p].duty_type, "BREAK")))
                {
                    printf(GREEN"%-6s"RESET, whole_schedule[l].all_duty_blocks[p].duty_type);
                    printf("|");
                }

                else
                {
                    printf(YELLOW"%-6s"RESET, whole_schedule[l].all_duty_blocks[p].duty_type);
                    printf("|");
                }

                printf("|____|____|____|____|____|____|");
                continue;
            }

            // for all the other slots
            if (!(strcmp(whole_schedule[l].all_duty_blocks[p].duty_type, "BREAK")))
            {
                printf(GREEN"%-6s"RESET, whole_schedule[l].all_duty_blocks[p].duty_type);
                printf("|");
            }

            else
            {
                printf(YELLOW"%-6s"RESET, whole_schedule[l].all_duty_blocks[p].duty_type);
                printf("|");
            }

        }
    // "new line" added before moving onto the next row
    printf("\n");
    }
}


// random_int() takes in 2 numbers, max & min values. It then returns a random integer between these two values.
int random_int(int lower, int upper)
{
    int num;
    for (int i = 0; i < 1; i++)
    {
        num = (rand() % (upper - lower + 1)) + lower;
    }
    return num;
}