#include <stdio.h>
#include <stdlib.h>

int main() 
{
	FILE* filepath;
	char filename[100] = "";
	printf("Please enter the Full Path of the file: \n");
	scanf_s("%s", &filename, (unsigned int)sizeof(filename));
	errno_t err = fopen_s(&filepath, filename, "r");
	if (filepath == NULL)
	{
		printf("%s " "File not found.", filename);
		exit(1);
	}
}