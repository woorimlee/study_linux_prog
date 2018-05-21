1.  forktest : The way to use fork() & getpid() syscall.
    Usage : # ./forktest

2.  shm_sender & shm_receiver : The way to use shmget() & shmat() syscall.
				sender makes random numbers to shared memory.
				receiver identifies that numbers in the shared memory.
    Usage :
    First shell : # ./shm_sender
    Second shell : # ./shm_receiver

3.  fork_and_shm : The way to forked processes use shared memory with parent process.
    Usage : # ./fork_and_shm
