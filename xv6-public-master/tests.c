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
  printf(1, "this should print %d\n ", num1 + num2);
  exit();
}

void f1(void* arg1, void* arg2) {
  int num1 = *(int*)arg1;
  int num2 = *(int*)arg2;
  printf( 1 , "num1: %d , num2 : %d this should print %d\n",num1 , num2 , num1+num2);
  sleep(20);
  exit();
}

// void f2(void* arg1, void* arg2) {
//   int num = *(int*)arg1;
//   //if (num) lock_acquire(lk);
//   printf(1, "2. this should print %s\n", num ? "second\n" : "whenever\n");
//   printf(1, "2. sleep for %d ticks\n", SLEEP_TIME);
//   sleep(SLEEP_TIME);
//   //if (num) lock_release(lk);
//   exit();
// }

// void f3(void* arg1, void* arg2) {
//   int num = *(int*)arg1;
//   //if (num) lock_acquire(lk);
//   printf(1, "3. this should print %s\n", num ? "third\n" : "whenever\n");
//   printf(1, "3. sleep for %d ticks\n", SLEEP_TIME);
//   sleep(SLEEP_TIME);
//   //if (num) lock_release(lk);
//   exit();
// }

int
main(int argc, char *argv[])
{
  lock_init(lock_thread);
  int arg1 = 9, arg2 = 1;
  printf(1, "test executing threads without lock :\n");
  thread_create(&add, (void *)&arg1, (void *)&arg2);
  int arg3 = 4 , arg4 = 2;
  thread_create(&add, (void *)&arg3, (void *)&arg4);
  int arg5 = 7 ,  arg6 = 4;
  thread_create(&add, (void *)&arg5, (void *)&arg6);
  printf(1 , "before first join") ; 
  thread_join();
  printf(1 , "after first join") ; 
  thread_join();
  thread_join();
  exit();
}