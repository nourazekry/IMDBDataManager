struct title_basics {
    char *tconst;
    char *primaryTitle;
};
struct array *get_title(char *directory);
void build_ptindex(struct array *ptr);
struct title_basics *find_primary_title(struct array *ptr, char *key);
void build_tindex(struct array *ptr);
struct title_basics *find_tconst(struct array *ptr, char *key);
