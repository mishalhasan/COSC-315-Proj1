# COSC-335-Proj1

## Contributors

* **Spencer Ke** - 

   - Devloped logic of the project 
  
   - Progamming & Debugging 
 
* **Mishal Hasan** - 20647160

    - Developed logic of the project 
  
    - Research 
  
    - Debugging 
    
*As we are only two people in our group, we took more of a pair programming approach. We worked on it together as a whole.*

## Code Design 

After the main shell input loop runs to read the different input from the user, it will check if parallel is set to p. If it is the run_parallel function will execute otherwise the run_sequential will be executed. 
  
  * int run_parallel(char** cmdTokens, int count)
     - An array called cid stores at each index the pid of a child process. 
     - The number of proccesses is the number of times a command needs to execute ie. count. 
     - A switch is used to check for whether it is the parent, child or if the fork failed. 
     - If a its a child, (cid == 0) the pid will print out onto the console and the cmdTokens will be executed. 
     - If it is anything else, it will wait till all the children finish executing before exiting the process itself. 
     - A new child proccess is initiated through the fork command which is run in a for loop. 
     - Since the parent and child proccesses are executed at the same time, the parent process will increment the for loop causing the fork command to be called again until the for loop exits ie. when all child proccesses are created. This way all child processes are created at the same time and will run concurrently.  
     - The parent proccess will exit after all child proccesses are complete.

  * int run_sequential(char** cmdTokens, int count)
     - inside a for loop, fork the process
     - if the process is a child, print the pid, run the cmdTokens and exit
     - if the process is a parent, wait until the child dies, then continue
     - repeat the number of times the command should execute, ie. count.
     - once all process have been run, there are no child processes left and the parent process exits.
}
## Online Resources 

https://www.geeksforgeeks.org/creating-multiple-process-using-fork/
https://stackoverflow.com/questions/12711799/creating-child-processes-in-parallel

