#include <stdio.h>

// 12 r , 13 g , 14 b

#define SPACE 0b100000

int parse_game(char *stuff);
int parse_game_p2(char *stuff);

int main()
{
    FILE *fp;
    char buff[255];
    fp = fopen("./input.txt", "r");

    unsigned short sum_ids = 0;
    unsigned int sum_powers = 0;

    for (int i = 0; i < 100; i++)
    {
        fgets(buff, 255, fp);
        sum_ids = sum_ids + parse_game(buff);
        sum_powers = sum_powers + parse_game_p2(buff);
        puts(buff);
    }

    printf("\n\nANS: %i", sum_ids);
    printf("\n\nANS: %i", sum_powers);

    return 0;
}

int parse_game_p2(char *line)
{
    char answers[100];
    char red_max = 0;
    char blue_max = 0;
    char green_max = 0;
    char ans_ind = -1;
    char cnt;
    for (int i = 0; i < 255; i++)
    {
        if (line[i] >= 48 && line[i] <= 57 && !(line[i - 1] >= 48 && line[i - 1] <= 57))
        {
            cnt = 0;
            ans_ind = ans_ind + 1;
            answers[ans_ind] = 0;
            while (line[i + cnt] != SPACE && line[i + cnt] != ':')
            {
                answers[ans_ind] = answers[ans_ind] * 10 + (line[i + cnt] - 48);
                cnt = cnt + 1;
            }
        }
        else if (line[i] == 'r' && line[i - 1] != 'g' && (answers[ans_ind] > red_max))
        {
            red_max = answers[ans_ind];
        }
        else if (line[i] == 'g' && (answers[ans_ind] > green_max))
        {
            green_max = answers[ans_ind];
        }
        else if (line[i] == 'b' && (answers[ans_ind] > blue_max))
        {
            blue_max = answers[ans_ind];
        }
        else if (line[i] == 10 || line[i] == 0)
        {
            break;
        }
    }

    return red_max * green_max * blue_max;
}

int parse_game(char *line)
{
    char answers[100];
    char ans_ind = -1;
    char cnt;
    for (int i = 0; i < 255; i++)
    {
        if (line[i] >= 48 && line[i] <= 57 && !(line[i - 1] >= 48 && line[i - 1] <= 57))
        {
            cnt = 0;
            ans_ind = ans_ind + 1;
            answers[ans_ind] = 0;
            while (line[i + cnt] != SPACE && line[i + cnt] != ':')
            {
                answers[ans_ind] = answers[ans_ind] * 10 + (line[i + cnt] - 48);
                cnt = cnt + 1;
            }
        }
        else if (line[i] == 'r' && line[i - 1] != 'g' && answers[ans_ind] > 12)
        {
            return 0;
        }
        else if (line[i] == 'b' && answers[ans_ind] > 14)
        {
            return 0;
        }
        else if (line[i] == 'g' && answers[ans_ind] > 13)
        {
            return 0;
        }
        else if (line[i] == 10 || line[i] == 0)
        {
            break;
        }
    }

    return answers[0];
}