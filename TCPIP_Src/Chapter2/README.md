### Chapter 2: 개선된 TCP 서버-클라이언트 통신

이 챕터에서는 **TCP 서버와 클라이언트 간의 데이터 통신**을 구현하면서, **읽기 방식**에 있어 좀 더 세부적인 개선이 이루어진 예제 코드입니다. 서버는 여전히 클라이언트와 연결을 통해 메시지를 보내며, 클라이언트는 받은 메시지를 출력합니다. 하지만 이번에는 메시지 읽기와 처리 방식에 차이가 있습니다.

#### 주요 개념
1. **소켓 생성 및 연결**: 서버와 클라이언트가 TCP 소켓을 생성하고 연결하는 방식은 동일하지만, 데이터 읽기 방식에서 변화가 있습니다.
2. **`read()` 함수 사용**: 클라이언트가 데이터를 받을 때 `read()` 함수를 사용하여 한 번에 하나씩 데이터를 읽고, 그 결과를 누적합니다.
3. **연결 종료**: 서버와 클라이언트가 통신을 마친 후 소켓을 종료하는 방식도 유사하지만, 클라이언트의 데이터 수신 로직에서 차이가 있습니다.

---

### 2.1 서버 코드 (`tcp_server.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
        error_handling("accept() error");

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

#### 설명
- 서버 코드에서는 클라이언트가 연결되면 `"Hello World!"`라는 메시지를 전송합니다.
- **소켓 연결**과 관련된 절차는 기존과 동일합니다.
- `accept()`로 클라이언트와 연결이 성사되면, 메시지를 전송하고 클라이언트와의 연결을 종료합니다.

### 2.2 클라이언트 코드 (`tcp_client.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len = 0;
    int idx = 0, read_len = 0;

    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");

    while(read_len = read(sock, &message[idx++], 1)) {
        if(read_len == -1)
            error_handling("read() error!");

        str_len += read_len;
    }

    printf("Message from server: %s \n", message);
    printf("Function read call count: %d \n", str_len);
    close(sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

#### 설명
- **소켓 연결**: 클라이언트는 서버와 연결하기 위해 IP 주소와 포트를 사용합니다.
- **`read()` 함수**: 서버로부터 데이터를 읽을 때 `read()` 함수를 사용하여 하나의 바이트씩 읽습니다. 이 방식은 메시지가 끝날 때까지 반복적으로 `read()` 호출을 통해 데이터를 수신합니다.
- **메시지 출력**: 클라이언트는 서버에서 받은 메시지를 출력하며, `read()` 함수가 몇 번 호출되었는지 카운트하여 출력합니다.

---

### 코드 흐름 요약
1. **서버**는 `socket()`, `bind()`, `listen()`, `accept()`를 통해 연결을 설정하고, `"Hello World!"`라는 메시지를 클라이언트에 전송합니다.
2. **클라이언트**는 서버와 연결 후 `read()`를 사용하여 데이터를 하나씩 수신하고, 최종적으로 수신된 메시지와 `read()` 호출 횟수를 출력합니다.

### 주요 특징
- **데이터 수신 방식**: 클라이언트가 데이터를 **한 번에 하나씩** 읽는 방식으로 수정되었습니다. 이는 데이터가 길어질 경우 여러 번에 걸쳐 `read()` 호출을 통해 수신되는 특징을 가집니다.
- **클라이언트의 `read()` 호출 횟수**: 클라이언트는 데이터를 읽을 때마다 호출 횟수를 추적하여 출력하는데, 이를 통해 데이터가 어떻게 읽히는지 확인할 수 있습니다. 
- **서버의 메시지 전송 방식**: 여전히 서버는 데이터를 한 번에 전송하지만, 클라이언트는 하나의 바이트씩 읽기 때문에 메시지를 전송받는 방식에 있어 차이를 보입니다.

### 개선된 점
- **수신 방식의 유연성**: `read()`를 하나의 바이트씩 반복 호출함으로써, 클라이언트는 수신하는 데이터의 길이를 알지 못해도 점진적으로 데이터를 처리할 수 있게 되었습니다. 이는 **비동기적**으로 데이터를 처리하는 방식에 가까운 접근법입니다.
