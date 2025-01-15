### Chapter 1: 기본 서버-클라이언트 통신

이 챕터에서는 **서버와 클라이언트 간의 기본적인 TCP/IP 통신**을 구현한 예제 코드입니다. 서버는 클라이언트로부터의 연결을 기다리고, 클라이언트는 서버에 연결 후 데이터를 수신하는 구조입니다.

#### 주요 개념
1. **TCP 소켓**: 서버와 클라이언트 간의 통신을 위해 TCP 소켓을 사용합니다. 이는 신뢰성 있는 연결 지향적인 통신을 제공합니다.
2. **소켓 함수**: `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `read()`, `write()` 등의 시스템 콜을 통해 통신을 처리합니다.
3. **IP 주소 및 포트 설정**: 서버와 클라이언트가 서로 연결하기 위해 IP 주소와 포트를 설정하여 상대방을 식별합니다.

---

### 1.1 서버 코드 (`hello_server.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
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
    if(serv_sock < 0) error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("bind() error");

    if(listen(serv_sock, 5) < 0)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock < 0)
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
- **소켓 생성**: `socket()`을 통해 TCP 소켓을 생성합니다. `PF_INET`은 IPv4 프로토콜을, `SOCK_STREAM`은 TCP 소켓을 의미합니다.
- **주소 설정**: `serv_addr` 구조체를 사용하여 서버의 IP 주소와 포트를 설정합니다. `INADDR_ANY`는 모든 네트워크 인터페이스에서의 연결을 허용합니다.
- **바인딩**: `bind()`를 통해 생성한 소켓에 IP와 포트를 할당합니다.
- **연결 대기**: `listen()`은 클라이언트의 연결을 대기하는 상태로 전환합니다.
- **클라이언트 연결 수락**: `accept()`로 클라이언트의 연결을 수락하고, 연결된 클라이언트에게 메시지를 전송합니다.

---

### 1.2 클라이언트 코드 (`hello_client.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0) error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("connect() error!");

    str_len = read(sock, message, sizeof(message)-1);
    if(str_len < 0) error_handling("read() error!");

    printf("Message from server: %s \n", message);
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
- **소켓 생성**: 서버와의 연결을 위해 `socket()`을 사용하여 클라이언트 소켓을 생성합니다.
- **서버 주소 설정**: `serv_addr` 구조체에 서버의 IP 주소와 포트를 설정합니다.
- **서버에 연결**: `connect()`를 통해 서버와 연결을 시도합니다. 연결이 성공하면 데이터를 읽습니다.
- **메시지 수신**: 서버에서 전송한 메시지를 `read()`로 수신하고, 받은 메시지를 출력합니다.

---

### 코드 흐름 요약
1. **서버**는 먼저 소켓을 생성하고, 포트 번호를 설정하여 클라이언트의 연결을 기다립니다.
2. **클라이언트**는 서버의 IP 주소와 포트를 지정하여 서버에 연결을 요청합니다.
3. **서버**는 연결이 들어오면, "Hello World!"라는 메시지를 클라이언트로 전송합니다.
4. **클라이언트**는 서버로부터 메시지를 받아 출력합니다.

### 주요 특징
- **소켓 통신**을 사용하여 클라이언트와 서버 간의 데이터 전송을 구현합니다.
- 클라이언트와 서버가 연결되는 구조는 **연결 지향적 통신**(TCP)으로 안정적이며 신뢰성이 높은 데이터 전송을 보장합니다.
