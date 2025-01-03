## **C++에서 함수와 함수 포인터 사용 예시**

이 코드는 C++에서 함수를 정의하고 호출하는 방식, 함수 포인터를 사용하여 함수에 접근하는 방법을 보여줍니다. 함수 포인터는 함수의 주소를 저장하고, 이를 통해 함수를 동적으로 호출할 수 있게 해줍니다. 또한, 다양한 함수 서명과 매개변수 타입을 사용하는 방법을 설명합니다. 코드의 흐름을 차근차근 살펴보겠습니다.

### 1. **기본적인 함수 정의**

먼저 몇 가지 함수가 정의되어 있습니다.

```cpp
void Calc()
{
    std::cout << "Function::Calc()" << std::endl;
}

void Sum()
{
    std::cout << "Function::Sum()" << std::endl;
}
```

`Calc`와 `Sum`은 매개변수가 없고, 출력만 하는 단순한 함수들입니다. `Calc` 함수는 `Function::Calc()`를 출력하고, `Sum` 함수는 `Function::Sum()`을 출력합니다.

### 2. **매개변수가 있는 함수 정의**

다음은 매개변수와 반환값이 있는 함수들입니다.

```cpp
int Calc(int x)
{
    std::cout << "Function::Calc(int x)" << std::endl;
    int a = 10;
    int b = 23;
    int y = a * x + b;
    return y;
}
```

이 함수는 하나의 정수 `x`를 매개변수로 받아 `y = a * x + b`의 형태로 계산을 하고 결과를 반환합니다. `a`는 10, `b`는 23으로 고정되어 있습니다.

```cpp
int Calc(int& a, int b, int& x, int* y = nullptr)
{
    std::cout << "Function::Calc(int& a, int b, int& x, int* y=nullptr)" << std::endl;
    *y = a * x + b;
    return 1;
}
```

이 함수는 참조형 매개변수 `a`, `x`와 일반 매개변수 `b`를 사용하고, 선택적인 포인터 매개변수 `y`를 받아서 `*y = a * x + b`의 결과를 `y`가 가리키는 메모리 위치에 저장합니다.

### 3. **`main` 함수에서 함수 호출 및 포인터 사용**

```cpp
int main()
{
    Calc();
```

처음에 `Calc()`가 호출됩니다. 이 함수는 매개변수가 없고, `"Function::Calc()"`를 출력합니다.

#### 함수 포인터 사용

```cpp
    void (*pfnCalc)(void); // 함수 포인터 선언
    pfnCalc = Calc;        // 함수 포인터에 Calc 함수의 주소를 저장
    pfnCalc();             // 함수 포인터를 통해 Calc 함수 호출
```

이 부분에서 `pfnCalc`는 함수 포인터입니다. `pfnCalc`는 `void` 반환 타입과 매개변수가 없는 함수를 가리킵니다. `pfnCalc = Calc`로 `Calc` 함수의 주소를 함수 포인터에 할당하고, `pfnCalc()`를 호출하여 `Calc` 함수를 실행합니다.

```cpp
    pfnCalc = Sum;         // 함수 포인터에 Sum 함수의 주소를 저장
    pfnCalc();             // 함수 포인터를 통해 Sum 함수 호출
```

마찬가지로 `Sum` 함수의 주소를 함수 포인터에 할당하고 호출합니다. 결과적으로 `Function::Sum()`이 출력됩니다.

#### 함수 호출 및 값 전달

```cpp
    int y = 0;
    int x = 10;
    y = Calc(x);
    std::cout << "y = f(x) " << y << " = f(" << x << ")" << std::endl;
```

여기서는 `x` 값을 `Calc(x)` 함수에 전달하여 결과 `y`를 계산합니다. `y = a * x + b`에서 `a = 10`과 `b = 23`이므로 `y = 10 * 10 + 23 = 123`이 됩니다.

```cpp
    int a = 10;
    int b = 23;
    int ret = Calc(a, b, x, &y);
    std::cout << "y = f(x) " << y << " = f(" << x << ")" << std::endl;
```

이제 `Calc(a, b, x, &y)`를 호출하여 `a`, `b`, `x`를 이용해 `y` 값을 업데이트합니다. 이때 `y`는 포인터를 통해 값이 변경됩니다. `y = a * x + b` 계산이 수행되고, 결과는 `y = 10 * 10 + 23 = 123`이 됩니다.

#### 또 다른 함수 포인터 사용

```cpp
    int (*pfnCalcParams)(int&, int, int&, int*);
    pfnCalcParams = Calc;
    ret = pfnCalcParams(a, b, x, &y);
    std::cout << "y = f(x) " << y << " = f(" << x << ")" << std::endl;
```

이 부분에서는 함수 포인터 `pfnCalcParams`가 정의되고, `Calc` 함수의 주소를 할당합니다. 이후 `pfnCalcParams(a, b, x, &y)`를 호출하여 `a`, `b`, `x`, `y`의 값을 처리합니다. 여기서도 `y = a * x + b` 계산이 수행됩니다.

### 결론

이 코드는 C++에서 함수 정의 및 함수 포인터의 사용을 보여줍니다. 중요한 점은:

1. **기본적인 함수 호출**: 함수는 입력을 받아 계산을 수행하고 결과를 반환합니다.
2. **함수 포인터 사용**: 함수의 주소를 변수에 저장하고 이를 통해 동적으로 함수를 호출할 수 있습니다.
3. **매개변수 전달 방식**: 값 전달, 참조 전달, 포인터 전달 등 다양한 방식으로 매개변수를 처리할 수 있습니다.

이 코드는 함수 포인터를 통해 함수 호출을 동적으로 바꾸는 방법과, 함수의 매개변수를 다루는 다양한 방법들을 이해하는 데 도움을 줍니다.