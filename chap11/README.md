# 시그널

### 0. 첨부한 c 코드 
+ alarm.c는 '1. 시그널'의 SIGALRM을 사용하는 예시다.
+ alarm_handler.c는 '2. 시그널처리'의 SIGALRM을 사용하는 예시다.
+ pause.c는 '2. 시그널처리'의 pause() 함수 사용 예시다.
+ sigaction.c는 '2. 시그널처리'의 sigaction() 함수 사용 예시다.
+ time_limit.c는 '4. 시그널 보내기'의 kill() 함수 사용 예시다. 
    + ex) $ ./time_limit 제한시간(초) command명령어 명령어옵션
+ kill.c는 '4. 시그널 보내기'의 kill() 함수를 사용한 예시다.
+ jump.c는 '5. 시그널과 비지역 점프'의 setjmp() 함수와 longjmp() 함수의 사용 예시다.

### 1. 시그널
+ 예기치 않은 사건이 발생할 때 이를 알리는 소프트웨어 인터럽트.
+ /usr/include/signal.h에 정의되어 있다.
  + SIGINT : 터미널에서 Ctrl + C가 입력됐을 때 발생하는 인터럽트 시그널. (기본 처리는 종료)
  + SIGSTP : 터미널에서 Ctrl + Z가 입력됐을 때. (중지)
  + SIGQUIT : 터미널에서 Ctrl + \가 입력됐을 때 모든 fg process에 시그널을 보냄. (종료)
  + SIGKILL : 잡을 수 없는 프로세스 종료 시그널(User defined signal handler 사용 불가). (종료)
  + SIGSTOP : kill()에 의해 호출되는 잡을 수 없는 프로세스 중지 시그널. (중지)
  + SIGCONT : kill()에 의해 호출되는 중지된 프로세스를 다시 실행시키는 시그널. (무시)
  + SIGTERM : kill()에 의해 호출되는 잡을 수 있는 프로세스 종료 시그널. (종료)
  + SIGABRT : abort()에 의해 발생되는 종료 시그널. (종료(코어 덤프 생성))
  + SIGALRM : alarm()이 울릴 때 발생하는 알람 시그널. (종료)
  + SIGCHLD : 프로세스의 종료 혹은 중지를 부모에게 알리는 시그널. (무시)
  + SIGFPE : 0으로 나누기, floating-point error, over/underflows 와 같은 산술 오류. (종료(코어 덤프 생성))
  + SIGIO : 비동기 IO 이벤트 알림. (종료)
  + SIGPIPE : 파이프가 끊어졌거나, 파이프에 쓰려는데 리더가 없을 때. (종료)
  + SIGSEGV : 유효하지 않은 메모리 참조(Segmentation violation(unmapped memory access)). (종료)
  + SIGUSR1 ~ 2 : 사용자 정의 시그널. (종료)
  + SIGTRAP : 프로세스가 실행하다 브레이크 포인트 도달하거나 넘으면 발생. 디버거가 캐치함. (무시)
  + SIGHUP : 터미널 연결이 끊겼을 때 발생(보통 사용자 로그아웃). 세션의 리더한테 이 신호를 보낸다. (종료) 
  + SIGILL : 프로세스가 illegal macine instruction을 수행하려 할 시 보내는 시그널. (종료(코어 덤프 생성))
  + SIGXFSZ : 프로세스가 file size limit를 초과하려 한다면 보내는 시그널. (종료)
  
  
위의 시그널들을 종료별로 분류해보자면
  + 터미널에서 생성된 시그널 : SIGINT, SIGSTP
  + 하드웨어 예외가 생성하는 시그널 : SIGFPE, SIGSEGV
  + kill() 시스템 호출 : SIGSTOP, SIGCONT, SIGTERM
  + 소프트웨어 조건 : SIGALRM, SIGPIPE, SIGCHLD
+ 시그널 처리 기본 동작
  + 프로세스를 종료시킨다(terminate)
  + 시그널을 무시한다(ignore) 
  + 프로세스를 중지시킨다(suspend)
  + 프로세스를 계속돌린다(resume)

### 2. 시그널 처리
+ 시그널에 대한 처리 함수를 지정해주는 signal() syscall.
  + sighandler_t signal(int signum, sighandler_t handler);
  + signum에 대한 처리 함수를 handler로 지정한다. 반환 값은 기존의 처리 함수다.
  + handler의 매개변수로 사용자 정의 함수, SIG_IGN, SIG_DFL을 넘겨줄 수 있다.
    + SIG_IGN : 해당 시그널을 무시한다. SIGKILL, SIGSTOP을 제외하고 사용가능하다.
    + SIG_DFL : 해당 시그널을 디폴트 처리 함수를 사용하겠다는 말이다.
  + 이 함수는 void 타입을 return한다. no standard place in the program for this function to return 이기 때문이다.
+ 시그널을 받을 때까지 프로세스를 중지시키는 pause() syscall. 프로세스는 인터럽트를 받을 수 있는 wait 상태로 전환된다.
  + 시그널을 받으면 -1을 리턴하고 errno는 EINTR로 설정되며 중지가 풀린다.
  + 만약 무시되는 시그널을 받으면 프로세스는 wake up 하지 못한다.
+ signal() 함수보다 정교하게 시그널 처리기를 등록하기 위해선 sigaction() 함수를 사용한다.
  + sigaction 구조체를 사용하여 좀 더 정교한 시그널 처리 액션을 등록할 수 있다.
  + int sigaction(int signum ,const struct sigaction *act, struct sigaction *oldact);
    + signum 시그널(SIGKILL & SIGSTOP 제외)이 수신됐을 때, 수행할 새로운 액션은 act가 됙, 이전 액션은 oldact에 저장된다. 성공하면 0을, 실패하면 -1을 반환한다.
  + 시그널 처리 액션은 구조체 형태로 정의되고, 각 필드에 대한 설명은 다음과 같다.
    + void (*sa_handler)(int) : 시그널 처리기를 나타내는 필드로 SIG_DFL, SIG_IGN, 사용자 정의 함수로 지정할 수 있다.
    + void (*sa_sigaction)(int, siginfo_t *, void *) : sa_flags가 SA_SIGINFO일 때 sa_handler 대신에 동작하는 시그널 처리기. 시그널 번호, 시그널이 만들어진 이유, 시그널을 받는 프로세스 등을 받을 수 있다.
    + sigset_t sa_mask : 시그널을 처리하는 동안 차단할 시그널 집합. 이런 기능을 시그널 마스크라 한다.
    + int sa_flags : 시그널 처리 절차를 수정하는데 사용. 아래와 같은 값이 있다.
      + SA_SIGINFO : sa_handler 대신 sa_sigaction 사용.
      + SA_NOCLDSTOP : signum이 SIGCHLD일 경우, 자식 프로세스가 종료되거나 중단되었을 때 부모 프로세스에게 SIGCHLD가 전달되지 않는다.
      + SA_ONESHOT : 시그널을 받으면 설정된 액션을 하고 시스템 기본 설정인 SIG_DFL로 재설정된다.
      + SA_NOMASK : 시그널을 처리하는 동안에 전달되는 시그널은 차단되지 않는다.

### 3. Executuon and Inheritance 
+ 부모 프로세스가 정의한 signal handler는 
  1) fork() 할 시, 자식 프로세스는 exact the same signal semantics as the parent를 상속받는다.
  2) 쉘에서 실행 시 주소 공간을 공유하지 않으니 부모가 설정한 핸들러가 default로 바뀐다.
+ 자식 프로세스가 생성되고 exec() 되면, 부모 프로세스와 주소 공간을 공유하지 않기 때문에 부모가 사용하던 signal hadlers를 사용하지 못하고 시그널 액션은 기존의 default action으로 수행한다.
+ background에서 새로 executed 되는 프로세스는 interrupt & quit character(SIGINT & SIGQUIT)를 ignore(SIG_IGN) 해야 한다. (예. 쉘 프로세스는 SIGINT & SIGQUIT가 무시되어야 한다.)

### 4. 시그널 보내기
+ kill 명령어를 사용해 특정 프로세스에 임의의 시그널을 강제적으로 보낸다. 
  + 커맨드 명령어 kill -l로 시그널 리스트를 출력할 수 있고, 출력된 리스트는 1번부터 순서대로 나열된다.
  + kill -시그널 PID
+ kill() syscall은 원하는 pid에 시그널 signo를 보낼 수 있다.
  + int kill(int pid, int signo)
    + pid에 signo를 보내고, 성공하면 0, 실패하면 -1을 반환한다.
    + pid > 0 : 특정 pid에 시그널을 보냄.
    + pid == 0 : PGID가 동일한 프로세스들에게 시그널을 보낸다.
    + pid < 0 : PGID가 똑같고 pid의 절대값이 같은 프로세스에게 시그널을 보낸다.
    + pid == -1 : POSIX.1에서는 unspecifed condition으로 정함(used as a broadcast signal in SVR4, 4.3+BSD).
+ 시그널 보내기가 성공하기 위해서는 보내는 프로세스의 사용자가 프로세스 pid의 사용자와 같거나 혹은 보내는 프로세스의 사용자가 슈퍼유저여야 한다.
+ raise() 함수를 사용해 자기 자신에게 시그널을 보낼 수 있다.
  + int raise(int sigCode);
  + 사실 kill(getpid(), signo)와 같다.

### 5. 시그널과 비지역 점프(Non-local jump)
+ 예외를 만나거나 인터럽트 시그널을 받게되면, 프로세스의 실행 위치가 어디에 있던지 프로그램의 특정 루틴으로 돌아가야 하는 상황을 생각해볼 수 있다. 이러한 상황은 setjmp()와 longjmp() 두 함수를 이용하여 처리할 수 있다.
+ longjmp() 함수는 일종의 비지역 점프로, setjmp() 함수에 의해 설정된 지점으로 점프하게 된다.
  + void longjmp(jmp_buf env, int val);
  + env에 저장된 상태를 복구하여 스택 내용 드잉 저장된 곳으로 비지역 점프한다. 상응하는 setjmp() 함수가 실행된 뒤 val 값을 반환하게 한다.
+ setjmp() 함수는 두 번 반환할 수 있는데, 처음 호출되었을 때는 복귀 주소를 포함한 프로그램의 현재 상태(주로 runtime stack 내용)를 저장하고 반환한다. longjmp()를 호출 한 뒤 setjmp() 함수에 으해 저장된 상태를 복구하면 두 번째로 setjmp() 함수가 반환된다. 처음 반환시 0을 반환, 두 번째는 0이 아닌 값을 반환한다.
  + int setjmp(jmp_buf env);
  + 비지역 점프를 위해 스택 내용 등을 env에 저장한다. setjum()는 처음 반환할 때 0을 반한, 두 번째에 0이 아닌 longjmp에 의해 전해지는 val 값을(longjmp 함수에 넘겨주는 인자 값) 반환한다.
