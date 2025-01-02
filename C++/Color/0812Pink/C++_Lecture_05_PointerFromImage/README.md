## **OpenCV를 이용한 사각형 및 교차선 그리기**

### 설명:
이 프로그램은 OpenCV 라이브러리를 사용하여 100x100 크기의 이미지를 생성하고, 그 안에 사각형과 교차선 형태로 흰색 픽셀을 배치하는 예제입니다. 이미지는 그레이스케일(`CV_8UC1`)로 생성되며, 포인터를 사용하여 이미지 배열을 조작합니다.

### 코드 설명:

#### 1. 이미지 객체 생성
```cpp
int rows = 100;
int cols = 100;

cv::Mat img = cv::Mat::zeros(rows, cols, CV_8UC1);
```
- `cv::Mat::zeros()`는 100x100 크기의 이미지를 생성하고, 모든 값을 0으로 초기화합니다. `CV_8UC1`은 8비트 단일 채널(흑백 이미지)을 의미합니다. 따라서, 생성된 이미지는 모두 검정색(0)으로 초기화됩니다.

#### 2. 데이터 포인터 설정
```cpp
uchar* pData = img.data; // array start address
int width = cols;  // array width size
int height = rows; // array height size
```
- `img.data`는 이미지 데이터의 시작 주소를 가리키는 포인터입니다. 이를 통해 이미지 배열의 각 픽셀에 직접 접근할 수 있습니다.
- `width`와 `height`는 각각 이미지의 가로, 세로 크기를 나타냅니다.

#### 3. 사각형 그리기
```cpp
size_t start_row = (rows / 4) - 1;
size_t start_col = (cols / 4) - 1;
size_t finish_row = (rows - (rows / 4))-1;
size_t finish_col = (cols - (cols / 4))-1;

for (size_t row = start_row; row <= finish_row; row++)
{
    for (size_t col = start_col; col <= finish_col; col++)
    {
        size_t index = col + row * width;
        if (row == start_row || row == finish_row || col == start_col || col == finish_col)
        {
            pData[index] = 255;
        }
    }
}
```
- `start_row`, `start_col`, `finish_row`, `finish_col`는 그리드의 경계 좌표입니다. 이미지의 중심에서 1/4 크기만큼 떨어진 위치에서 사각형이 그려집니다.
- 두 개의 `for` 루프를 사용하여 `start_row`와 `finish_row`, `start_col`과 `finish_col` 사이의 영역을 순회합니다. 해당 영역의 경계(`start_row`, `finish_row`, `start_col`, `finish_col`)에 위치한 픽셀을 흰색(`255`)으로 설정합니다.

#### 4. 교차선 그리기
```cpp
for (size_t row = 0; row < rows; row++)
{
    for (size_t col = 0; col < cols; col++)
    {
        size_t index = col + row * width;
        if (row == 50 || col == 50)
        {
            pData[index] = 255;
        }
    }
}
```
- 이 코드에서는 이미지의 가로와 세로 가운데에 교차선이 그려집니다.
- `row == 50` 또는 `col == 50`인 픽셀을 찾아서 흰색(`255`)으로 설정합니다. 이는 이미지의 중앙 가로선과 세로선에 해당하는 부분을 흰색으로 그리기 위한 방식입니다.

### 요약:
이 프로그램은 100x100 크기의 흑백 이미지를 생성하고, 이미지 상에 두 가지 형태의 그래픽을 그립니다:
1. **사각형**: 이미지의 중심에서 1/4 크기만큼 떨어진 위치에 흰색 경계선으로 사각형을 그립니다.
2. **교차선**: 이미지의 중앙 가로선과 세로선에 흰색 교차선을 그립니다.

이 과정은 `cv::Mat` 객체를 이용한 이미지 조작과 `uchar` 포인터를 통해 직접 배열을 조작하는 방법을 보여줍니다.