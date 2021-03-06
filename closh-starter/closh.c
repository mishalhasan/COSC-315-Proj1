 // closh.c - COSC 315, Winter 2020
// YOUR NAME HERE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

int run_parallel(char** cmdTokens, int count){

    int cid[count];
    for(int i = 0; i < count; i++){
        cid[i] = fork();
        switch(cid[i]){
            case 0:
                //child
                printf("PID: %i\n", getpid());
                exec(cmdTokens);
                exit(0);
            case -1:
                //fork failed
                exit(1);
        }
    }

}

int run_sequential(char** cmdTokens, int count){
    //run exec count number of times
    for(int i = 0; i < count; i++){
        int cid = fork();
        if(cid == 0){//child - run program, then exit
            printf("PID: %i\n", getpid());
            exec(cmdTokens);
            exit(0);
        }else{
            waitpid(cid,0,0);
        }
    }
    return(0);
}
int exec(char** cmdTokens){
    execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
    // doesn't return unless the calling failed
    printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
    exit(1); 
}


// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    
    while (TRUE) { // main shell input loop
        
        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);
        
        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code
        
        
        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////


        if(parallel == TRUE){
            run_parallel(cmdTokens, count);
        }
        else{
            run_sequential(cmdTokens, count);
        }

    }
}

