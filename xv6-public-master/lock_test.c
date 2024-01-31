#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

lock_t* lock_thread;

void Test_func(void* arg1, void* arg2) {
  lock_acquire(lock_thread);
  sleep(10);
  lock_release(lock_thread); 
  exit();
}

int
main(int argc, char *argv[])
{
  lock_init(lock_thread) ; 
  int arg5 = 7 ,  arg6 = 4;
  for(int i=0 ; i< 5 ; i++ )
    thread_create(&Test_func , (void *)&arg5, (void *)&arg6);
  for(int i=0 ; i< 5 ; i++ )
    thread_join();
  exit() ; 
}


