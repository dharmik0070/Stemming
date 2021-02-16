#include <stdio.h>


struct list {
	char *string;
	struct list *next;
};

typedef struct list LIST;

int main(void) {
	FILE *fp;
	char line[10];
	LIST *current, *head;
	char word[10];
	printf("\nEnter word:");
	scanf("\n%s", &word);
	head = current = NULL;
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\prefix.txt", "r");

	while (fgets(line,sizeof(line), fp)) {
		LIST *node = malloc(sizeof(LIST));
		node->string = strdup(line);//note : strdup is not standard function
		node->string[strcspn(node->string, "\n")] = 0;
		strcat(node->string,word);
		node->next = NULL;

		if (head == NULL) {
			current = head = node;
		}
		else {
			current = current->next = node;
		}

	}
	fclose(fp);
	//test print

	for (current = head; current; current = current->next)
	{
		printf("%s\n",current->string);
	}
	//need free for each node
	return 0;
}