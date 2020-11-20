#include <stdio.h>
#define MAX_PATH_LEN 100

int main() {
    int i;
    FILE *f;
    for(i=2;i<10;i++)
    {
	char file_path[MAX_PATH_LEN];
	sprintf (file_path, "cards/%d.txt", i);
	f = fopen(file_path, "w");
	fprintf(f, "*********\n");
	fprintf(f, "*       *\n");
	fprintf(f, "*       *\n");
	fprintf(f, "*   %d   *\n", i);
	fprintf(f, "*       *\n");
	fprintf(f, "*       *\n");
	fprintf(f, "*********\n");
	fclose (f);
    }

    f = fopen("cards/10.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*  10   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/ace.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   A   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/jack.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   J   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/queen.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   Q   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose (f);

    f = fopen("cards/king.txt", "w");
    fprintf(f, "*********\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*   K   *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*       *\n");
    fprintf(f, "*********\n");
    fclose(f);

    return 0;
}
