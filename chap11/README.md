# 시그널

### 0. 첨부한 c 코드 
+ alarm.c는 '1. 시그널'의 SIGALRM을 사용하는 예시다.
+ alarm_handler.c는 '2. 시그널처리'의 SIGALRM을 사용하는 예시다.


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
  + SIGHUP : 터미널 연결이 끊겼을 시, 세션의 리더한테 이 신호를 보낸다. (종료) 
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
    
