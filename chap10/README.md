# Chapter 10 : 메모리 관리

### 0. 첨부한 파일
+ student_malloc.c는 '2. 동적 할당'에 관한 간단한 예시다.
+ student_linked_list_stack.c는 '3. Linked list'에서 stack 형태로 구성한 사용 예시다.
+ student_linked_list_queue.c는 '3. Linked list'에서 queue 형태로 구성한 사용 예시다.
+ mem_family.c는 '4. 메모리 관리 함수'의 함수들 사용 예시다.

### 1. 변수와 메모리
+ 프로그램을 실행 -> 메인 메모리에 프로그램이 탑재 됨 -> 이 상태를 __프로세스__ 라고 함.
+ 프로그램을 실행시키기 위해 필요한 메모리를 모두 합쳐 __프로세스 이미지__ 라고 함.
  + 프로세스 이미지 내 __Text segment__ 에는 프로그램 코드와 리터럴 상수 등이 저장 됨(이 영역 내 값은 거의 변경되지 않으므로 정적 영역이라고 할 수 있다).
  + __Data segment__ 에는 전역 변수나 정적 변수들을 저장한다. 프로그램이 시작될 때 할당되어 프로그램이 끝날 때까지 지속된다.
  + __Stack__ 은 함수 호출을 구현하기 위한 Runtime stact(실행시간 스택)을 위한 메모리 영역으로, 함수가 호출될 때마다 Activation record(활성 레코드. 매개변수, 반환주소, 반환 값, 지역 변수 등)가 스택에 자동으로 할당된다. 활성 레코드는 Stack frame(스택 프레임)이라고도 부른다. 이렇게 함수 호출/복귀에 따라 자동으로 할당/해제되는 변수를 C에서는 Automatic variable(자동 변수)라고 부르고 키워드 auto를 사용하기도 하지만, 보통 지역변수는 기본적으로 자동변수로 인식하기 때문에 auto를 생략한다.
  + __Heap segment__ 에는 선언하지 않고도 필요할 때 필요한 만큼만 동적으로 메모리를 요청해 사용할 수있다. 이런 변수들은 Dynamic variable(동적 변수)이라고 부른다.
    + Funtions for dynamic memory allocation : 
      1) malloc : allocate memory spacle
      2) calloc : allocate memory space and initialize it to zero
      3) free : frees previously allocated memory space
      4) realloc : modifies the size of previously allocated space.

### 2. 동적 할당
+ malloc으로 메모리 할당 받은 뒤, free로 메모리 공간 해제할 때 매개변수 인자로 포인터만 넘기면 C runtime system이 공간의 크기가 얼마인지 관리해주기 떄문에 알아서 메모리 해제를 해준다. 
+ 동적 메모리 할당을 스택에 하고 싶다면 alloca() 함수를 사용하자. 이 함수는 스택에 메모리 할당을 해주기 때문에, 따로 메모리 해제를 할 필요가 없다(호출된 함수 반환시 자동 메모리 해제).
+ 동적 할당은 Static allocation(정적 할당)에 비해 약간 느리고, 덜 reliable한 단점이 있다(스태틱 할당은 compilation time에 memory spaces에 보관되기 때문에).

### 3. Linked list
+ 같은 타입의 데이터 항목 여러 개를 포인터를 통해 연결하는 연결리스트는 메모리 관리를 더욱 효율적으로 활용하게 만들어준다.
+ Linked list의 맨 앞 항목을 가리키는 포인터를 Head라고 한다. 연결리스트의 끝을 가리키는 포인터는 tail이라고 한다(사용 할 수도 있고 안 할 수도 있고).
  + 새로운 데이터가 생성되고 Linked list의 헤드 부분이 그것을 가리키게하면 stack 형태로 구성된다(LIFO).
  + 새로운 데이터를 연결리스트의 끝 부분에 추가하면 queue 형태로 구성된다(FIFO). 이때 tail을 써야한다.

### 4. 메모리 관리 함수
+ void *memset(void *s, int c, size_t n);
  + s가 가리키는 곳에서 n 바이트 만큼 c로 설정한다. s를 반환한다.
  + 보통 메모리 블록을 0으로 채울 때 많이 사용한다. 
    + memset(s, 0x00, sizeof(*s));
    + calloc()를 사용할 수 있다면 malloc + memset 으로 메모리 0 초기화 하는 작업을 사양하도록 하자. calloc() 한 번으로 함수 호출 횟수를 줄일 수 있을 뿐 아니라, 수동으로 모든 바이트를 0으로 초기화하는 작업을 피할 수 있어서 성능이 향상되기 때문이다.
    + calloc(sizeof(*s)로 만들고자 하는 갯수, sizeof(*s));
+ void *memcmp(const void *s1, const void *s2, size_t n);
  + s1과 s2에서 첫 n 바이트를 비교해서 메모리 블록 내용이 동일하면 0을, s1이 s2보다 작으면 음수를, s1이 s2보다 크면 양수를 반환한다.
+ void *memchr(const void *s, int c, size_t n);
  + s가 가리키는 메모리의 n 바이트 범위에서 문자 c를 찾는다. c와 일치하는 첫 바이트에 대한 포인터를 반환하거나, c를 못 찾으면 NULL을 반환한다.
+ void *memrchr(const void *s, int c, size_t n);
  + s가 가리키는 메모리의 뒤에서부터 n 바이트 범위에서 탐색을 시작.
+ void *memmove(void *dst, void *src, size_t n);
  + src에서 dst로 n 바이트를 복사하고, dst를 반환.
+ void *memcpy(void *dst, const void *src, size_t n);
  + src에서 dst로 n 바이트를 복사하되, 두 메모리 영역은 겹쳐지지 않는다. dst를 반환.
