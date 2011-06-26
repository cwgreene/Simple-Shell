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

void readcommand_old(char **command,char ***args)
{
	char *buffer = malloc(sizeof(char)*10);
	int i = 0;
	int cursize = 10;
	buffer[0] = getchar();
	while(buffer[i] != ' ' && buffer[i] != '\n')
	{
		i++;
		if(i % 10 == 0){
			printf("resizing\n");
			buffer = realloc(buffer,(cursize+10)*sizeof(char));
			cursize +=10;
		}
		buffer[i] = getchar();
	}
	*command = buffer;
	if(buffer[i] == '\n')
	{
		buffer[i] = '\0';
		return;
	}else{
		buffer[i] = '\0';
	}
	//buffer = malloc(sizeof(char)*10);
}

void readcommand(char **command,char ***args)
{
	char *buffer = malloc(sizeof(char)*10);
	int cursize = 10;
	int i =0;
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
	char **linesplit = split(buffer," \n");
	*command = linesplit[0];
	*args = linesplit+1;
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
			printf("%s",args[i]);
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
			exit(0);
		}
		//clean up
		free_split(args-1);
	}
}
