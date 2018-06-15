# 소켓

### 0. 첨부한 파일
+ fserver.c & fclient.c 는 파일을 주고받는 소켓 프로그래밍의 예제다.

### 1. 소켓
+ sockets : low level form of communication between distributed processes.
+ 소켓은 세 가지 관점으로 바라볼 수 있다.
  1. 데이터 타입 : OS가 통신을 위해 관리하는 데이터를 간접적으로 참조할 수 있도록 만든 일종의 핸들(handle). 생성과 설정 과정이 끝나면 이를 이용하여 통신과 관련된 다양한 작업을 할 수 있는 간편한 데이터 타입.
  2. 통신 종단점(communication end-point) : 소켓은 통신을 위해 필요한 여러 요소의 집합체(프로토콜, IP & 포트번호). 요소 정보를 포인트로 서로 통신을 함.
  3. 네트워크 프로그래밍 인터페이스 : 통신 양단이 모두 소켓을 사용할 필요는 없다. 통신을 위한 인터페이스다.
+ 소켓은 양방향 통신 방법으로 1) 유닉스 소켓(AF_UNIX) : 같은 호스트 내의 프로세스 사이 통신 방법,  2) 인터넷 소켓(AF_INET) : 인터넷에 연결된 서로 다른 호스트에 있는 프로세스 사이의 통신 방법. 총 두 가지가 있다.
+ 서버 : socket 생성 -> bind -> listen -> accept -> read & write -> close
+ 클라이언트 : socket 생성 -> connect -> read & write -> close
+ 소켓 주소 구조체 : 네트워크 프로그램에서 필요로 하는 주소 정보를 담고 있는 구조체. 기본은 sockaddr이고, sockaddr_in과 _un이 파생됨.
  + sockaddr.sa_family : 주소 체계를 나타내는 상수값.
  + sockaddr.sa_data : 해당 주소 체계에서 사용하는 주소 정보(IP & 포트 번호, 소켓 이름).
+ socket() 함수로 소켓 생성시 __Family & Type & Protocol 정보와__ __Local Socket Address & Remote Socket Address__ 에 대한 정보를 담을 수 있는 구조체가 생성된다. Local에는 자기의 port나 family, addr 정보를, Remote에는 후에 accept & connect가 이뤄질 시 상대방에 대한 정보가 담긴다.
+ 소켓에 주소(이름)를 주기 위해 bind() 함수를 사용한다.
+ 소켓 큐를 생성하기 위해 listen() 함수를 사용한다.
+ 소켓에 연결 요청을 위해 connect() 함수를 호출한다.
+ 소켓 연결 요청을 수락하기 위해 accept() 함수를 호출한다.
+ 
+ 

### 2. TCP/IP 프로토콜
+ 애플리케이션 계층 (TELNET, FTP, HTTP, ... )
+ 전송 계층 (TCP, UDP)
+ 인터넷 계층 (IP)
+ 네트워크 액세스 계층 (디바이스 드라이버, 네트워크 하드웨어)
+ TCP : connection-oriented(연결형) 프로토콜. 연결이 성공해야 통신 가능. 데이터 경계를 구분하지 않는 byte-stream 서비스. 신뢰성 있는 전송을 위해 필요시 데이터 재전송. 1:1 통신에 주로 사용(unicast).
+ UDP : connectionless-oriented(비연결형) 프로토콜. 연결 없이 통신 가능. 데이터 경계를 구분하는 datagram 서비스. 데이터를 재전송하지 않아서 신뢰적이지 못함. 1:1, 1:다(broadcast), 다:다 (multicast) 통신에 사용.

### 3. 패킷
+ 패킷(packet)은 각 프로토콜에서 정의한 제어 정보(IP 주소, 포트 번호, ...) + 데이터로 구성된다(헤더 + 데이터 + 트레일러).

### 4. IP 주소와 포트 번호
+ IP 주소 : 인터넷에 존재하는 호스트(터미널, 라우터)를 유일하게 구별할 수 있는 식별자. 
  + IPv4는 32비트, v6는 128비트 사용.
  + 8비트 단위로 구분하여 10진수로 표기한다(IPv4)

+ 포트 번호 : 통신 종착지를 나타내는 식별자. 프로그램에 붙는 번호.

### 5. 바이트 정렬
+ byte ordering : 메모리에 데이터를 저장할 때의 바이트 순서. 
+ 네트워크 바이트 정렬은 빅 엔디안 방식이지만, 호스트 시스템에서 쓰는 방식은 리틀 엔디안을 쓸 수도 있기 때문에 바이트 정렬 방식을 고려해야 한다.
+ Host -> Network : hton  ==  소켓 함수에 데이터 넘겨줄 때 사용.
+ Network -> Host : ntoh  ==  소켓 함수에서 어플리케이션을 데이터가 넘어올 때 사용.

### 6. DNS
+ Domain Name System : 인터넷의 IP 주소와 도메인 이름 사이의 맵핑.  
+ hostent 구조체를 사용한다. 
+ IP 주소는 IP 주소 구조체인 in_addr에 저장된다.
+ in_addr에 저장된 IP 주소를 출력할 수 있는 A.B.C.D 포맷의 스트링으로 변환하는 inet_ntoa().
+ A.B.C.D 포맷의 IP 주소를 네트워크 바이트 순서로 된 이진 데이터로 변환하는 inet_addr().

### 7. 소켓 프로그래밍. 서버 클라이언트 구조 개략
1. 서버가 리슨 큐를 생성한 후, 클라이언트의 connent를 accept 대기하고 있다.
2. 클라이언트가 connect 요청을 한 후, 서버는 요청을 accept 하며 새로운 fd를 만들어 연결한다.
3. 서버가 fork() 한다.
4. 서버의 부모 프로세스는 accept 한 fd를 close하고(parent closes ephemeral port), 자식은 listen 용 fd를 close한다(cild closes well-known port).
5. read & write 작업.
6. 클라이언트 연결이 끊기면, 서버의 자식은 accept 용 fd를 닫고 종료한다.
