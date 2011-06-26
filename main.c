#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*split(char *string,char*delimiters)                       */
/*Returns an array of non-empty strings terminated with NULL*/
/*Free result with free_split                               */
char **split(char *string,char *delimiters){
	char *buffer = malloc(strlen(string));
	strcpy(buffer,string);
	char **result = (char **)malloc(sizeof(char **));
	int length = 0;
	char *pch = strtok(buffer,delimiters);
	while(pch != NULL)
	{
		length +=1;
		result = (char **)realloc(result,
				          (length+1)*sizeof(char **));
		result[length-1] = malloc(sizeof(char)*strlen(pch));
		strcpy(result[length-1],pch);
		pch = strtok(NULL,delimiters);
	}
	result[length] = NULL;//Null terminate array, also empty string
	free(buffer);
	return result;
}
/*free_split(char **split_result) */
/*Frees the result of a free_split*/
void free_split(char **split_result)
{
	int i=0;
	while(split_result[i] != NULL)
	{
		free(split_result[i]);
		i++;
	}
	free(split_result);
}

void readcommand(char **command,char ***args)
{
	char *buffer = malloc(sizeof(char)*10);
	int cursize = 10;
	int i =0;

	/*This is where autocomplete would go*/
	buffer[i]=getchar();
	while(buffer[i] != '\n')
	{
		i++;
		if(i % 10 == 0){
			printf("resizing\n");
			buffer = realloc(buffer,(cursize+10)*sizeof(char));
			cursize +=10;
		}
		buffer[i] = getchar();
	}

	/*split*/
	char **linesplit = split(buffer," \n");
	free(buffer);

	/*return results*/
	*command = linesplit[0];
	*args = linesplit;

}

int main()
{
	while(1){
		char **args = {NULL};
		char *command = NULL;
		int pid;
		
		printf("$");
		readcommand(&command,&args);
		int i=0;
		while(args[i]!=0){
			i++;
		}
		if((pid = fork()) == 0){
			printf("Executing: %s\n",command);
			return execv(command,args);
		}else if(pid > 0){
			wait(0);
			printf("%d: terminated\n",pid);
		}else {
			printf("error, failed to fork");
			exit(-1);
		}
		//clean up
		free_split(args);
	}
}
