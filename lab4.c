#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void add_text(char **buff);
int search_word(char **buff);
void edit_text(char **buff);
int search_id(char **buff, char **searc);

int main(void)
{
    while (1)
    {
        int n;
        char *buff;

        FILE *text = fopen("buffer.txt", "r");
        char buf_l[1000]; 
        fgets(buf_l, sizeof(buf_l), text);

        if (strcmp(buf_l, "0") == 0)
        {
            buff = malloc(sizeof(char));
            if (buff == NULL)
            {
                printf("Memory error! \n");
                free(buff);
                return 1;
            }
            buff[0] = '\0';
        }
        else
        {
            int size = atoi(buf_l);
            buff = malloc(sizeof(char) * size);
            if (buff == NULL)
            {
                printf("Memory error! \n");
                free(buff);
                return 1;
            }
            fgets(buff, size, text);
        }
        fclose(text);
        printf("Your text: \n");
        printf("%s \n", buff);
        printf("\n");

        printf("Type 1 to add text. \n");
        printf("Type 2 to search for word. \n");
        printf("Type 3 to edit text. \n");
        printf("Type 4 to delete the whole text. \n");
        printf("Type 0 to exit. \n");

        do
        {
            scanf("%d", &n);
            if(n < 0 || n > 4)
            {
                printf("Incorect number, enter one more time\n");
            }
            while(getchar() != '\n');
        } while (n < 0 || n > 4);

        if (n == 1)
        {
            add_text(&buff);
            FILE *wrt = fopen("buffer.txt", "w");
            int l = strlen(buff) + 1;
            char ll[1000];
            sprintf(ll,"%d", l);
            fprintf(wrt, "%s\n", ll);
            fprintf(wrt, "%s", buff);
            fclose(wrt);
            printf("%s\n", buff);
        }
        else if (n == 2)
        {
            printf("This word appears %i times in the text\n", search_word(&buff));
            fgetc(stdin);
        }
        else if (n == 3)
        {
            edit_text(&buff);
            FILE *wrt = fopen("buffer.txt", "w");
            int l = strlen(buff) + 1;
            char ll[1000];
            sprintf(ll,"%d", l);
            fprintf(wrt, "%s\n", ll);
            fprintf(wrt, "%s ", buff);
            fclose(wrt);
            printf("%s\n", buff);
        }
        else if (n == 4)
        {
            FILE *wrt = fopen("buffer.txt", "w");
            int l = 0;
            char ll[1000];
            sprintf(ll,"%d", l);
            fwrite(ll, sizeof(char), strlen(ll), wrt);
            fclose(wrt);
        }
        else if (n == 0)
        {
            free(buff);
            break;
        }
        printf ("\033[0d\033[2J");
    }
    printf ("\033[0d\033[2J");
    return 0;
}

// Adding the text to the buffer
void add_text(char **buff)
{
    char *temp;
    temp = malloc(sizeof(char) * 100);
    printf("Enter your text: \n");
    fgets(temp, 100, stdin);
    int l = strlen(temp);
    if (l > 0 && temp[l - 1] == '\n') {
        temp[l - 1] = '\0';
    }
    
    int len = strlen(*buff) + strlen(temp) + 1;
    *buff = realloc(*buff, sizeof(char) * len);
    if (*buff == NULL)
    {
        printf("Memory error! \n");
        free(*buff);
    }
    if (strlen(*buff) == 0)
    {
        snprintf(*buff, len, "%s%s", *buff, temp);
    }
    else
    {
        snprintf(*buff, len + 1, "%s %s", *buff, temp);
    }
    free(temp);
}
// search_word function
int search_word(char **buff)
{
    int amm = 0;
    int num = 0;
    char *searc;
    searc = malloc(sizeof(char) * 100);
    printf("Write the word: \n");
    fgets(searc, 100, stdin);
    
    char *temp;
    int sl = strlen(searc);
    (searc)[sl-1] = '\0';
    temp = malloc(sizeof(char) * sl);
    memset(temp, '\0', sl);

    if ((searc)[sl-2] == ' ')
    {
        for (int i = 0, n = strlen(*buff); i < n; i++)
        {
            char c = (*buff)[i];
            if (num == 0 && c == ' ') 
            {
                continue;
            }
            else
            {
                temp[num] = c;
            }
            if (c == ' ')
            {
                if (strcmp(searc, temp) == 0)
                {
                    amm++;
                    num = -1;
                    memset(temp, '\0', sl);
                }
                else
                {
                    num = -1;
                    memset(temp, '\0', sl);
                }
            }
            num++;
        }
    }
    else
    {
        for (int i = 0, n = strlen(*buff); i < n; i++)
        {
            char c = (*buff)[i];
            if (num == 0 && c == ' ') 
            {
                continue;
            }
            else
            {
                temp[num] = c;
            }
            if ((*buff)[i+1] == '\0' ||(*buff)[i+1] == ' ' || ispunct((*buff)[i+1]))
            {
                if (strcmp(searc, temp) == 0 && ((*buff)[i+1] == ' ' || (*buff)[i+1] == '\0' || ispunct((*buff)[i+1])))
                {
                    amm++;
                    num = -1;
                    memset(temp, '\0', sl);
                }
                else
                {
                    num = -1;
                    memset(temp, '\0', sl);
                }
            }
            num++;
        }  
    }
    free(searc);
    return amm;
}

// edit_text function
void edit_text(char **buff)
{
    char *temp;
    char *second_part;
    second_part = malloc(200);
    memset(second_part, '\0', 200);
    temp = malloc(sizeof(char) * 100);
    printf("Write the word you would like to change: \n");
    fgets(temp, 100, stdin);
    char *fw;
    fw = malloc(200);
    memset(fw, '\0', 200);
    int id = search_id(&(*buff), &temp);
    int si = id + strlen(temp);
    if (id == -1)
    {
        printf("There is no such word :(\n");
    }
    else
    {  
        strncpy(fw, *buff, id); 
        strcpy(second_part, (*buff)+si);
        char *the_word;
        the_word = malloc(sizeof(char) * 100);
        printf("Write the word you would like to be there: \n");
        fgets(the_word, 100, stdin);
        the_word[strlen(the_word)-1] = '\0';

        char *slice;
        slice = malloc(strlen(*buff) + strlen(the_word));
        memset(slice, '\0', (strlen(*buff) + strlen(the_word)));
        strcat(fw, the_word);
        strcat(fw, second_part);
        strcpy((*buff), fw);
        free(the_word);
        free(slice);
    }
} 

int search_id(char **buff, char **searc)
{
    int amm = 0;
    int num = 0;
    int id = -1;
    
    char *temp;
    int sl = strlen(*searc);
    (*searc)[sl-1] = '\0';
    temp = malloc(sizeof(char) * sl);
    memset(temp, '\0', sl);

    if ((*searc)[sl-2] == ' ')
    {
        for (int i = 0, n = strlen(*buff); i < n; i++)
        {
            char c = (*buff)[i];
            if (num == 0 && c == ' ') 
            {
                continue;
            }
            else
            {
                temp[num] = c;
            }
            if (c == ' ')
            {
                if (strcmp(*searc, temp) == 0)
                {
                    amm++;
                    memset(temp, '\0', sl);
                    if (amm == 1)
                    {
                        id = i - num;
                    }
                    num = -1;
                }
                else
                {
                    num = -1;
                    memset(temp, '\0', sl);
                }
            }
            num++;
        }
    }
    else
    {
        for (int i = 0, n = strlen(*buff); i < n; i++)
        {
            char c = (*buff)[i];
            if (num == 0 && c == ' ') 
            {
                continue;
            }
            else
            {
                temp[num] = c;
            }
            if ((*buff)[i+1] == '\0' ||(*buff)[i+1] == ' ' || ispunct((*buff)[i+1]))
            {
                if (strcmp(*searc, temp) == 0 && ((*buff)[i+1] == ' ' || (*buff)[i+1] == '\0' || ispunct((*buff)[i+1])))
                {
                    amm++;
                    if (amm == 1)
                    {
                        id = i - num;
                    }
                    num = -1;
                    memset(temp, '\0', sl);
                }
                else
                {
                    num = -1;
                    memset(temp, '\0', sl);
                }
            }
            num++;
        }  
    }
    return id;
}