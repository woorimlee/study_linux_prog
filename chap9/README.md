Chapter 9 : 프로세스 제어 
========================
  
  
## 1. fork() 시스템 호출시 
+ 부모 프로세스 : 자식의 pid 값을 반환받음. 또한 자식에게 1) fork 반환 값, 2) pid, 3) 부모가 설정한 프로세스 잠금 & 파일 잠금 상태, 4) 설정된 시그널과 알람은 상속하지 않음.
+ 자식 프로세스 : 부모의 fd 테이블을 복사함(+ U-area 복사). 같은 파일의 offset을 공유해서 출력이 중복되지 않게 함.
+ 참고로 pid도 지역 변수라 프로세스의 STACK 섹션에 저장됨.

## 2. wait() 시스템 호출시
+ 부모 프로세스는 자식이 보내는 SIGCHILD 시그널을 기다림. 
  + 자식이 종료됐을 때 커널로 자기의 종료 사실을 보내는데, 그 시그널이 바로 SIGCHILD. 부모 입장에서 그 신호를 받아 무언가를 하려는게 아니면 해당 신호는 무시된다(사용하려면 핸들러 루틴을 이용해야 하고, 이 시그널을 통해 자식이 왜 종료됐는지 부가적인 정보도 받아볼 수 있다).
+ 자식 프로세스가 없으면 즉시 error를 리턴함(ECHILD)
+ wait() 함수의 return 값은 자식 프로세스의 pid 값이다.
+ wait() 함수를 호출할 때 int 형 변수를 인자로 넘겨주면 자식 프로세스로부터 받은 종료 코드 값이 int형 4 바이트 중 3번째 바이트에 저장되므로 우로 8 비트 이동해서 print해 확인할 수 있다.
  + 인자로 넘겨준 int형 변수(보통 status라는 이름)에 chlid에 대한 추가적인 정보가 저장되어 있으니 Macro 함수들을(WIFEXITED, WIFSTOPPED, ...) 이용해 그 상태를 확인해볼 수 있음.
    + WIFEXITED : return true if the process terminated normally (WEXITSTATUS : get exit status)
    + WIFSIGNALED : returns true if a signal caused the process' termination (abnormal) (WTERMSIG : fetch the signal number that caused the termination)
    + WIFSTOPPED : return true if the process was stopped
    + WIFCONTINUED : return true if the process was stopped or continued, respectively, and is currently being traced via the ptrace() system call (WSTOPSIG : fetch the signal number that caused the stop)
* wait_macro.c 파일의 자식 프로세스가 terminated 되는 방법에 따라 (exit or abort) 다른 값이 printf됨.

## 3. waitpid() 시스템 콜에 대해서
+ Additional parameters allow for fine-tuning -> more powrful version of wait().
+ 자식 프로세스의 pid만 안다면 원하는 프로세스 만의 종료를 기다리게 만들 수 있음.
+ pid_t waitpid(pid_t pid, int *status, int options)의 원형에서 pid 값은 다음의 네가지 경우에 따라 상황이 분리된다.
  + 1) pid < -1 : 프로세스 그룹 아이디가 pid의 절대값과 같은 자식 프로세스를 기다린다.
  + 2) pid == -1 : child process 아무나 기다린다. wait() 함수와 동일.
  + 3) pid == 0 : 부모 프로세스의 ID와 프로세스 그룹 ID와 같은 자식 프로세스의 종료를 기다린다.
  + 4) pid > 0 : 넘어온 pid 값의 프로세스 종료를 기다린다.
+ options에 다음의 값이 들어가면 
  + 1) WNOHANG : waitpid 호출해도 블록하지 않는다. 즉, 어떤 자식이 종료되지 않아도 리턴하라는 것이다.
  + 2) WUNTRACED : 자식 프로세스가 STOP하면 반환.
  + 3) WCONTINUED : STOP되었던 자식 프로세스가 재실행되면 반한.

## 4. Zombie 프로세스 ? 
+ 자식 프로세스가 종료됐는데 부모 프로세스가 wait를 호출하지 않았었다면, 그 자식 프로세스를 좀비 프로세스라고 부름(프로세스 테이블에 존재하는 상태)
+ 분명 자식 프로세스가 종료를 하겠다고 exit()호출을 했는데도 system resources를 계속 소비하는 상태임.
+ 정확히는 자식 프로세스가 보낸 SIGCHILD를 SIG_IGN해두지 않거나(무시하겠다는 설정) 적절한 처리를 하지 않았다면, 이런 일이 발생하는 것으로, 가장 기본적으로는 wait()호출을 해야 SIGCHILD를 처리할 수 있음.
+ 좀비 프로세스가 있는 상태에서 만약 부모 프로세스가 종료되면 좀비 프로세스의 부모 프로세스가 init 프로세스(1번 프로세스)로 바뀌는데, init 프로세스가 SIG_IGN으로 SIGCHILD에 대해 처리해주기 때문에 좀비 프로세스는 사라진다.

## 5. vfork() ??
+ fork() 시스템 콜은 보통 fork & exec 형식으로 같이 사용 됨.
+ 따라서 fork()를 통해 부모 프로세스의 필요없는 코드나 데이터등을 복사하는건 불필요한 오버헤드임.
+ 이런 경우에 사용하는게 vfork().

## 6. Copy-On-Write(COW)와 개선된 fork()
+ COW : fork시 fork 윗단의 코드나 쓸데없는 데이터 등을 복사하는 등의 lazy optimization strategy를 개선시키기 위해서 copy할 내용을 modify하기 전까지는 해당 내용을 공유만하고 있다가 modify 시도가 있을 시 copy를 하는 optimization 기술이다.
+ 현재의 리눅스에서는 fork가 COW기법을 사용하기 때문에 자식 프로세스 생성시 모든 자원을 복사하지 않고 attempts to modify 경우에만 복사하도록 구현되어 있다.

## 7. exec() 시스템 콜에 대해서
+ 프로세스가 exec()콜을 하면 exec 인자로 넘긴 프로그램으로 대치된다.
+ 프로세스를 새로 생성하는게 아니기 때문에 프로세스 번호는 바뀌지 않는다.
+ 또한, 기존의 프로그램이 없어지기 때문에 return 할 위치가 없어지기 때문에 exec() syscall이 성공한 경우에는 반환하지 않으며 실패시에만 -1을 return한다.

