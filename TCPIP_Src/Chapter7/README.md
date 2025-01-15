### Chapter 7: 파일 전송 서버-클라이언트 통신

이번 챕터에서는 **파일 전송 서버와 클라이언트**를 구현한 예제를 다룹니다. 서버는 클라이언트에게 지정된 파일을 전송하고, 클라이언트는 서버로부터 파일을 받아 로컬에 저장합니다.

#### 주요 개념
1. **파일 전송**: 서버는 파일을 읽어서 클라이언트에게 데이터를 전송하고, 클라이언트는 이를 받아서 로컬 파일로 저장합니다.
2. **소켓 통신**: 파일을 송수신하는 과정에서 TCP 소켓을 사용하여 안정적인 데이터 전송을 보장합니다.
3. **버퍼 크기 조정**: 파일을 한 번에 전송할 수 없기 때문에 버퍼를 사용하여 일정 크기씩 나누어 전송합니다.

---

### 7.1 파일 서버 코드 (`file_server.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sd, clnt_sd;
    FILE *fp;
    char buf[BUF_SIZE];
    int read_cnt;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("file_server.c", "rb");  // 파일 열기
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);  // 소켓 생성

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));  // 포트에 바인딩
    listen(serv_sd, 5);  // 서버 리스닝 상태로 대기

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);  // 클라이언트 연결 수락

    // 파일 전송
    while(1) {
        read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);
        if(read_cnt < BUF_SIZE) {
            write(clnt_sd, buf, read_cnt);  // 마지막 조각 전송
            break;
        }
        write(clnt_sd, buf, BUF_SIZE);  // 버퍼 크기만큼 계속 전송
    }

    shutdown(clnt_sd, SHUT_WR);  // 전송 완료 후 종료 신호 전송
    read(clnt_sd, buf, BUF_SIZE);
    printf("Message from client: %s \n", buf);

    fclose(fp);
    close(clnt_sd); close(serv_sd);  // 연결 종료
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

#### 설명
- **서버**는 `file_server.c` 파일을 읽어서 클라이언트에게 전송합니다.
- `fread()`로 파일에서 일정 크기만큼 데이터를 읽고, `write()`를 사용하여 클라이언트에게 데이터를 전송합니다.
- 클라이언트가 데이터를 모두 받은 후, 서버는 전송을 종료하고 클라이언트에게 종료 메시지를 읽어 출력합니다.
- 서버는 **버퍼 크기**를 `BUF_SIZE`로 설정하여 한 번에 파일을 작은 조각으로 나누어 전송합니다.

---

### 7.2 파일 클라이언트 코드 (`file_client.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]) {
    int sd;
    FILE *fp;
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_adr;

    if(argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("receive.dat", "wb");  // 받은 파일 저장
    sd = socket(PF_INET, SOCK_STREAM, 0);  // 소켓 생성

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));  // 서버와 연결

    // 서버로부터 파일 수신
    while((read_cnt = read(sd, buf, BUF_SIZE)) != 0) {
        fwrite((void*)buf, 1, read_cnt, fp);  // 받은 데이터를 파일에 쓰기
    }

    puts("Received file data");
    write(sd, "Thank you", 10);  // 서버에게 감사 메시지 전송
    fclose(fp);
    close(sd);  // 연결 종료
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

#### 설명
- **클라이언트**는 서버에서 전송한 파일을 `receive.dat`라는 이름으로 저장합니다.
- `read()`로 서버로부터 파일 데이터를 일정 크기만큼 읽어와 `fwrite()`를 사용해 로컬 파일에 기록합니다.
- 파일 전송이 완료된 후, 서버에 "Thank you" 메시지를 전송하고 연결을 종료합니다.

---

### 코드 흐름 요약
1. **서버**:
   - `file_server.c` 파일을 클라이언트에게 전송합니다.
   - `fread()`와 `write()`를 사용하여 파일을 일정 크기씩 나누어 송신합니다.
   - 클라이언트가 모든 데이터를 수신하면 서버는 종료 신호를 보내고 연결을 종료합니다.

2. **클라이언트**:
   - 서버에 연결한 후, 데이터를 `read()`로 받습니다.
   - 받은 데이터는 `fwrite()`로 로컬 파일에 저장합니다.
   - 파일 전송이 완료되면 서버에 감사 메시지를 전송하고 연결을 종료합니다.

### 주요 특징
- **파일 송수신**: 서버는 파일을 읽어 클라이언트에게 전송하고, 클라이언트는 이를 받아서 로컬에 저장합니다.
- **버퍼 크기 조정**: 데이터를 일정 크기씩 나누어 전송하며, 이는 네트워크의 효율성을 높이고 대용량 파일의 전송을 가능하게 합니다.
- **소켓 통신**: TCP 소켓을 이용하여 서버와 클라이언트 간 안정적인 연결을 유지하며 데이터를 송수신합니다.

### 개선된 점
- **파일 전송의 효율성**: 데이터를 일정 크기만큼 나누어 전송하여 대용량 파일도 안전하게 전송할 수 있습니다.
- **파일 저장**: 클라이언트는 받은 데이터를 로컬 파일에 저장하며, 파일의 크기와 상관없이 전송을 받을 수 있습니다.
