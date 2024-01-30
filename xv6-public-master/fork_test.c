#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"
#define SLEEP_TIME 100
void ThreadFunc1(void *args1,void *args2)
{
    //printf(1,"in process %d thread %d\n",*(int*)args1,*(int*)args2);
    sleep(SLEEP_TIME);
    //printf(1,"process %d thread %d complete\n",*(int*)args1,*(int*)args2);
    exit();
}
int main()
{
    int f1 = fork();
    if (f1 == 0)
    {
        for(int i=0;i<4;i++){
            //printf(1,"in process 1\n");
            sleep(SLEEP_TIME);
            //printf(1,"%d complete\n",i);
        }
        exit();
    }
    int f2=fork();
    if(f2==0){
         int arg1 = 2, arg2 = 1;

        thread_create(&ThreadFunc1, (void *)&arg1, (void *)&arg2);
        int arg3 = 2;
        thread_create(&ThreadFunc1, (void *)&arg1, (void *)&arg3);
        int arg4 = 3;
        thread_create(&ThreadFunc1, (void *)&arg1, (void *)&arg4);
        int arg5 = 4;
        thread_create(&ThreadFunc1, (void *)&arg1, (void *)&arg5);
        thread_join();
        thread_join();
        thread_join();
        thread_join();
    }
    wait();
    wait();
    // printf("%d\n", x);
    return 0;
}

// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"

// lock_t* lock_thread;

// void add(void* arg1, void* arg2) {
//   lock_acquire(lock_thread);
//   int num1 = *(int*)arg1;
//   int num2 = *(int*)arg2;
//   int num3 = num1+num2 ; 
//   printf(1 , "%d\n" , num3) ; 
//   //printf(1, "this should print %d\n ", num1 + num2);
//   sleep(10);
//   lock_release(lock_thread); 
//   exit();
// }

// int
// main(int argc, char *argv[])
// {
//   int pid =0 ; 
//   pid = fork() ; 
//   if( pid > 0 )
//   {
    
//     //printf(1 , "in child process \n" ) ;
//     exit() ; 
//   }
//   else if (pid < 0 )
//   {
//     //error
//     printf(1, "######## error in fork ########\n");
//   }
//   else // parent 
//   {
//    // int t1 , t2 , t3 ; 
//     lock_init(lock_thread) ; 
//     // printf(1, "test executing threads without lock :\n");
//     int arg1 = 9, arg2 = 1 ; 
//     thread_create(&add, (void *)&arg1, (void *)&arg2);
//     int arg3 = 4 , arg4 = 2;
//     thread_create(&add, (void *)&arg3, (void *)&arg4);
//     int arg5 = 7 ,  arg6 = 4;
//     thread_create(&add, (void *)&arg5, (void *)&arg6);
//     thread_join();
//     thread_join();
//     thread_join();
//     //printf(1 , "t1 : %d , t2 : %d , t3 : %d \n" , t1 , t2 , t3 );
//     wait() ; 
//     //printf(1, "after wait\n") ; 
//     exit();
//   }
// }