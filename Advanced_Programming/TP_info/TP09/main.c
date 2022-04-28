#define _GNU_SOURCE
#include "reponse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_list_ep (l_ep *p_list)
{
    Ep episode_null_template = {0,0,0,"","",0};

    (p_list)->dernier = 0;
    for (int i = 0; i < LIST_SIZE; i++)
    {
        (p_list)->episode[i] = episode_null_template;
    }
}

void ajout_ep (Ep epis, l_ep list)
{
    list.episode[list.dernier] = epis;
    list.dernier++;
}

void ajout_episode (char *line_buf, l_ep *list)
{
    char *tok = NULL;

    tok = strtok(line_buf,",");
    list->episode[list->dernier].season = atoi(tok);
    tok = strtok(NULL,",");
    list->episode[list->dernier].episode_num_in_season = atoi(tok);
    tok = strtok(NULL,",");
    list->episode[list->dernier].episode_num_overall = atoi(tok);
    tok = strtok(NULL,",");
    strcpy(list->episode[list->dernier].title,tok);   //The problem is here
    tok = strtok(NULL,",");
    strncpy(list->episode[list->dernier].original_air_date,tok,AIR_DATE_SIZE);
    tok = strtok(NULL,"\n");
    list->episode[list->dernier].us_viewers = atoi(tok);

    list->dernier++;
}

void affiche_list_ep (l_ep list)
{
    for (int i = 0; i < list.dernier; i++)
    {
        printf("%d %d %d %s %s %d\n",list.episode[i].season,list.episode[i].episode_num_in_season,list.episode[i].episode_num_overall,list.episode[i].title,list.episode[i].original_air_date,list.episode[i].us_viewers);
    }
}

void save_list_ep (l_ep list)
{
    FILE *fp = fopen("list_episode_binar","wb");
    //char nb_buffer[11];
    char *str = malloc(80*sizeof(char));
    for (int i = 0; i < list.dernier; i++)
    {
        sprintf(str,"%d,%d,%d,%s,%s,%d\n",list.episode[i].season,list.episode[i].episode_num_in_season,list.episode[i].episode_num_overall,list.episode[i].title,list.episode[i].original_air_date,list.episode[i].us_viewers);

        /**
         * @brief The translation on 8bits of the string str
         * is done by compare each bit of the char
         * The << (~j&7) section is : with the bit representation of 1
         * we shift (rotate) the 1 (0000 0001) by
         *
         */
        for(size_t j=0; j < 8*strlen(str); j++)
        {
            fprintf(fp,"%d",0 != (str[j/8] & 1 << (~j&7)));
        }
        fprintf(fp,"\n");
    }
    free(str);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Aucun argument !\n");
        return EXIT_FAILURE;
    }

    l_ep list_epis;
    init_list_ep(&list_epis);

    affiche_list_ep(list_epis);

    /* Open the file for reading */
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;
    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
    fprintf(stderr, "Error opening file '%s'\n", argv[1]);
    return EXIT_FAILURE;
    }

    /* Get the first line of the file. */
    line_size = getline(&line_buf, &line_buf_size, fp);
    line_size = getline(&line_buf, &line_buf_size, fp);

    Ep *tmp_ep = malloc(sizeof(Ep));

    /* Loop through until we are done with the file. */
    while (line_size >= 0)
    {
        /* Show the line details */
        //printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count, line_size, line_buf_size, line_buf);

        /*tok = strtok(line_buf,",");
        tmp_ep->season = atoi(tok);
        tok = strtok(NULL,",");
        tmp_ep->episode_num_in_season = atoi(tok);
        tok = strtok(NULL,",");
        tmp_ep->episode_num_overall = atoi(tok);
        tok = strtok(NULL,",");
        strcpy(tmp_ep->title,tok);   //The problem is here
        tok = strtok(NULL,",");
        strncpy(tmp_ep->original_air_date,tok,AIR_DATE_SIZE);
        tok = strtok(NULL,"\n");
        tmp_ep->us_viewers = atoi(tok);*/

        //ajout_ep(*tmp_ep,list_epis);

        ajout_episode(line_buf,&list_epis);

        /* Get the next line */
        line_size = getline(&line_buf, &line_buf_size, fp);
    }

    //affiche_list_ep(list_epis);

    save_list_ep(list_epis);

    /* Free the allocated line buffer */
    free(line_buf);
    free(tmp_ep);

    /* Close the file now that we are done with it */
    fclose(fp);

    return EXIT_SUCCESS;
}