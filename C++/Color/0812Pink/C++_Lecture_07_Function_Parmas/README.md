## **값과 참조, 포인터를 이용한 값 교환**

이 코드는 C++에서 다양한 방법을 사용하여 두 변수의 값을 교환하는 방법을 설명하고 있습니다. `Swap_ref`, `FnSwap`, 그리고 `swap_assign` 함수가 그 주인공입니다. 각 방식은 값을 직접적으로 수정하거나, 참조를 사용하거나, 포인터를 사용하여 값을 교환합니다. 코드의 흐름을 하나씩 살펴보겠습니다.

### 1. `Swap_ref` 함수
먼저 `Swap_ref` 함수는 두 인수를 참조로 받아들이고, 그들의 값을 교환합니다.

```cpp
void Swap_ref(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}
```

이 함수는 `int&` 타입의 참조를 사용하여, 매개변수 `a`와 `b`의 값을 바꿉니다. 이 방식은 메모리에서 직접적으로 참조를 통해 값을 수정하므로, 호출한 함수 외부에서도 값이 변경됩니다. 이 방식은 빠르고 직관적입니다.

### 2. `FnSwap` 함수
다음은 `FnSwap` 함수입니다. 이 함수는 포인터를 사용하여 값을 교환합니다.

```cpp
void FnSwap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
```

여기서 `*a`와 `*b`는 포인터 `a`와 `b`가 가리키는 값을 의미합니다. `*` 연산자를 사용하여 포인터가 가리키는 메모리 위치에 있는 값을 가져오거나 변경합니다. 이렇게 포인터를 사용하면 메모리 주소를 통해 값을 변경하는 방식이므로, `Swap_ref`와 유사하지만 포인터를 명시적으로 사용한다는 차이가 있습니다.

### 3. `swap_assign` 함수
세 번째는 `swap_assign` 함수입니다. 이 함수는 값 복사를 통해 두 변수의 값을 교환하려고 시도합니다.

```cpp
void swap_assign(int a, int b) 
{
    int t = a;
    a = b;
    b = t;
}
```

이 함수는 `a`와 `b`를 값으로 받습니다. 즉, `a`와 `b`는 함수 내에서 복사된 값이므로, 실제로 외부 변수들의 값은 변경되지 않습니다. 이 함수는 단순히 지역 변수 `a`와 `b`만 교환하고, 외부의 값에는 영향을 주지 않습니다. 이로 인해 `swap_assign` 함수는 값 변경의 효과가 없음을 알 수 있습니다.

### 4. `main` 함수에서의 실행

```cpp
int a = 10;
int b = 20;
std::cout << "초기 값" << std::endl;
std::cout << "a = " << a <<" " << "b = " << b << " " << std::endl;
Swap_ref(a, b);
std::cout << "swap_ref(a,b)" << std::endl;
std::cout << "a = " << a << " " << "b = " << b << " " << std::endl;
FnSwap(&a, &b);
std::cout << "Swap_pointer(a,b)" << std::endl;
std::cout << "a = " << a <<" "<< "b = " << b << " " << std::endl;
swap_assign(10 , 20);
swap_assign(a, b);
```

- **초기 값 출력**: 먼저 `a`와 `b`의 값을 출력합니다. `a = 10`, `b = 20`이 출력됩니다.
- **Swap_ref 호출**: `Swap_ref(a, b)`가 호출되면, `a`와 `b`의 값이 교환됩니다. `a`는 20, `b`는 10이 됩니다.
- **FnSwap 호출**: `FnSwap(&a, &b)`가 호출되면, 다시 값이 교환되어 `a`는 10, `b`는 20으로 돌아갑니다.
- **swap_assign 호출**: `swap_assign` 함수는 값 복사를 이용하므로, 외부 값에 아무런 영향을 미치지 않습니다. 호출은 되지만, 출력은 바뀌지 않습니다.

### 5. `Swap_assign` 결과

```cpp
int a_assign = 0;
a_assign = a;
a_assign = 10;
std::cout << "Swap_assign(a,b)" << std::endl;
```

위 코드에서 `a_assign`은 `a`의 값을 복사하지만, 값만 복사된 것이기 때문에 `a`나 `b`의 값은 바뀌지 않습니다.

### 결론

- **`Swap_ref`**는 참조를 사용하여, 함수 외부에서도 값이 바뀌게 합니다.
- **`FnSwap`**는 포인터를 사용하여, 메모리 주소를 통해 값을 교환합니다.
- **`swap_assign`**는 값 복사를 사용하며, 함수 외부의 값에는 영향을 주지 않습니다.

즉, C++에서 함수 내부에서 외부 변수 값을 교환할 수 있는 방법은 참조와 포인터를 사용해야 하며, 값 복사는 외부 변수에 영향을 미치지 않음을 알 수 있습니다.