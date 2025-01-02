## **OpenCV를 이용한 이미지 불러오기 및 출력**

### 설명:
이 프로그램은 OpenCV 라이브러리를 사용하여 이미지를 불러오고, 화면에 표시하는 간단한 예제입니다. OpenCV의 이미지 처리 기능을 활용하여 이미지를 읽고 윈도우 창에 출력하는 방법을 다룹니다.

### 코드 설명:

#### 1. 기본 출력
```cpp
std::cout << "Hello World!\n";
int a = 10;
int b = 20;
int c = a + b;
```
- 프로그램의 시작 부분에서 "Hello World!"를 출력하고, 두 개의 정수(`a`, `b`)를 선언하여 더한 결과를 변수 `c`에 저장합니다. 이 부분은 주석을 위한 코드로, 실제 이미지 처리와는 관련이 없습니다.

#### 2. 이미지 생성 및 불러오기
```cpp
cv::Mat img = cv::Mat::zeros(100, 100, CV_8UC1);
cv::Mat colorImage = cv::imread("Images\\Audrey.jpg", cv::ImreadModes::IMREAD_UNCHANGED);
```
- `cv::Mat::zeros(100, 100, CV_8UC1)`:
  - `cv::Mat` 객체를 생성하여 100x100 크기의 흑백 이미지를 생성합니다. 모든 값은 0으로 초기화되며, `CV_8UC1`은 8비트 단일 채널(흑백 이미지)을 나타냅니다.
  
- `cv::imread("Images\\Audrey.jpg", cv::ImreadModes::IMREAD_UNCHANGED)`:
  - 지정된 경로(`Images\\Audrey.jpg`)에서 이미지를 읽어옵니다. `cv::ImreadModes::IMREAD_UNCHANGED`는 이미지의 원본을 그대로 읽어들이는 옵션으로, 컬러 이미지일 경우 RGB 형식 그대로 불러옵니다. 만약 다른 모드가 사용되면 그레이스케일로 읽거나 알파 채널을 제거할 수 있습니다.

#### 3. 윈도우 창 설정
```cpp
std::string nameWindow = "Show";
cv::namedWindow(nameWindow, cv::WindowFlags::WINDOW_NORMAL);
cv::resizeWindow(nameWindow, 600, 800);
```
- `cv::namedWindow(nameWindow, cv::WindowFlags::WINDOW_NORMAL)`:
  - `"Show"`라는 이름의 윈도우 창을 생성합니다. `cv::WindowFlags::WINDOW_NORMAL`은 창 크기를 자유롭게 조절할 수 있게 해줍니다.
  
- `cv::resizeWindow(nameWindow, 600, 800)`:
  - 생성된 윈도우 창의 크기를 600x800으로 설정합니다.

#### 4. 이미지 표시
```cpp
cv::imshow(nameWindow, colorImage);
```
- `cv::imshow(nameWindow, colorImage)`:
  - `"Show"`라는 이름의 윈도우 창에 `colorImage`를 표시합니다. `colorImage`는 이전에 불러온 이미지입니다.

#### 5. 키 입력 대기 및 종료
```cpp
cv::waitKey();
cv::destroyAllWindows();
```
- `cv::waitKey()`:
  - 키보드 입력을 기다립니다. 프로그램이 종료되기 전에 사용자가 키를 눌러야 창을 닫을 수 있습니다. 인자를 지정하지 않으면 무한 대기합니다.

- `cv::destroyAllWindows()`:
  - 모든 OpenCV 윈도우를 닫습니다. 이 함수는 이미지 출력이 끝난 후 호출되어 창을 닫고 프로그램을 종료합니다.

### 요약:
이 프로그램은 OpenCV를 사용하여 이미지를 읽고 출력하는 방법을 보여줍니다. `cv::Mat`을 사용해 이미지를 불러오고, `cv::namedWindow`와 `cv::imshow`로 윈도우 창을 만들어 이미지를 표시합니다. 사용자가 키를 눌러 프로그램을 종료할 때까지 이미지는 표시된 채로 대기합니다.