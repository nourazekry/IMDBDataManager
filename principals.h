struct title_principals{
    char *tconst;
    char *nconst;
    char *characters;
};
struct array *get_principals(char *directory);
void build_tindex_tp(struct array *ptr);
struct tree *find_tconst_tp(struct array *ptr, char *key);
void build_nindex_tp(struct array *ptr);
struct tree *find_nconst_tp(struct array *ptr, char *key);
