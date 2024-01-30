// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"



// void worker_function(void* arg1, void* arg2) {
//   lock_acquire(lock_thread);
//   //int num1 = *(int*)arg1;
//   //int num2 = *(int*)arg2;
//   //int num3 = num1+num2 ; 
//   sleep(10) ; 
//   //printf(1 , "%d\n" , num3) ; 
//   //printf(1, "this should print %d\n ", num1 + num2);
//   //sleep(10);
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
//     sleep(20) ; 
//     //printf(1 , "in child process \n" ) ;
//     exit() ; 
//   }
//   else if (pid < 0 )
//   {
//     //error
//     printf(1, "######## error in fork ########\n");
//     exit() ; 
//   }
//   else // parent 
//   {
//    // int t1 , t2 , t3 ; 
//     lock_init(lock_thread) ; 
//     // printf(1, "test executing threads without lock :\n");
//     int arg1 = 9, arg2 = 1 ; 
//     thread_create(&worker_function, (void *)&arg1, (void *)&arg2);
//     int arg3 = 4 , arg4 = 2;
//     thread_create(&worker_function, (void *)&arg3, (void *)&arg4);
//     int arg5 = 7 ,  arg6 = 4;
//     thread_create(&worker_function ,(void *)&arg5, (void *)&arg6);
//     thread_join();
//     thread_join();
//     thread_join();
//     //printf(1 , "t1 : %d , t2 : %d , t3 : %d \n" , t1 , t2 , t3 );
//   }
//   wait() ; 
//   exit(); 
// }


#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

lock_t* lock_thread;

void worker_function(void* arg1, void* arg2) {
  lock_acquire(lock_thread);
  sleep(10);
  lock_release(lock_thread); 
  exit();
}

int main()
{
    int f1 = fork();
    if (f1 == 0)
    {
        sleep(10);
        exit();
    }
    int f2=fork();
    if(f2==0){
      lock_init(lock_thread) ; 
      int arg1 = 9, arg2 = 1 ; 
      thread_create(&worker_function, (void *)&arg1, (void *)&arg2);
      int arg3 = 4 , arg4 = 2;
      thread_create(&worker_function, (void *)&arg3, (void *)&arg4);
      int arg5 = 7 ,  arg6 = 4;
      thread_create(&worker_function ,(void *)&arg5, (void *)&arg6);
      thread_join();
      thread_join();
      thread_join();
    }
    wait();
    wait();
    exit() ; 
}
