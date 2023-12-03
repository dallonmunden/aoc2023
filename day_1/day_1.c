#include <stdio.h>

#define DEBUG 1

int get_line_digits(char buff[255], int length);
int get_line_digits_two(char buff[255], int length);
int get_line_length(char buff[255]);
void debug_info(char buff[255], int length);

int main()
{
    FILE *fp;
    char buff[255];
    int sum_p1 = 0;
    int sum_p2 = 0;
    int line_value;
    int line_length;

    fp = fopen("./input.txt", "r");

    for (int i = 0; i < 1000; i++)
    {
        fgets(buff, 255, fp);
        // apply logic / computes
        line_length = get_line_length(buff);
        line_value = get_line_digits(buff, line_length);
        sum_p1 = sum_p1 + line_value;
        line_value = get_line_digits_two(buff, line_length);
        sum_p2 = sum_p2 + line_value;
        if (DEBUG)
        {
            debug_info(buff, line_length);
        }
    }

    printf("ANS: %i \n", sum_p1);
    printf("ANS: %i \n", sum_p2);

    return 0;
}

int get_line_digits_two(char buff[255], int length)
{
    int value[2] = {0, 0};
    int len_number;
    int forward_match = 0;
    int backward_match = 0;
    char *numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            forward_match = 1;
            backward_match = 1;
            len_number = get_line_length(numbers[j]);
            for (int k = 0; k < len_number; k++)
            {
                if (!(buff[i + k] == numbers[j][k]))
                {
                    forward_match = 0;
                    break;
                }
            }
            for (int k = 0; k < len_number; k++)
            {
                if (!(buff[length - i - len_number + k] == numbers[j][k]))
                {
                    backward_match = 0;
                    break;
                }
            }
            if (forward_match && !value[0])
            {
                value[0] = j + 1;
            }
            if (backward_match && !value[1])
            {
                value[1] = j + 1;
            }
        }
        if (buff[i] >= 48 && buff[i] <= 57 && !value[0])
        {
            value[0] = buff[i] - 48;
        }
        if (buff[length - i - 1] >= 48 && buff[length - i - 1] <= 57 && !value[1])
        {
            value[1] = buff[length - i - 1] - 48;
        }
        if (value[0] && value[1])
        {
            break;
        }
    }

    return value[0] * 10 + value[1];
}

int get_line_digits(char buff[255], int length)
{
    int value[2] = {0, 0};

    for (int i = 0; i < length; i++)
    {
        if (buff[i] >= 48 && buff[i] <= 57 && !value[0])
        {
            value[0] = buff[i];
        }
        if (buff[length - i - 1] >= 48 && buff[length - i - 1] <= 57 && !value[1])
        {
            value[1] = buff[length - i - 1];
        }
        if (value[0] && value[1])
        {
            break;
        }
    }

    return (value[0] - 48) * 10 + (value[1] - 48);
}

int get_line_length(char buff[255])
{
    int length;
    for (int i = 0; i < 255; i++)
    {
        if (buff[i] == 10 || buff[i] == 0)
        {
            length = i;
            break;
        }
    }
    return length;
}

void debug_info(char buff[255], int length)
{
    puts(buff);
    printf("\n %i \n", length);
}