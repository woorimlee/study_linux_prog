# 파이프

### 0. 첨부한 파일
+ pipe.c는 '1. 이름없는 파이프'의 pipe() 함수를 쓰는 예시다.
+ pipe_exec.c는 '2. 쉘 파이프 구현'에서 dup()를 사용한 표준 출력과 파이프를 응용하는 예시다.
  + ex) $ ./pipe_exec date
+ shell_pipe.c는 '2. 쉘 파이프 구현'에서 쉘 파이프를 구현한 예시다.
  + ex) # ./shell_pipe  -> [shell]ls|wc
+ popen_exec.c는 '3. 파이프 함수'에서 popen() 함수를 쓰는 예시다.
  + ex) # ./popen_exec date
+ pipe_chat_server.c & pipe_chat_client.c는 파이프 두 개를 이용한 양방향 채팅 프로그램이다. 

### 1. 이름 없는 파이프
+ 파이프 개념 : 두 개의 파일 디스크립터를 사용해 하나는 쓰고 하나는 읽는다. 이런 방식으로 IPC를 한다. 데이터를 한 방향(One way)으로만 보낼 수 있다. (Half duplex)
+ 파이프를 통해 보낼 수 있는 데이터의 양에는 제한이 없다.
+ 조상이 같아야만 파이프를 통해 데이터 전송이 가능하다.
+ 파이프는 open하는 것이기 때문에 자동으로 동기화가 된다.
+ 자식 프로세스는 부모 프로세스의 pipes를 상속받는다.
  + 부모 자식중 쓰는 read 용은 write pipe fd를 닫고, write 용은 read pipe fd를 닫는다. 그 후 각 프로세스가 read & write() 함수를 호출하며 파이프 fd를 통해 데이터를 송수신한다.
  
  
(regular file 들을 이용한 IPC는 1) unrelated processes 간에 공유가 가능하고,  2) 고정된 사이트로 전송되고,  3) life-time이 존재하고,  4) lack of synchronization의 특징이 있다.)
+ pipe() syscall은 fd[2]의 배열을 넘겨 fd[0]에 읽기용, fd[1]에 쓰기용 fd를 생성하는 함수다. 성공하면 0을, 실패하면 -1을 반환한다.
+ 쓰기용 파이프는 메세지를 보내다가 너무 많은 양이 보내지면 automatic blocking이 되고, 읽기용 파이프는 읽는 양이 파이프 안 내용물보다 많으면 automatic blocking이 걸린다.

### 2. 쉘 파이프 구현
+ 쉘 파이프와 같은 기능을 구현하려면 한 프로세스의 표준출력을 파이프를 통해 다른 프로세스에게 보낼 수 있어야 한다.
+ pipe() 함수를 사용하고 dup() 함수를 사용해, 파이프를 생성하고 표준 입출력의 fd에 파이프를 복사해주면 된다.
+ command 1의 표춘 출력을 command 2의 표준 입력으로 받는다. 파이프 구분을 위해 strchr() 함수와 strtok() 함수를 사용한다.

### 3. 파이프 함수
+ popen() 함수를 사용해서 커맨드 명령어를 파이프로 읽고 쓸 수 있다.
+ FILE *popen(const char *command, const char *type)
  + 자식 프로세스를 생성하고 자식 프로세스에게 명령어를 실행시켜 표준 출력이나 입력을 파이프를 통해 보낸다.
+ int pclose(FILE *fp);
  + 성공하면 command 명령어의 종료 상태를, 실패하면 -1을 반환한다.

### 4. 이름 있는 파이프
+ 기존의 파이프는 이름이 없었기에 서로 관련이 있는 부모 자식 프로세스간에만 사용이 가능했다. 이런 문제점을 해결하기 위해 named pipe가 고안됐고, fifo라고도 부른다.
+ 일반 파일처럼 이름이 있는 상태로, 파일 시스탬 내에 존재한다(fifo file이라 한다).
+ 파이프를 만드는 방법은
  1. 쉘 상에서 mknod 명령어에 -p 옵션을 사용하여 만드는 것이다.
    + ex) # mknod 파이프이름 p
    + ls -l 명령어로 확인해보면 첫 번째 글자가 p로, 파이프임을 나타낸다.
  2. mkfifo() syscall을 사용해 named pipe를 만들 수 있다.
    + int mkfifo(const char *path, mode_t mode);
    + 성공하면 0, 실패하면 -1을 반환한다.
+ 만들어진 파이프를 사용하기 위해서는 먼저 파이프를 open 해야 한다. 그 후 write()와 read()를 하면 된다.

