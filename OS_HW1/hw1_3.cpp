#include<iostream>
#include<unistd.h>
#include<vector>
#include<string>
#include<cstring>
#include<fcntl.h>
#include<sys/wait.h>
#include <string.h>

#define MAX_LINE 80

using namespace std;

int main(void)
{
	int should_run = 1; 
	vector<string> arg;
	string tmp;
	vector<char*> argv_t;
	char **argv;
	char buf[80];
	int n;
	int argc;
	int mode;
	int status;
	pid_t pid;
	bool has_and;
	while(should_run){
		cout<<"osh>";
		fflush(stdout);
		n = read(STDIN_FILENO, buf, 80);
		for(int i=0;i<n;i++){
			if(buf[i]==' '||i==n-1){ 
				if(tmp.size()>0) 
					arg.push_back(tmp);
				tmp = "";
			}
			else{
				tmp = tmp + buf[i];
			}
		}
		argc = arg.size();
		argv = new char*[argc+1]; 
		for(int i=0;i<argc;i++){
			argv[i]=new char[arg[i].size()];
			strcpy(argv[i], arg[i].c_str());
		}
		argv[argc] = new char;
		argv[argc] = NULL;
        /**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will not invoke wait()
		*/
		pid = fork();
		if (pid == 0) {
			execvp(argv[0], argv);
			char exit_str[] = "exit";
			if (strcmp(argv[0], exit_str) == 0) {
				exit(5);
			}
			else {
				exit(0);
			}
		}
		else if (pid > 0) {
			char amp[] = "&";
			if (strcmp(amp, argv[argc - 1]) != 0) {
				wait(&status);
				if (WIFEXITED(status) != 0 && WEXITSTATUS(status) == 5) {
					break;
				}
			}
		}
		else {
			cout << "Error!\n";
		}

		arg.clear();
		argv_t.clear();
		for(int i=0;i<argc;i++){
			delete [] argv[i];
		}		
		delete argv;
	}
	return 0;
}
