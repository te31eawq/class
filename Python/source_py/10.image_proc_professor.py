#%%
import cv2
print(cv2.__version__)

import time

def face_procs(face_image, face_cascade, eye_cascade):
    gray_img = cv2.cvtColor(face_image, cv2.COLOR_BGR2GRAY)

    # 얼굴 검출
    faces = face_cascade.detectMultiScale(gray_img, 1.1, 4)

    # 얼굴 주위에 사각형 그리기
    for (x, y, w, h) in faces:
        cv2.rectangle(face_image, (x, y), (x + w, y + h), (255, 0, 0), 2)

        # 얼굴 영역 추출 (ROI: Region Of Interest)
        roi_gray = gray_img[y:y + h, x:x + w]
        roi_color = face_image[y:y + h, x:x + w]

        # 눈 검출
        eyes = eye_cascade.detectMultiScale(roi_gray)
        for (ex, ey, ew, eh) in eyes:
            cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)



#face_cascade = cv2.CascadeClassifier('./Images/haarcascade_frontalface_default.xml')
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye_tree_eyeglasses.xml')
cap = cv2.VideoCapture(0)

print(face_cascade.empty())  # 파일이 비어있는지 확인
mode_image = False
mode_video = True




if mode_video:
    while True:    
        start_time = time.time()

        ret, frame = cap.read()
        if ret:
            face_procs(frame, face_cascade, eye_cascade)

        finish_time = time.time()
        elapsed_time_ms = (finish_time - start_time)*1000#ms
        print(f'Elapsed time : {elapsed_time_ms:.3f} ms')


        cv2.imshow('Face Detection', frame)          
        # 키 입력 대기 (1ms) -> 'q' 또는 'Q'를 누르면 종료
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') or key == ord('Q'):
            break

if mode_image:
    
    img_path = './Images/Audrey.jpg'
    img = cv2.imread(img_path)
    '''
    rows = img.shape[0]
    cols = img.shape[1]
    channels = img.shape[2]
    '''
    rows,cols,channels = img.shape
    factor = cols/rows

    n_cols = 400
    n_rows = int(n_cols*factor)
    img_resized = cv2.resize(img,(n_rows,n_cols))

    face_image = img_resized
    face_procs(face_image, face_cascade, eye_cascade)
    cv2.imshow('show_img', face_image)
    cv2.waitKey(0)

cv2.destroyAllWindows()
# %%
