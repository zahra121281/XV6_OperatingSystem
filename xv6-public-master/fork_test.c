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
        //sleep(10);
        exit();
    }
    int f2=fork();
    if(f2==0){
      lock_init(lock_thread) ; 
      int arg5 = 7 ,  arg6 = 4;
      for(int i=0 ; i< 5 ; i++ )
        thread_create(&worker_function, (void *)&arg5, (void *)&arg6);
      for(int i=0 ; i< 5 ; i++ )
        thread_join();
      exit() ; 
    }
    wait();
    wait();
    exit() ; 
}
