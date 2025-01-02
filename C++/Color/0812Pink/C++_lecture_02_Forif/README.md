## C++ 배열과 벡터를 활용한 반복문과 조건문 예제

### 코드 설명:

이 코드는 C++에서 배열과 벡터를 활용하여 반복문과 조건문을 사용하는 예제를 보여줍니다. 주로 배열과 벡터의 크기 확인, 반복문을 통한 값 출력, 조건문을 이용한 분기 등을 다룹니다.

#### 1. 주석 처리된 배열 예제:
```cpp
// int nArray[10] = { 1,2,3,4,5,6,7,8,9,10 }; // int x array[10] = 4x10 = 40
// int* arrayPtr = nArray;
```
- `nArray` 배열은 크기가 10인 정수 배열입니다. 주석 처리되어 있어서 실제로 실행되지 않습니다.
- `arrayPtr`은 `nArray` 배열을 가리키는 포인터입니다.

#### 2. 배열 크기 출력:
```cpp
// for (int i = 0; i < sizeof(nArray) / sizeof(int); i++)
// {
//     std::cout << arrayPtr[i] << "  "<<std::endl;
// }
// std::cout << "sizeof(nArray) ũ�� : " << sizeof(nArray) << std::endl;
// std::cout << "sizeof(int) ũ�� : " << sizeof(int) << std::endl;
// std::cout << "sizeof(nArray)/sizeof(int) ũ�� : " << sizeof(nArray)/sizeof(int) << std::endl;
```
- `sizeof(nArray)`는 `nArray` 배열의 전체 크기(바이트)를 반환하고, `sizeof(int)`는 `int` 타입의 크기를 반환합니다.
- 배열의 크기 계산은 `sizeof(nArray) / sizeof(int)`로, 배열의 요소 수를 계산하는 방법입니다. 주석 처리되어 있어서 실행되지 않지만, 배열의 크기를 확인할 수 있는 방법을 제공합니다.

#### 3. 조건문과 반복문을 활용한 출력:
```cpp
for (int i = 0; i < 10; i++)
{
    if (i % 2 == 0)
        std::cout << "i = " << i << std::endl;
    else if (i % 2 != 0)
        std::cout << "i_o = " << i << std::endl;
    else
        std::cout << "default" << std::endl;
}
```
- `for` 반복문을 사용하여 `i`가 0부터 9까지 반복합니다.
- `if` 조건문을 사용하여 `i`가 짝수일 때는 `"i = i"`를 출력하고, 홀수일 때는 `"i_o = i"`를 출력합니다.
- `else`는 사실 실행되지 않으며, `else if (i % 2 != 0)`와 중복된 조건문입니다.

#### 4. 벡터 크기 확인 후 값 출력:
```cpp
std::vector<int> v(10);
size_t sz = v.size();
for (size_t i = 0; i < v.size(); i++)
    std::cout << "v =  " << v[i] << std::endl;
```
- `std::vector<int> v(10)`은 크기가 10인 벡터를 선언합니다.
- `v.size()`를 사용하여 벡터의 크기를 확인하고, `for` 반복문을 사용하여 벡터의 모든 값을 출력합니다.
- 벡터는 기본값으로 0으로 초기화되기 때문에 출력되는 값은 모두 0입니다.

#### 5. 짝수 인덱스만 출력:
```cpp
for (size_t i = 0; i < v.size(); i++)
{
    if (i % 2 == 0)
    {
        std::cout << "i = " << i << std::endl;
    }
}
```
- 이 부분에서는 벡터의 인덱스가 짝수일 경우만 출력합니다. `i % 2 == 0` 조건이 참인 경우만 `"i = i"`를 출력합니다.

#### 6. 2차원 배열 형태로 출력:
```cpp
for (size_t row = 0; row < 10; row++)
{
    for (size_t col = 0; col < 10; col++)
    {
        std::cout << "[row,col] = " << row << " , " << col << std::endl;
    }
}
```
- 두 개의 중첩된 `for` 반복문을 사용하여 10x10 크기의 2차원 배열을 출력합니다.
- `row`와 `col`이 각각 0부터 9까지 반복하며, `[row,col]` 형태로 출력됩니다. 