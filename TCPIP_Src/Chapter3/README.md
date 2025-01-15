### Chapter 3: IP 주소 변환 함수 사용

이 챕터에서는 **IP 주소의 변환과 관련된 함수들**인 `inet_addr()`, `inet_aton()`, `inet_ntoa()`를 사용하는 예제를 다룹니다. 각 함수는 문자열 형식의 IP 주소를 네트워크 바이트 순서로 변환하거나, 그 반대로 변환하는 역할을 합니다.

#### 주요 개념
1. **`inet_addr()`**: 점-십진수 형식의 IP 주소를 **네트워크 바이트 순서의 정수**로 변환합니다. 이 함수는 IP 주소가 유효하지 않으면 `INADDR_NONE`을 반환합니다.
2. **`inet_aton()`**: IP 주소를 **네트워크 바이트 순서의 정수**로 변환하며, 성공하면 1을 반환하고, 실패하면 0을 반환합니다.
3. **`inet_ntoa()`**: 네트워크 바이트 순서의 IP 주소를 **점-십진수 형식**의 문자열로 변환합니다.

---

### 3.1 `inet_addr()` 예제 (`inet_addr.c`)

```c
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    char *addr1 = "127.212.124.78";
    char *addr2 = "127.212.124.256";  // 잘못된 IP 주소

    unsigned long conv_addr = inet_addr(addr1);
    if(conv_addr == INADDR_NONE)
        printf("Error occurred! \n");
    else
        printf("Network ordered integer addr: %#lx \n", conv_addr);

    conv_addr = inet_addr(addr2);
    if(conv_addr == INADDR_NONE)
        printf("Error occurred \n");
    else
        printf("Network ordered integer addr: %#lx \n\n", conv_addr);

    return 0;
}
```

#### 설명
- `inet_addr()` 함수는 문자열 형태의 IP 주소를 네트워크 바이트 순서로 변환합니다. 
- **올바른 IP**(`127.212.124.78`)은 정상적으로 변환되어 정수 형태로 출력됩니다.
- **잘못된 IP**(`127.212.124.256`)은 유효한 IP가 아니므로, `INADDR_NONE` 값이 반환되고 오류 메시지가 출력됩니다.
- **특징**: 이 함수는 이제는 사용이 권장되지 않으며, 대신 `inet_aton()`을 사용하는 것이 좋습니다.

---

### 3.2 `inet_aton()` 예제 (`inet_aton.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if(!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error");
    else
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

#### 설명
- `inet_aton()` 함수는 **점-십진수 형식의 IP 주소**를 **네트워크 바이트 순서의 정수**로 변환합니다. 이 함수는 변환이 성공하면 1을 반환하고, 실패하면 0을 반환합니다.
- 이 예제에서는 IP 주소 `"127.232.124.79"`를 `inet_aton()`을 사용하여 변환하고, 그 결과를 출력합니다.
- **특징**: `inet_aton()`은 `inet_addr()`보다 더 안전하게 IP 주소를 처리합니다.

---

### 3.3 `inet_ntoa()` 예제 (`inet_ntoa.c`)

```c
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);
    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1: %s \n", str_ptr);

    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s \n", str_ptr);
    printf("Dotted-Decimal notation3: %s \n", str_arr);

    return 0;
}
```

#### 설명
- `inet_ntoa()` 함수는 **네트워크 바이트 순서의 IP 주소**를 **점-십진수 형식의 문자열**로 변환합니다.
- `addr1`과 `addr2`는 각각 16진수로 정의된 주소값을 가지고 있으며, `inet_ntoa()`를 사용하여 이를 문자열 형식으로 변환합니다.
- **문제점**: `inet_ntoa()`는 **정적 메모리**를 사용하여 결과를 반환하므로, 두 번째 호출에서 이전에 변환된 결과가 덮어씌워지게 됩니다. 이 문제는 `str_arr`를 사용해 복사하여 해결합니다.
- **특징**: `inet_ntoa()`는 **단일 IP 주소**를 반환하며, 여러 번 호출하는 경우 반환된 결과가 덮어쓰여지므로 주의가 필요합니다.

---

### 코드 흐름 요약
1. **`inet_addr()`**: 점-십진수 형식의 IP 주소를 네트워크 바이트 순서의 정수로 변환하며, 유효하지 않은 주소에 대해서는 `INADDR_NONE`을 반환합니다.
2. **`inet_aton()`**: IP 주소를 네트워크 바이트 순서의 정수로 변환하며, 변환이 성공하면 1을 반환하고, 실패하면 0을 반환합니다.
3. **`inet_ntoa()`**: 네트워크 바이트 순서의 IP 주소를 점-십진수 형식의 문자열로 변환합니다. 반환된 문자열은 정적 메모리를 사용하므로, 여러 번 호출 시 덮어쓰여질 수 있습니다.

### 주요 특징
- **`inet_addr()`**는 더 이상 사용이 권장되지 않으며, 대신 **`inet_aton()`**을 사용하는 것이 좋습니다.
- **`inet_aton()`**은 성공 시 반환값이 1로 명확하고, 실패 시 0을 반환하여 오류 처리가 용이합니다.
- **`inet_ntoa()`**는 점-십진수 형식으로 IP 주소를 변환하며, 반환된 문자열은 여러 번 호출 시 덮어씌워지기 때문에 주의가 필요합니다.

### 개선된 점
- **`inet_aton()`의 사용**: `inet_aton()`을 통해 IP 주소 변환에 더 나은 오류 처리와 안정성을 제공합니다.
- **`inet_ntoa()` 반환 값 처리**: 반환된 문자열을 직접 사용하는 대신, 이를 **복사**하여 다른 변수에 저장하는 방식으로 안정성을 높였습니다.