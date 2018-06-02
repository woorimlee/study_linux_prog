Chapter 9 : 프로세스 제어 
========================
  
  
## 1. fork() 시스템 호출시 
+ 부모 프로세스 : 자식의 pid 값을 반환받음. 또한 자식에게 1) fork 반환 값, 2) pid, 3) 부모가 설정한 프로세스 잠금 & 파일 잠금 상태, 4) 설정된 시그널과 알람은 상속하지 않음.
+ 자식 프로세스 : 부모의 fd 테이블을 복사함(U-area 복사). 같은 파일의 offset을 공유해서 출력이 중복되지 않게 함.
+ 참고로 pid도 지역 변수라 프로세스의 STACK 섹션에 저장됨.

## 2. wait() 시스템 호출시
+ 부모 프로세스는 자식이 보내는 SIGCHILD 시그널을 기다림. 
  + 자식이 종료됐을 때 커널로 자기의 종료 사실을 보내는데, 그 시그널이 바로 SIGCHILD. 부모 입장에서 그 신호를 받아 무언가를 하려는게 아니면 해당 신호는 무시된다(사용하려면 핸들러 루틴을 이용해야 하고, 이 시그널을 통해 자식이 왜 종료됐는지 부가적인 정보도 받아볼 수 있다).
+ 자식 프로세스가 없으면 즉시 error를 리턴함(ECHILD)
+ wait() 함수의 return 값은 자식 프로세스의 pid 값이다.
+ wait() 함수를 호출할 때 int 형 변수를 인자로 넘겨주면 자식 프로세스로부터 받은 종료 코드 값이 int형 4 바이트 중 3번째 바이트에 저장되므로 우로 8 비트 이동해서 print해 확인할 수 있다.
  + 인자로 넘겨준 int형 변수(보통 status라는 이름)에 chlid에 대한 추가적인 정보가 저장되어 있으니 Macro 함수들을(WIFEXITED, WIFSTOPPED, ...) 이용해 그 상태를 확인해볼 수 있음.
    * WIFEXITED : return true if the process terminated normally (WEXITSTATUS : get exit status)
    * WIFSIGNALED : returns true if a signal caused the process' termination (abnormal) (WTERMSIG : fetch the signal number that caused the termination)
    * WIFSTOPPED : return true if the process was stopped
    * WIFCONTINUED : return true if the process was stopped or continued, respectively, and is currently being traced via the ptrace() system call (WSTOPSIG : fetch the signal number that caused the stop)
+ wait_macro.c 파일의 자식 프로세스가 terminated 되는 방법에 따라 (exit or abort) 다른 값이 printf됨.
