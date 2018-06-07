## 1. Pthread
#### 스레드 관리
+ 스레드 생성, 종료, 조인, 디태치의 과정.

#### 동기화
+ 뮤텍스와 조건 변수, barrier 등의 방법이 제공됨.

#### pthread 사용시
+ glibc에서 pthread를 제공하지만 libpthread 라이브러리는 분리되어 있으므로, 링크를 해줘야 한다. -pthread 플래그로 링크하면 된다.

## 2. pthread 사용하기
#### 1. 스레드 생성하기
+ 프로그램을 처음 실행해서 main() 함수를 실행하는 시점에는 싱글스레드다. 이 기본 스레드(메인 스레드)에서 새로운 스레드를 생성해야 멀티스레드 프로그램이 된다.
+ pthread_creat() 함수를 사용해 새로운 스레드를 생성할 수 있다.
  + int pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
+ 호출이 성공하면 새로운 스레드가 생성되고 start_routine에 전달한 함수를 arg 매개변수를 갖고 실행한다.
  + start_routine에는 반드시 다음과 같은 형태를 갖춰야 한다.
    + void * start_thread(void *arg);
+ pthread_t 부분에는 NULL을 넣지 않는다면 새로 만든 스레드를 나타내기 위해 스레드 ID를 넣는다.
+ pthread_attr_t에는 새로 생성된 스레드의 기본 속성을 변경하기 위한 값을 넘긴다. 보통 널을 넘긴다.
+ fork를 이용하면 부모 프로세스의 리소스를 자식 프로세스가 복사해서 사용하지만, thread를 생성하면 부모와 소스를 공유한다. 시그널 핸들러와 열린 파일도 공유한다.

#### 2. 스레드 ID (TID)
+ TID는 PID와 유사하다. PID는 리눅스 커널에서 할당해죽, TID는 pthread 라이브러리에서 할당한다.
  + 리눅스 커널 입장에서 스레드는 리소스를 공유하는 프로세스일 뿐이다. 따라서 각 스레드를 유일한 PID 값을 통해 일반 프로세스처럼 구분한다.
+ pthread_creat() 호출이 성공하면 thread 인자에 TID가 저장된다. 이때 pthread_self() 함수를 이용해서 자신의 TID를 얻을 수 있다.
  + pthread_t pthread_self (void);
+ Pthread 표준에서 __pthread_t가 int 타입이라고 강제하지 않기 때문에 '==' 연산자가 동작하리라 보장할 수 없다.__ 따라서 스레드 ID를 비교하려면 Pthread 라이브러리에서 제공하는 pthread_equal() 함수를 사용해야 한다.
  + int pthread_equal (pthread_t t1, pthread_t t2);
  + 매개 변수로 넘길 두 인자가 같은 값이면 0이 아닌 값을 반환하고, 다르면 0을 반환한다.

#### 3. 스레드 종료하기
+ 하나의 스레드가 종료되는 상황
  1) start_routine 함수가 반환한 경우. 이는 main() 함수가 다 끝나고 return 한 상황과 비슷하다.
  2) pthread_exit() 함수를 호출한 경우. exit() 함수 호출과 비슷하다.
  3) pthread_cancel() 함수를 누군가 호출해 다른 스레드에 의해 중지된 경우. kill()을 통해 SIGKILL을 보낸 경우와 비슷하다.
+ 한 프로세스 내 전체 스레드가 종료되는 경우.
  1) 프로세스의 main() 함수가 반환한 경우.
  2) 프로세스가 exit() 호출로 종료된 경우.
  3) 프로세스가 execve() 호출로 새로운 바이너리를 실행한 경우.
+ pthread_exit를 호출하면 호출한 스레드가 종료된다.
  + void pthread_exit (void *retval); 
  + retval은 이 스레드의 종료를 기다리는 다른 스레드에 전달할 값이고, exit(x)에서 x에 넣는 값과 같다.
+ pthread_cancel() 함수를 통해 다른 스레드를 취소시켜 종료할 수 있다.
  + int pthread_cancel (pthread_t thread);
  + 이 호출이 성공하면 thread로 명시한 TID를 가진 스레드에 취소 요청을 보낼 수 있다. 스레드의 취소 상태와 타입에 따라 취소 가능한지 등이 결정된다.
  + 성공시 0을 반환한다. 실패시 thread가 유효하지 않아서다.
    + 스레드 취소 상태가 불가능이라면(가능이 default), 해당 요청은 취소 상태가 가능할 때까지 큐에서 대기한다. 이런 스레드의 취소 상태는 pthread_setcancelstate() 함수를 통해 변경할 수 있다. 여기선 다루지 않는다.
  + 스레드 취소의 타입은 1) 비동기와 2) 취소 유예의 두 가지가 있다. 
    1) 비동기 취소는 취소 요청이 들어오면 언제든지 종료시킬 수 있다. 하지만 취소될 스레드가 크리티컬 섹션 안에 있다면 큰일나기 때문에 
    2) 취소 유예의 방식이 default다. 그래야 안전한 특정 시점에서만 종료시킬 수 있기 때문이다.
  + 취소 타입을 바꿀 땐 pthread_setcanceltype() 함수를 사용한다. 여기선 다루지 않는다.

#### 4. 스레드 조인과 디태치
+ 프로세스에서 wait() 함수와 마찬가지로 스레드의 종료를 동기화해야 할 때 사용하는 함수가 join이다.
  + int pthread_join (pthread_t thread, void *(*retval));
  + 호출이 성공하면, 호출한 스레드는 thread 인자로 명시한 스레드가 종료될 때까지 block된다. 만약, 이미 종료된 스레드라면 이 함수는 즉시 return 된다.
    + thread로 명시한 스레드가 종료되면 호출한 스레드는 깨어나고 retval이 가리키는 곳에 스레드 종료시 넘기거나 반환한 값이 들어간다.
+ Pthread의 모든 스레드는 서로 동등하므로 어떤 스레드도 조인이 가능하다.

#### 5. 스레드 디태치
+ 기본적으로 스레드는 조인이 가능하다만, 가능하지 않도록 디태치하는 것도 가능하다.
+ 부모 프로세스에서 wait()을 호출하기까지 자식 프로세스가 시스템 리소스를 잡아먹는 것과 마찬가지로, 스레드도 조인이 되기 전까지 시스템 리소스를 잡아먹고 있으므로, 조인을 할 생각이 없는 스레드는 디태치해둬야만 한다. (좀비 프로세스 & 스레드 개념)
  + int pthread_detach(pthread_t thread);
  + 호출이 성공하면 thread로 명시한 스레드를 detach하고 0을 반환한다.
  + 에러 발생시 thread 인자가 유효하지 않은 것이다.
  + 이미 detach된 스레드에 대해선 호출 결과가 정의되어 있지 않다.
+ 스레드 join & detach를 통해 해당 스레드가 종료되었을 때 시스템 리소스를 해제할 수 있다.

## 3. 첨부된 예제 __thread_ex__  컴파일시 명령어
+ gcc -o thread_ex thread_ex.c -pthread

## 4. 첨부된 예제 __thread_ex__ 실행시
Thing 1
  
  
Thing 2
  
  
의 결과 값이 나오거나, 위 아래가 바뀔 수 있다.
스케줄링 기법에 따라 실행되는 순서가 다를 뿐이니 걱정하지 말자.

## 5. Pthread 뮤텍스
+ mutual exclusion을 보장하기 위한 한 가지 알고리즘인 뮤텍스.
+ Mutex는 사실 MUTual EXclusion의 줄임말이다.
  + pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  + mutex라는 이름의 뮤텍스를 선언하고 초기화하는 함수다.
+ 뮤텍스 락을 걸기 위해선 pthread_mutex_lock() 함수를 사용한다.
  + int pthread_mutex_lock (pthread_mutex_t *mutex);
  + 호출 성공시 mutex로 지정한 mutex가 사용가능해질 때까지 호출한 스레드를 block 한다.
  + 뮤텍스가 사용가능한 상태가 되면, 호출한 스레드는 꺠어나고 이 함수는 0을 반환한다(즉시 사용 가능한 상태면 이 함수는 바로 리턴)
  + 보통 에러가 나지 않기 때문에 반환 값을 따로 처리하거나 하진 않는다.
+ 뮤텍스 락을 해제하기 위해선 pthread_mutex_unlock() 함수를 사용한다.
  + int ptread_mutex_unlock (pthread_mutex_t *mutex);
  + 함수 호출 성공시 mutex로 지정한 뮤텍스를 해제하고 0을 반환한다.
  + 이 함수는 블록되지 않는다.

## 6. 첨부된 예제 __mutex_ex__ 
+ 의 .c파일에서 뮤텍스를 적용하기 전과 후의 결과물 차이를 통해 상호 배제에 따른 결과 차이를 알 수 있다.
