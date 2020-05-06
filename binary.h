
struct tree{
	char *key;
	void *data;
	struct tree *children[2];
};

struct array{
	int nitems;
	void *arrptr;
	struct tree *index1;
	struct tree *index2;
};
void add_node(struct tree **root, char *string, void *element);
struct tree *find(struct tree *root, char *target);
