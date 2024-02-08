## Xv6_multiThreading
The main objective of our project is to implement kernel threads in xv6. Firstly, this is 
done by the implementation of clone and join system calls. Secondly, we wrap 
thread_create , join, lock_release and lock_acquire functions around these system calls to 
utilize them. Finally, we make some changes to the scheduler function so that fair share
is considered for all threads and processes.  

## Implementation of **clone** and **join**
these two system calls are located in proc.c . The base of clone is fork function. The 
difference is the memory of the thread. one page of the parent process heap is allocated 
to its child thread.  

## Steps of adding system_calls: **Considering files**
systemfile.h,defs.h,user.h,sysproc.c,usys.s,syscall.c,proc.c,ps.ca  

## Impelemtation of **lock**:
We designed our own struct for lock which is simpler and doesn’t have debugging field. And 
for the sake of atomicity, we implemented our lock functions using xchg. If the lock is held, 
flag will already be 1, so the xchg returns 1 and the loop continues. If ththe flaghg returns 0, however, acquire has successfully acquired the lock—locked was 0 and is now 1—so the 
loop can stop. These are done in ulib.c.  

## Implementation of **fair share**:
In our implementation each thread is implemented using process struct. So we have to 
share quantum times fairly between all process and threads. As a result of making threads 
using process struct, each thread is already in ready queue but we should ignore when we 
reach them . we handle threads using a turn integer in their parent struct . This uint points 
to the thread which its turn to run has come up. These changes are made in scheduler 
function in proc.c.  



