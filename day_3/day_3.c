#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int check_part_numbers(char lines[3][255]);
int check_part_numbers_p2(char lines[3][255]);
bool is_symbol(char c);
bool is_num(char c);
unsigned short get_num(char *line, unsigned char ind);

int main(int argc, char const *argv[])
{
    FILE *fp;
    char lines[3][255];
    fpos_t position;
    fp = fopen("./input.txt", "r");

    position = 0;

    unsigned long int sum_parts = 0;
    unsigned long int sum_gears = 0;

    // need triple line.
    for (int i = 0; i < 140; i++)
    {
        switch (i)
        {
        case 0:
            memset(&lines[0], 0, 255);
            memset(&lines[1], 0, 255);
            memset(&lines[2], 0, 255);
            fgetpos(fp, &position);
            fgets(lines[1], 255, fp);
            fgets(lines[2], 255, fp);
            break;
        case 139:
            fsetpos(fp, &position);
            fgets(lines[0], 255, fp);
            fgetpos(fp, &position);
            fgets(lines[1], 255, fp);
            memset(&lines[2], 0, 255);
            break;
        default:
            fsetpos(fp, &position);
            fgets(lines[0], 255, fp);
            fgetpos(fp, &position);
            fgets(lines[1], 255, fp);
            fgets(lines[2], 255, fp);
        }
        sum_parts = sum_parts + check_part_numbers(lines);
        sum_gears = sum_gears + check_part_numbers_p2(lines);
    }

    printf("\n\n%lu\n\n", sum_parts);
    printf("\n\n%lu\n\n", sum_gears);
    return 0;
}

int check_part_numbers_p2(char lines[3][255])
{
    // want to consider dimensions : i(column index) start of number in row j
    // we care about (i - 1) to (i + numlength + 1) for row j, j-1, j+1.
    // we look entirely through array lines[1].
    int gear_array[2] = {0, 0};
    char array_ind = 0;
    int gear_ratio = 0;
    int gear_ratio_sum = 0;
    bool already_used = false;

    for (int i = 0; i < 255; i++)
    {
        // check the surrounding elements if you find a star.
        if (lines[1][i] == '*')
        {
            gear_array[0] = gear_array[1] = 0;
            for (int j = 0; j < 3; j++)
            {
                already_used = false;
                for (int k = -1; k < 2; k++)
                {
                    // want to check if the lines[1][ind] is num
                    // you can have more than 1 number per line but dont take the same number twice :/
                    if (!already_used && is_num(lines[j][i + k + (!(k + 1) & !i)]))
                    {
                        gear_array[!!gear_array[0]] = get_num(lines[j], i + k + (!(k + 1) & !i));
                        already_used = true;
                        // break;
                    }
                    else if (!is_num(lines[j][i + k + (!(k + 1) & !i)]))
                    {
                        already_used = false;
                    }
                }
            }
        }

        if (gear_array[0] && gear_array[1])
        {
            gear_ratio_sum = gear_ratio_sum + (gear_array[0] * gear_array[1]);
            gear_array[0] = gear_array[1] = 0;
        }
        else if (lines[1][i] == '\n' || lines[1][i] == '\000')
        {
            break;
        }
    }

    return gear_ratio_sum;
}

int check_part_numbers(char lines[3][255])
{
    // want to consider dimensions : i(column index) start of number in row j
    // we care about (i - 1) to (i + numlength + 1) for row j, j-1, j+1.
    // we look entirely through array lines[1].
    int part_sum = 0;
    int add_num = 0;
    bool record = false;

    for (int i = 0; i < 255; i++)
    {
        // can also set something to break if /n or /000.
        // is the element lines[1][i] a number?
        if (lines[1][i] >= 48 && lines[1][i] <= 57)
        {
            add_num = add_num * 10 + (lines[1][i] - 48);
            // find adjacent element and tell if its inside the same number symbol found.
            // will also need to consider if i - 1 or i + 1 exists. can be done using XOR (^) operations.
            // can techincally not worry about i+1 case since buff longer than str and will break loop completes.
            if (!record)
            {
                for (int j = 0; j < 3; j++)
                {
                    for (int k = -1; k < 2; k++)
                    {
                        // want (!!i ^ 1) = + 1 when k=-1, i=0, !!i^1 = 1 when i=0
                        // record = record || is_symbol(lines[j][i + k + (!(k + 1) & (!!i ^ 1))]);
                        record = record || is_symbol(lines[j][i + k + (!(k + 1) & !i)]);
                    }
                }
            }
        }
        else if (record)
        {
            part_sum = part_sum + add_num;
            add_num = 0;
            record = false;
        }
        else if (lines[1][i] == '\n' || lines[1][i] == '\000')
        {
            break;
        }
        else
        {
            add_num = 0;
        }
    }
    return part_sum;
}

unsigned short get_num(char *line, unsigned char ind)
{
    // check if ind is zero probably. check if the char at the ind is not an int is when stop
    // find the bounds. backward pass till either ind is zero or line[ind] is non number.

    unsigned char start_bound = 0;
    unsigned short number = 0;

    // back pass
    for (int i = 0; i < 255; i++)
    {
        if (((ind - 1) < 0) || !is_num(line[ind - i]))
        {
            start_bound = ind - i + 1;
            break;
        }
    }

    // forward pass. could probably just use while loop check for non number. getting lazy.
    for (int i = 0; i < 255; i++)
    {
        if (is_num(line[start_bound + i]))
        {
            number = number * 10 + (line[start_bound + i] - 48);
        }
        else
        {
            break;
        }
    }

    return number;
}

bool is_symbol(char c)
{
    // is symbol would imply not '.', any number, '\n', '\000'.
    if ((c >= 48 && c <= 57) || c == '.' || c == '\n' || c == 0)
    {
        return false;
    }
    else
        return true;
}

bool is_num(char c)
{
    if (c >= 48 && c <= 57)
    {
        return true;
    }
    else
        return false;
}