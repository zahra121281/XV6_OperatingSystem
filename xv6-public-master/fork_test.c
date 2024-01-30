#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

lock_t* lock_thread;

void add(void* arg1, void* arg2) {
  lock_acquire(lock_thread);
  int num1 = *(int*)arg1;
  int num2 = *(int*)arg2;
  printf(1, "this should print %d\n ", num1 + num2);
  sleep(50);
  lock_release(lock_thread); 
  exit();
}

int
main(int argc, char *argv[])
{
  int pid =0 ; 
  pid = fork() ; 
  if( pid > 0 )
  {
    printf(1 , "id of fork child : %d\n" , pid ) ; 
    for( int i=0 ; i < 10 ; i++ )
    {
        printf(1 , "in child process i : %d\n" , i ) ; 
    }
    exit() ; 
  }
  else if (pid < 0 )
  {
    //error
    printf(1, "######## error in fork ########\n");
  }
  else // parent 
  {
    int t1 , t2 , t3 ; 
    lock_init(lock_thread) ; 
    printf(1, "test executing threads without lock :\n");
    int arg1 = 9, arg2 = 1 ; 
    t1 = thread_create(&add, (void *)&arg1, (void *)&arg2);
    int arg3 = 4 , arg4 = 2;
    t2 = thread_create(&add, (void *)&arg3, (void *)&arg4);
    int arg5 = 7 ,  arg6 = 4;
    t3 = thread_create(&add, (void *)&arg5, (void *)&arg6);
    thread_join();
    thread_join();
    thread_join();
    printf(1 , "t1 : %d , t2 : %d , t3 : %d \n" , t1 , t2 , t3 );
    wait() ; 
    printf(1, "after wait\n") ; 
    exit();
  }
}