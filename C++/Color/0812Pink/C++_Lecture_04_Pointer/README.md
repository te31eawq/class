## **C++ 배열과 포인터를 사용한 합계 계산 예제**

### 설명:
이 프로그램은 C++에서 배열과 포인터를 활용하여 배열의 합계를 구하는 다양한 방법을 보여주는 예제입니다. `pArr` 포인터를 사용하여 배열을 순회하고, 배열의 합을 세 가지 방식으로 계산하고 출력합니다.

### 코드 설명:

```cpp
int nArray[] = {1,2,3,4,5,6,7,8,9,10};
int* pArr = nArray;
int length = sizeof(nArray) / sizeof(int);
```
- `nArray[]` 배열은 1부터 10까지의 정수값을 포함합니다.
- `pArr`는 `nArray` 배열의 첫 번째 요소를 가리키는 포인터입니다.
- `length`는 배열의 크기를 계산합니다. `sizeof(nArray)`는 배열 전체 크기를 바이트 단위로 반환하고, `sizeof(int)`는 각 배열 요소의 크기를 바이트 단위로 반환하여 배열의 길이를 구합니다.

### 첫 번째 방법: 포인터를 사용하여 합계 계산
```cpp
sum = 0;
for (size_t i = 0; i < length; i++)
    sum += *(pArr + i);
std::cout << "sum = " << sum << std::endl;
```
- 이 방법은 포인터 연산을 사용하여 배열의 값을 접근하고 합계를 계산합니다.
- `*(pArr + i)`는 `pArr` 포인터가 가리키는 메모리 주소에서 `i`만큼 이동한 위치의 값을 의미합니다. 즉, 배열의 각 요소를 포인터를 통해 접근하고, `sum`에 더합니다.

### 두 번째 방법: 배열 인덱스를 사용하여 합계 계산
```cpp
sum = 0;
for (size_t i = 0; i < length; i++)
    sum += pArr[i];
std::cout << "sum = " << sum << std::endl;
```
- 이 방법은 배열의 인덱스를 사용하여 배열의 값을 접근합니다.
- `pArr[i]`는 배열의 `i`번째 요소를 의미하며, 인덱스를 통해 각 값을 `sum`에 더합니다.

### 세 번째 방법: 포인터 증가 연산을 사용하여 합계 계산
```cpp
sum = 0;
for (size_t i = 0; i < length; i++)
    sum += *(pArr++);
std::cout << "sum = " << sum << std::endl;
```
- 이 방법은 포인터의 증가 연산을 사용하여 배열의 값을 순차적으로 접근합니다.
- `*(pArr++)`는 `pArr` 포인터가 가리키는 현재 값을 먼저 참조하고, 그 후 포인터를 하나 증가시킵니다. 이렇게 해서 배열의 모든 값을 순차적으로 더합니다.

### 네 번째 방법: 포인터 증가 연산을 사용하여 합계를 하나씩 더한 후 출력
```cpp
sum += *(pArr++);
std::cout << "sum = " << sum << std::endl;
```
- 이 부분에서는 위의 세 번째 방법과 동일한 방식으로 포인터를 하나씩 증가시키며 값을 더하지만, 추가로 한 번 더 더한 후 그 결과를 출력합니다.

### 주석 처리된 부분 (배열 값을 출력하는 방법)
```cpp
/*for (size_t i = 0; i < length; i++)
    std::cout << *(pArr + i) << " ";
std::cout << std::endl;
for (size_t i = 0; i < length; i++)
    std::cout << pArr[i] << " ";
std::cout << std::endl;
for (size_t i = 0; i < length; i++)
    std::cout << *(pArr++) << " ";
std::cout << std::endl;*/
```
- 이 부분은 배열의 값을 출력하는 세 가지 방법을 보여줍니다.
  1. `*(pArr + i)`를 사용하여 포인터로 값을 출력합니다.
  2. `pArr[i]`를 사용하여 배열의 인덱스를 통해 값을 출력합니다.
  3. `*(pArr++)`를 사용하여 포인터를 증가시키면서 값을 출력합니다.
- 이 코드들은 주석 처리되어 있어 실제로 실행되지 않지만, 각각 다른 방식으로 배열의 값을 출력하는 방법을 보여줍니다.

### 요약:
이 프로그램은 배열과 포인터를 활용하여 배열의 합을 구하는 여러 가지 방법을 시연합니다. 첫 번째 방법은 포인터 연산을 사용하여 값에 접근하고, 두 번째는 배열 인덱스를 사용하며, 세 번째는 포인터 증가 연산을 이용하여 값을 더합니다. 또한 주석 처리된 코드에서는 배열의 값을 출력하는 다양한 방법을 제공합니다.