## **구구단 함수들 - 다양한 방식으로 구구단 출력**

이 프로그램은 구구단을 출력하는 여러 가지 방식의 함수를 포함하고 있습니다. 각각의 함수는 구구단을 출력하거나 구구단의 결과를 문자열로 반환하는 기능을 제공합니다. 각 함수의 작동 방식과 특징을 단계별로 설명하겠습니다.

### 1. **기본 구구단 출력 함수**

첫 번째 함수는 기본 구구단을 출력하는 함수입니다. 이 함수는 2단부터 9단까지의 구구단을 출력합니다.

```cpp
void GuGuDan() // 2~9단::기본 구구단
{
    std::cout << "Function::GuGuDan()" << std::endl;
    for (size_t i = 2; i < 10; i++)
    {
        for (size_t j = 1; j < 10; j++)
        {
            std::cout << i << "*"  << j  << "=" << i * j << "\t";
        }
    }
    std::cout << std::endl;
}
```

- **설명**:
  - `for (size_t i = 2; i < 10; i++)` 부분은 구구단의 단수를 2에서 9까지 반복합니다.
  - `for (size_t j = 1; j < 10; j++)` 부분은 각 단수마다 1부터 9까지 곱셈을 수행합니다.
  - `std::cout << i << "*" << j << "=" << i * j << "\t";`는 구구단 결과를 출력하는 부분입니다. 이 결과는 탭 문자로 구분되어 한 줄에 출력됩니다.
  - 구구단의 각 결과가 출력되며, `2*1=2`, `2*2=4`, ..., `9*9=81` 형식으로 표시됩니다.

### 2. **특정 구간 구구단 출력**

두 번째 함수는 구구단의 특정 구간을 출력하는 함수입니다. 사용자가 지정한 시작 단과 끝 단을 기준으로 구구단을 출력합니다.

```cpp
void GuGuDan(int startDan, int finishDan, int startStep, int finishStep)
{
    std::cout << "Function::GuGuDan(int startDan, int finishDan, int startStep, int finishStep)" << std::endl;
    
    for (size_t i = startDan; i < finishDan; i++)
    {
        for (size_t j = startStep; j <= finishStep; j++)
        {
            std::cout << i << "*" << j << "=" << i * j << "\t";
            if (j == finishStep) std::cout << std::endl;
        }
    }
}
```

- **설명**:
  - 이 함수는 `startDan`, `finishDan`, `startStep`, `finishStep`을 매개변수로 받습니다.
  - `startDan`과 `finishDan`은 구구단의 시작 단과 끝 단을 설정하며, `startStep`과 `finishStep`은 곱셈 범위를 설정합니다.
  - 예를 들어, `startDan = 2`, `finishDan = 5`, `startStep = 1`, `finishStep = 3`이면 2단부터 4단까지, 각 단에 대해 1부터 3까지의 곱셈 결과를 출력합니다.
  - 이 방법은 구간을 유동적으로 설정할 수 있어, 사용자가 원하는 구구단만 출력할 수 있습니다.

### 3. **구구단 결과를 문자열로 반환**

세 번째 함수는 구구단의 결과를 문자열로 반환하는 함수입니다. 이 함수는 출력 대신, 결과를 `std::string` 형식으로 반환합니다.

```cpp
std::string GuGuDans(int startDan, int finishDan, int startStep, int finishStep)
{
    std::cout << "Function::string GuGuDan(int startDan, int finishDan, int startStep, int finishStep)" << std::endl;
    std::string lines = "";
    
    for (size_t dan = 3; dan <= 5; dan++)
    {
        std::string line = "";
        for (size_t step = 2; step <= 6; step++)
        {
            int gugu = dan * step;
            line += std::to_string(dan);
            line += "*";
            line += std::to_string(step);
            line += "=";
            line += std::to_string(gugu);
            line += "\n";
        }
        lines += line;
    }
    return lines;
}
```

- **설명**:
  - `lines`라는 빈 문자열을 선언하여 구구단 결과를 하나씩 누적해 나갑니다.
  - `dan`은 3부터 5까지 반복하며, 각 `dan`에 대해 `step`은 2부터 6까지 반복하여 구구단 결과를 계산합니다.
  - 구구단 결과는 문자열로 만들어져 `line`에 저장되며, 각 결과는 새 줄(`\n`)로 구분됩니다.
  - 함수가 종료되면, 모든 구구단 결과가 포함된 문자열 `lines`를 반환합니다.
  - 이 방식은 출력 대신 구구단 결과를 다른 목적으로 활용할 수 있게 해줍니다.

### 4. **`main()` 함수**

```cpp
int main()
{
    GuGuDan(); // 기본 구구단 출력
    GuGuDan(2, 8, 1, 7); // 구간 구구단 출력
    std::string gg = GuGuDans(3, 5, 2, 6); // 구구단 문자열로 반환
    std::cout << gg << std::endl; // 구구단 결과 출력
    return 1;
}
```

- **설명**:
  - `GuGuDan()`을 호출하여 기본 구구단을 출력합니다.
  - `GuGuDan(2, 8, 1, 7)`을 호출하여 구간을 설정한 구구단을 출력합니다.
  - `GuGuDans(3, 5, 2, 6)`을 호출하여 구구단 결과를 문자열로 받아 출력합니다.

### 요약

이 프로그램은 구구단을 출력하는 세 가지 방법을 제공합니다:
1. 기본 구구단을 출력하는 함수.
2. 구간을 지정하여 구구단을 출력하는 함수.
3. 구구단 결과를 문자열로 반환하는 함수.

각각의 함수는 구구단을 다르게 처리할 수 있도록 하여, 사용자가 필요에 맞게 출력 형식과 범위를 조정할 수 있도록 합니다.