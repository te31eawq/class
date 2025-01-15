### Chapter 4: Echo 서버-클라이언트 통신

이번 챕터에서는 **Echo 서버와 클라이언트**를 구현한 예제입니다. 서버는 클라이언트로부터 받은 메시지를 그대로 되돌려주는 역할을 하며, 클라이언트는 사용자로부터 입력받은 메시지를 서버로 보내고, 서버로부터 받은 메시지를 출력합니다.

#### 주요 개념
1. **서버-클라이언트 통신**: 서버는 클라이언트로부터 메시지를 읽고, 그 메시지를 다시 클라이언트에게 보내는 방식으로 동작합니다.
2. **소켓 통신**: 클라이언트는 서버에 연결한 후, 메시지를 전송하고 서버로부터 응답을 받습니다.
3. **반복적인 통신**: 클라이언트는 사용자 입력을 계속해서 서버에 전송하고, 서버는 그 메시지를 그대로 응답합니다.

---

### 4.1 Echo 서버 코드 (`echo_server.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof(clnt_adr);

    for(i = 0; i < 5; i++) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock == -1)
            error_handling("accept() error");
        else
            printf("Connected client %d \n", i + 1);

        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
            write(clnt_sock, message, str_len);

        close(clnt_sock);
    }

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
- **서버**는 `socket()`, `bind()`, `listen()`, `accept()`를 사용하여 클라이언트와 연결을 설정합니다.
- 클라이언트가 연결되면, `read()`를 통해 클라이언트가 보낸 메시지를 읽고, `write()`를 사용하여 동일한 메시지를 클라이언트에게 다시 보냅니다.
- 5명의 클라이언트와 통신을 처리할 수 있도록 반복문을 사용합니다.
- **메시지 송수신**: 서버는 클라이언트로부터 받은 메시지를 그대로 되돌려주는 방식으로 에코 기능을 구현합니다.

### 4.2 Echo 클라이언트 코드 (`echo_client.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;

    if(argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected...........");

    while(1) {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;

        write(sock, message, strlen(message));
        str_len = read(sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Message from server: %s", message);
    }

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
- **클라이언트**는 서버에 연결을 시도하고, 연결되면 사용자로부터 메시지를 입력받아 서버로 보냅니다.
- 클라이언트는 `fgets()`로 메시지를 입력받고, `write()`를 통해 서버로 메시지를 전송합니다. 서버로부터 메시지를 받으면 `read()`로 수신하고, 이를 출력합니다.
- 클라이언트는 "q" 또는 "Q"를 입력하면 종료됩니다.
- **에코 기능**: 클라이언트가 보낸 메시지를 서버가 그대로 돌려주는 구조입니다.

---

### 코드 흐름 요약
1. **서버**:
   - 클라이언트가 연결되면 `accept()`를 사용하여 연결을 설정하고, `read()`로 클라이언트로부터 메시지를 읽은 후 `write()`로 다시 보내는 방식으로 에코 기능을 수행합니다.
   - 5명의 클라이언트와 통신을 처리하며, 각 클라이언트가 종료되면 연결을 닫고 새로운 클라이언트와의 연결을 기다립니다.

2. **클라이언트**:
   - 서버에 연결하고, 사용자가 입력한 메시지를 서버로 전송합니다.
   - 서버로부터 받은 메시지를 출력하고, "q" 또는 "Q"가 입력되면 종료됩니다.

### 주요 특징
- **에코 서버**: 서버는 클라이언트가 보낸 메시지를 그대로 다시 돌려주는 기능을 수행합니다.
- **반복적인 통신**: 클라이언트는 사용자로부터 입력을 계속해서 받고, 서버는 그 입력을 그대로 되돌려주는 방식으로 반복적으로 통신합니다.
- **`read()`와 `write()`**: 서버와 클라이언트 모두 `read()`와 `write()` 시스템 호출을 사용하여 데이터를 송수신합니다.

### 개선된 점
- **메시지 처리**: 클라이언트와 서버는 간단한 문자열 메시지를 송수신하는 방식으로, TCP 연결을 통해 신뢰성 있는 데이터 전송을 보장합니다.
- **`BUF_SIZE` 상수 사용**: 버퍼 크기를 상수로 정의하여 코드의 유지보수성을 높였습니다.