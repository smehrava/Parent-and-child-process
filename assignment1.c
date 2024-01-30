#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    //printf("hello from main");
    printf("%d",argc);
    
    for (int i =0; i < argc; i++){
        printf("argv[%d] = %s\n", i , argv[i]);
    
    }printf("/n");

    pid_t pid1,pid2, pid1_1, pid1_2,parent;

    
    parent = getpid();
    printf("parent (PID %d): process started\n", parent);
    printf("parent (PID %d): forking child_1\n", parent);

    //creating first child of the parent e.g. child_1
    pid1 = fork();

    
    
    
    if (pid1 == 0){     //child_1
        printf("parent (PID %d): fork successful for child_1 (PID %d)\n",parent,getpid());
        printf("parent (PID %d): waiting for child_1 (PID %d) to complete\n",parent,getpid());
        printf("child_1 (PID %d): process started from parent (PID %d)\n",getpid(),parent);
        printf("child_1 (PID %d): forking child_1.1\n", getpid());
        

        //creating first child of child_1 (first grand child of parent) e.g. child1_1
        pid1_1 = fork();  

        if(pid1_1 == 0 ){
            printf("child_1.1 (PID %d): process started from child_1 (PID %d)\n",getpid(),getppid());
            printf("child_1.1 (PID %d):calling an external program [./external_program1.out]\n",getpid());
            execl("external_program1.out",argv[1],NULL);
        }else{
            wait(NULL);  // waiting for child1_1 to complete
            printf("child_1 (PID %d): completed child_1.1\n", getpid());

            printf("child_1 (PID %d): forking child_1.2\n", getpid());
            pid1_2 = fork();
         

            //child1_2 or child1's second child has been created at this point.
            if(pid1_2 == 0){
                printf("child_1.2 (PID %d): process started from child_1 (PID %d)\n",getpid(), getppid());
                printf("child_1.2 (PID %d): calling an external program [./external_program1.out]\n",getpid());
                execl("external_program1.out",argv[2],NULL);
            }else{
                wait(NULL); //waiting for child1_2 to complete.
                printf("child_1 (PID %d): completed child_1.2\n",getppid());
            }
        }


    }else if (pid1> 0){  //parent
        wait(NULL);   //waiting for child_1 to terminate.
        printf("parent (PID %d): forking child_2\n",parent);
        pid2 = fork();

        if(pid2 == 0){
            //child_2 has been made.
            printf("parent (PID %d): fork successful for child_2 (PID %d)\n", parent, getpid());
            printf("child_2 (PID %d): process started from parent (PID %d)\n", getpid(), parent);
            printf("child_2 (PID %d): calling an external program [./external_program2.out]\n",getpid());

            execl("./external_program2.out",argv[3],NULL);
        
        }else{
            wait(NULL); //waiting for child_2 to complete.
            
            printf("parent (PID %d): completed parent\n",parent);
        }
    }

    return 0;


}