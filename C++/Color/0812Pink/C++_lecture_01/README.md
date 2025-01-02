## **C++ 기본 데이터 타입, 포인터, 배열, 벡터, 구조체 사용 예제**

### 코드 설명

#### 1. 기본 라이브러리 포함
```cpp
#include <iostream>
#include <string> // 문자열 관련 기능 제공
#include <vector> // 동적 배열 관련 기능 제공
```
- `iostream`: 표준 입출력 스트림을 처리하는 라이브러리입니다. 주로 `std::cout`, `std::cin` 등을 사용하여 콘솔에 출력하거나 입력을 받습니다.
- `string`: 문자열을 다룰 수 있는 클래스를 제공합니다.
- `vector`: 크기가 동적으로 변경되는 배열을 제공하는 클래스입니다.

#### 2. 기본 데이터 타입
```cpp
int a = 0;
unsigned char aa = 0;
char cA = 'A';
double _aa = 0.1f;
float _a = 0.01f;
```
- `int a`: 정수형 변수 `a`를 선언하고, 0으로 초기화.
- `unsigned char aa`: 부호 없는 문자형 `aa`를 선언.
- `char cA`: 문자형 변수 `cA`를 선언하고 'A'로 초기화.
- `double _aa`: 실수형 변수 `_aa`를 선언하고 0.1로 초기화. (`double`은 64비트 실수형)
- `float _a`: 실수형 변수 `_a`를 선언하고 0.01로 초기화. (`float`은 32비트 실수형)

#### 3. 포인터 선언
```cpp
void* pAddr = nullptr; 
char* pCharAddr = nullptr;
double* pDdAddr = nullptr;
```
- `void* pAddr`: `void*`는 모든 타입의 포인터를 받을 수 있는 포인터입니다.
- `char* pCharAddr`: `char` 타입의 포인터.
- `double* pDdAddr`: `double` 타입의 포인터.

#### 4. 구조체 선언
```cpp
struct MyStruct {
    int a = 0;
    unsigned char aa = 0;
    char cA = 'A';
    double _aa = 0.1f;
    float _a = 0.01f;
};
```
- `MyStruct`: `int`, `unsigned char`, `char`, `double`, `float` 타입의 멤버 변수를 가진 구조체입니다. 이 구조체의 각 변수는 기본값으로 초기화됩니다.

#### 5. 배열과 벡터 선언
```cpp
int Arr[10] = { 0x00, };
std::vector<int> vArr(10);
std::vector<char> vArr2(10);
std::vector<MyStruct> vArr3(10);
```
- `Arr[10]`: 크기가 10인 정수형 배열을 선언하고 첫 번째 요소만 0x00으로 초기화.
- `vArr`: 크기가 10인 `int` 타입의 벡터를 선언.
- `vArr2`: 크기가 10인 `char` 타입의 벡터를 선언.
- `vArr3`: 크기가 10인 `MyStruct` 타입의 벡터를 선언.

#### 6. 배열과 벡터의 값 할당
```cpp
Arr[5] = 10;  // 배열의 5번째 요소에 10을 할당
vArr[5] = 10; // 벡터의 5번째 요소에 10을 할당
```
- `Arr[5] = 10`: `Arr` 배열의 5번째 요소에 10을 할당.
- `vArr[5] = 10`: `vArr` 벡터의 5번째 요소에 10을 할당.

#### 7. 포인터를 사용한 값 변경
```cpp
int* pArr = &Arr[0];
pArr++;  // 포인터를 한 칸 이동시킴
(*pArr) = 10; // pArr이 가리키는 위치에 10을 할당

int* pvArr = &vArr[0];
pvArr++;
*pvArr = 10;  // pvArr이 가리키는 벡터의 두 번째 요소에 10을 할당
```
- `pArr++`: `pArr` 포인터를 배열 `Arr`의 첫 번째 요소에서 두 번째 요소로 이동.
- `(*pArr) = 10`: 포인터 `pArr`가 가리키는 위치에 10을 저장.

#### 8. 구조체 벡터 값 수정
```cpp
vArr3[0].a = 20;
vArr3[1].aa = 'B';
```
- `vArr3[0].a = 20`: `vArr3` 벡터의 첫 번째 `MyStruct` 구조체의 `a` 멤버에 20을 할당.
- `vArr3[1].aa = 'B'`: `vArr3` 벡터의 두 번째 `MyStruct` 구조체의 `aa` 멤버에 문자 'B'를 할당.

#### 9. 출력 코드 (오류 있음)
```cpp
std::cout << ("%d", vArr3[0].a) << std::endl;
std::cout << ("%s", vArr3[1].aa) << std::endl;
std::cout << ("%s", vArr3[2].cA) << std::endl;
std::cout << ("%lf", vArr3[3]._aa) << std::endl;
```
- 이 코드에는 오류가 있습니다. `std::cout`은 `printf`와 같은 방식으로 사용될 수 없습니다. `std::cout`에서는 `<<` 연산자를 사용해야 합니다.
- 수정된 코드:
  ```cpp
  std::cout << vArr3[0].a << std::endl;
  std::cout << vArr3[1].aa << std::endl;
  std::cout << vArr3[2].cA << std::endl;
  std::cout << vArr3[3]._aa << std::endl;
  ```

### 결론

이 프로그램은 C++에서 여러 데이터 타입과 컨테이너(배열, 벡터, 구조체)를 사용하는 기본적인 예제입니다. 주로 포인터, 배열, 벡터, 그리고 구조체와 같은 다양한 자료 구조를 다루고 있습니다. 또한, C++에서 `std::cout`을 통해 값을 출력하는 방법을 보여줍니다.