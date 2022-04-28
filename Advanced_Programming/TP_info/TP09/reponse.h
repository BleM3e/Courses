#define TITLE_SIZE 50
#define AIR_DATE_SIZE 11
#define LIST_SIZE 300

typedef struct episode {
    int season;
    int episode_num_in_season;
    int episode_num_overall;
    char title[TITLE_SIZE];
    char original_air_date[AIR_DATE_SIZE];
    int us_viewers;
} Ep;

typedef struct list_episode {
    Ep episode[LIST_SIZE];
    int dernier;
} l_ep, list_ep;