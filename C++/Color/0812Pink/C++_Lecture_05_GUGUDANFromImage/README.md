## **OpenCV를 이용한 이미지 배열 색상 설정 및 그리드 생성 예제**

### 설명:
이 프로그램은 OpenCV 라이브러리를 사용하여 100x100 크기의 이미지를 생성하고, 지정된 위치에 흰색 픽셀을 그리드 형태로 설정하는 예제입니다. 이 코드는 `cv::Mat` 객체를 이용하여 이미지 데이터를 조작하고, `uchar*` 포인터를 사용해 배열을 다룹니다.

### 코드 설명:

#### 1. 이미지 객체 생성
```cpp
int rows = 100;
int cols = 100;

cv::Mat img = cv::Mat::zeros(rows, cols, CV_8UC3);
```
- `cv::Mat::zeros()`를 사용하여 100x100 크기의 3채널(컬러) 이미지 `img`를 생성합니다. `CV_8UC3`는 8비트 3채널(즉, RGB 컬러 이미지)을 의미합니다. 이로 인해 이미지는 모두 검정색(0)으로 초기화됩니다.

#### 2. 데이터 포인터 설정
```cpp
uchar* pData = img.data; // array start address
int width = cols;  // array width size
int height = rows; // array height size
```
- `img.data`는 이미지 데이터의 시작 주소를 가리키는 포인터입니다. 이를 통해 이미지 배열의 픽셀에 직접 접근할 수 있습니다.
- `width`와 `height`는 이미지의 가로와 세로 크기입니다.

#### 3. 그리드 위치 및 크기 설정
```cpp
int startrow = 45;
int finishrow = 55;
int startcol = 45;
int finishcol = 55;
int offset = 15;
```
- `startrow`, `finishrow`, `startcol`, `finishcol`은 그리드의 중심이 될 픽셀 범위입니다. 
- `offset`은 그리드의 확장을 조정하는 값으로, 이 값을 바탕으로 그리드가 확장됩니다.

#### 4. 이미지 배열 순회 및 픽셀 값 설정
```cpp
for (size_t row = 0; row < rows; row++)
{
    for (size_t col = 0; col < cols; col++)
    {
        size_t index = col + row * width;
        for (int a = 0; a < 3; a++)
        {
            for (int b = 0; b < 3; b++)
            {
                // 각 조건에 맞는 그리드 부분에 흰색(255) 값을 설정
                if (row >= startrow + offset * a && row <= finishrow + offset * a
                    && col >= startcol + offset * b && col <= finishcol + offset * b)
                {
                    if (a == 0 || b == 0)
                        pData[index] = 255;
                    if (a == 2 && b == 2)
                        pData[index] = 255;
                }
                // 반대 방향으로 확장하는 그리드 추가
                if (row >= startrow - offset * a && row <= finishrow - offset * a
                    && col >= startcol - offset * b && col <= finishcol - offset * b)
                {
                    if (a == 0 || b == 0)
                        pData[index] = 255;
                    if (a == 2 && b == 2)
                        pData[index] = 255;
                }
                // 대각선 부분 처리
                if (row >= startrow + offset * a && row <= finishrow + offset * a
                    && col >= startcol - offset * b && col <= finishcol - offset * b)
                    if (a == 2 && b == 2)
                        pData[index] = 255;
                if (row >= startrow - offset * a && row <= finishrow - offset * a
                    && col >= startcol + offset * b && col <= finishcol + offset * b)
                    if (a == 2 && b == 2)
                        pData[index] = 255;
            }
        }
    }
}
```
- 이중 `for` 반복문을 사용하여 이미지 배열을 한 픽셀씩 순회합니다. 각 픽셀에 대해 조건을 체크하여 특정 위치에 흰색(255)을 설정합니다.
  
  - 첫 번째 조건:
    - 그리드 영역의 위쪽, 아래쪽, 왼쪽, 오른쪽 경계를 설정하고, 그 경계에 해당하는 픽셀을 흰색으로 설정합니다.
  
  - 두 번째 조건:
    - 반대 방향으로 그리드를 확장하여 같은 방식으로 경계에 해당하는 픽셀을 흰색으로 설정합니다.
  
  - 세 번째 및 네 번째 조건:
    - 대각선 방향으로 그리드 영역을 확장하여, 해당 범위에 해당하는 픽셀을 흰색으로 설정합니다.

#### 5. 이미지 출력
- 이 코드에서는 OpenCV의 `imread`와 같은 출력 코드가 없기 때문에, 실제로 결과 이미지를 출력하거나 저장하는 코드가 포함되지 않았습니다. 일반적으로 OpenCV에서 이미지를 표시하려면 `cv::imshow()`나 `cv::imwrite()`를 사용하여 이미지를 창에 띄우거나 파일로 저장할 수 있습니다.

### 요약:
이 프로그램은 OpenCV를 사용하여 100x100 크기의 이미지를 생성하고, 그 안에 그리드 형태로 흰색 픽셀을 배치하는 예제입니다. 각 그리드는 `offset` 값을 기준으로 확장되어, 대각선 및 사각형 형태로 배치됩니다. 포인터 연산을 통해 이미지 데이터를 직접 수정하며, 이를 통해 그리드 모양을 만들고 있습니다.