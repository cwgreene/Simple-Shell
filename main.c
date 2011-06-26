#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strtok.h>
#include <stdio.h>

char **split(char *string,char *delimeters){
	char **result = (char **)malloc(sizeof(char **));
	int length = 0;
	char *pch = strtok(string,delimeters)
	while(pch != NULL)
	{
		length +=1;
		result = (char **)realloc(result,sizeof(char **));
		result[length-1] = malloc(sizeof(char)*strlen(pch));
		strcpy(result+length-1 ,pch);
	}
	result[length] = NULL;//Null terminate array, also empty string
	return result;
}

void readcommand(char **command,char ***args)
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
	}else
		buffer[i] = '\0';
	}
	
	buffer = malloc(sizeof(char)*10);

}

int main()
{
	while(1){
		char **args = {NULL};
		char *command = NULL;
		int pid;
		
		printf("$");
		readcommand(&command,&args);

		if((pid = fork()) == 0){
			printf("Executing: %s\n",command);
			return execl(command,"",NULL);
		}else if(pid > 0){
			wait(0);
			printf("%d: terminated\n",pid);
		}else {
			printf("error, failed to fork");
			exit(0);
		}
		//clean up
		free(command);
	}
}

