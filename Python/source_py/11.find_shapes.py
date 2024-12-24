import cv2
import numpy as np

def find_contours_and_features(image):
    # 이미지를 그레이스케일로 변환
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # 이진화(Threshold) 처리하여 도형의 외곽선 검출에 용이하게 함
    _, thresh = cv2.threshold(gray, 30, 255, cv2.THRESH_BINARY)

    # findContours를 사용하여 외곽선 검출
    contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # 도형의 특징 계산 및 출력
    for idx, contour in enumerate(contours):
        print(f"Contour {idx + 1}:")
        
        # 면적 (Area)
        area = cv2.contourArea(contour)
        print(f"  Area: {area}")
        
        # 둘레 (Perimeter)
        perimeter = cv2.arcLength(contour, True)
        print(f"  Perimeter: {perimeter}")
        
        # 모멘트 (Moments) 계산
        moments = cv2.moments(contour)
        print(f"  Moments: {moments}")
        
        # 도형의 중심 (Centroid) 계산
        if moments["m00"] != 0:  # m00이 0인 경우는 중심 계산 불가
            cx = int(moments["m10"] / moments["m00"])
            cy = int(moments["m01"] / moments["m00"])
            print(f"  Centroid: ({cx}, {cy})")
        else:
            print("  Centroid: Undefined (m00 is zero)")

        # 랜덤 색상 생성 (BGR 형식)
        color = tuple(np.random.randint(0, 255, size=3).tolist())

        # 도형 외곽선 그리기 (랜덤 색상 사용)
        cv2.drawContours(image, [contour], -1, color, 3)

        # 최소 외접 사각형 (회전된) 계산
        rect = cv2.minAreaRect(contour)
        box = cv2.boxPoints(rect)
        #box = np.int(box)

        # 사각형의 좌상단 좌표 찾기
        top_left = tuple(box[0])  # box[1]은 회전된 사각형의 좌상단 좌표

        # 도형의 면적과 둘레를 텍스트로 표시
        text = f"Area: {int(area)}, Perimeter: {int(perimeter)}"

        # 좌상단 좌표 근처에 텍스트 표시
        text_position = (int(top_left[0] - 20), int(top_left[1]))
        cv2.putText(image, text, text_position, cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1, cv2.LINE_AA)


    return image

if __name__ == "__main__":
    # 이미지 읽기 (색상 도형이 있는 이미지 파일)
    image_path = './Images/shapes.jpg'  # 이미지 경로 설정
    image = cv2.imread(image_path)

    # 외곽선 및 도형 특징 검출
    result_image = find_contours_and_features(image)

    # 결과 이미지 표시
    cv2.imshow("Detected Contours", result_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
