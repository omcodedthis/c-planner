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


// global arrays & variables
char *all_duty_types[7] = {"DUTY1", "DUTY2", "DUTY3", "DUTY4", "DUTY5", "DUTY6", "DUTY7"};
int all_duty_hours[7] = {8, 16, 28, 31, 13, 4, 4};


// function prototyping
void get_names(int strength, individual_schedule whole_schedule[]);
void plan_schedule(int strength, individual_schedule whole_schedule[]);
void print_schedule(int strength, individual_schedule whole_schedule[]);
int random_int(int lower, int upper);



int main(void)
{

    int strength = get_int("Total People:");

    individual_schedule whole_schedule[strength];

    get_names(strength, whole_schedule);

    plan_schedule(strength, whole_schedule);

    print_schedule(strength, whole_schedule);

}



void get_names(int strength, individual_schedule whole_schedule[])
{
    for (int i = 0; i < strength; i++)
    {
       whole_schedule[i].name = get_string("Enter Name:");
    }
}


void plan_schedule(int strength, individual_schedule whole_schedule[])
{
    int i_length = 16;

    for (int a = 0; a < strength; a++)
    {
        for(int b = 0; b < i_length; b++)
        {
            whole_schedule[a].all_duty_blocks[b].is_duty = false;
            whole_schedule[a].all_duty_blocks[b].duty_type = "NONE";
        }
    }


    // 8pm to 9pm duty
    for (int i = 0; i < 4; i++)
    {
        int random = random_int(0 , strength);
        int random_duty = random_int(1 , 4);

        whole_schedule[random].all_duty_blocks[0].duty_type = all_duty_types[random_duty];
        whole_schedule[random].all_duty_blocks[0].is_duty = true;
        all_duty_hours[random_duty] --;

    }


    // 0700 to 0900 duty
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

    // 1700 to 1900 duty
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

    // main day duty
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


            int random_duty = random_int(1 , 4);
            whole_schedule[l].all_duty_blocks[p].duty_type = all_duty_types[random_duty];
            whole_schedule[l].all_duty_blocks[p].is_duty = true;
            all_duty_hours[random_duty]--;
        }
    }
}


void print_schedule(int strength, individual_schedule whole_schedule[])
{
    int i_length = 16;

    for (int l = 0; l < strength; l++)
    {
        printf("%-8s", whole_schedule[l].name);
        printf("    ||");
        for (int p = 0; p < i_length; p++)
        {

             if (p == 1)
             {
                printf("%-6s", whole_schedule[l].all_duty_blocks[p].duty_type);
                printf("|____|____|____|____|____|____|");
                continue;
             }
             printf("%-6s", whole_schedule[l].all_duty_blocks[p].duty_type);
             printf("|____|");

        }
        printf("\n");
    }
}

int random_int(int lower, int upper)
{
    int num;
    for (int i = 0; i < 1; i++)
    {
        num = (rand() % (upper - lower + 1)) + lower;
    }
    return num;
}