#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s \"input_string\" [options : -n , -o ]\n", argv[0]);
        return 1;
    }

    const char *str = argv[1];
    char str2[strlen(str) + 1];

    for (int i = 0; i < strlen(str); i++)
    {
        for (char j = ' '; j <= str[i]; j++)
        {
            str2[i] = j;
            str2[i + 1] = '\0';
            printf("%s\n", str2);
            usleep(10000);

            if (strncmp(argv[2], "-n", 2))
            {
                system("clear");
            }
        }
    }

    printf("\n%s\n\n", str2);

    return 0;
}
