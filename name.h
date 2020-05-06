

struct name_basics{
    char *nconst;
    char *primaryName;
};

struct array *get_name(char *directory);
char *duplicate(char *string);
struct name_basics *find_name(struct array *ptr, char *key);
void build_pnindex(struct array *ptr);
struct name_basics *find_nconst(struct array *ptr, char *key);
void build_nindex(struct array *ptr);
