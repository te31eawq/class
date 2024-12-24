
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
cap = cv2.VideoCapture(1)

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
import sys
import cv2
from PySide6.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QGraphicsView, QGraphicsScene, QGraphicsPixmapItem
from PySide6.QtGui import QPixmap, QImage, QPainter, QPen
from PySide6.QtCore import QTimer, Qt, QRectF, QPointF

class CameraApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Camera App with Zoom, Drag and Face Detection")
        
        # GUI 요소 설정
        self.initUI()
        
        # 얼굴 및 눈 검출을 위한 Haar Cascade 로드
        self.face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
        self.eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye_tree_eyeglasses.xml')
        
        # 카메라 비디오 캡처 객체
        self.cap = None
        self.zoom_factor = 1.0
        self.cap = cv2.VideoCapture(0)
        self.drag_start = None
        self.detect_faces = False
        self.detected_faces = []
        self.detected_eyes = []

        # 타이머 설정 (카메라 프레임 업데이트용)
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_frame)
    
    def closeEvent(self, event):
        if self.cap is not None:
            self.cap.release()
            self.cap = None
        self.scene.clear()  # 화면을 비움
        event.accept()  # 창을 닫을 수 있도록 설정
    
    def initUI(self):
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.resize(800, 600)
        
        # 카메라 스트림을 표시할 QGraphicsView 설정
        self.view = QGraphicsView()
        self.scene = QGraphicsScene()
        self.view.setScene(self.scene)
        self.view.setDragMode(QGraphicsView.ScrollHandDrag)  # 드래그 모드 활성화
        
        # Zoom In/Out 버튼
        self.zoom_in_btn = QPushButton("Zoom In")
        self.zoom_in_btn.clicked.connect(self.zoom_in)
        
        self.zoom_out_btn = QPushButton("Zoom Out")
        self.zoom_out_btn.clicked.connect(self.zoom_out)
        
        # Find Faces 버튼
        self.find_faces_btn = QPushButton("Find Faces")
        self.find_faces_btn.clicked.connect(self.toggle_face_detection)
        
        # Camera Start/Stop 버튼
        self.start_btn = QPushButton("Camera Start")
        self.start_btn.clicked.connect(self.start_camera)
        
        self.stop_btn = QPushButton("Camera Stop")
        self.stop_btn.clicked.connect(self.stop_camera)
        
        # 레이아웃 설정
        layout = QVBoxLayout()
        layout.addWidget(self.view)
        layout.addWidget(self.zoom_in_btn)
        layout.addWidget(self.zoom_out_btn)
        layout.addWidget(self.find_faces_btn)
        layout.addWidget(self.start_btn)
        layout.addWidget(self.stop_btn)
        
        self.central_widget.setLayout(layout)
    
    def start_camera(self):
        # 카메라 시작
        self.timer.start(30)
    
    def stop_camera(self):
        # 카메라 정지
        self.timer.stop()

    def zoom_in(self):
        # 줌 인 기능
        self.zoom_factor *= 1.1
        self.view.scale(1.1, 1.1)
    
    def zoom_out(self):
        # 줌 아웃 기능
        self.zoom_factor *= 0.9
        self.view.scale(0.9, 0.9)

    def toggle_face_detection(self):
        # 얼굴 검출 토글
        self.detect_faces = not self.detect_faces
        if self.detect_faces == True:
            self.find_faces_btn.setText("Stop Faces")
        else:
            self.find_faces_btn.setText("Find Faces")
    
    def update_frame(self):
        ret, frame = self.cap.read()
        if ret:
            if self.detect_faces:
                self.detected_faces, self.detected_eyes = self.process_frame(frame)
            else:
                self.detected_faces = []
                self.detected_eyes = []

            
            # OpenCV에서 얻은 BGR 이미지를 RGB로 변환
            rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            # 얼굴 검출 시 사각형 그리기
            if len(self.detected_faces)>0:
                for (x, y, w, h) in self.detected_faces:
                    cv2.rectangle(rgb_image, (x, y), (x + w, y + h), (255, 0, 0), 2)
                if len(self.detected_eyes)>0:
                    for (ex, ey, ew, eh) in self.detected_eyes:
                        cv2.rectangle(rgb_image, (ex+x, ey+y), (ex+x + ew, ey+y + eh), (0, 255, 0), 2)


            h, w, ch = rgb_image.shape
            bytes_per_line = ch * w
            qt_image = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format_RGB888)
            pixmap = QPixmap.fromImage(qt_image)
            
            # QGraphicsView에 표시
            self.scene.clear()
            pixmap_item = QGraphicsPixmapItem(pixmap)
            self.scene.addItem(pixmap_item)

        
            '''
            painter = QPainter(pixmap)
            pen = QPen(Qt.red, 3)
            painter.setPen(pen)
            for (x, y, w, h) in self.detected_faces:
                painter.drawRect(x, y, w, h)
            painter.end()
            '''

    def process_frame(self, frame):
        gray_img = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces=[]
        eyes=[]
        # 얼굴 검출
        faces = self.face_cascade.detectMultiScale(gray_img, 1.1, 4)

        for (x, y, w, h) in self.detected_faces:
            roi_gray = gray_img[y:y + h, x:x + w]
            eyes = self.eye_cascade.detectMultiScale(roi_gray)
        return faces, eyes

    def wheelEvent(self, event):
        # 마우스 휠 이벤트 처리로 Zoom In/Out
        if event.angleDelta().y() > 0:
            self.zoom_in()
        else:
            self.zoom_out()

    def mousePressEvent(self, event):
        # 마우스 드래그 시작점 설정
        if event.button() == Qt.LeftButton:
            self.drag_start = event.pos()
        super().mousePressEvent(event)
    
    def mouseMoveEvent(self, event):
        # 마우스 이동 시 이미지 드래그 처리
        if self.drag_start:
            delta = event.pos() - self.drag_start
            self.view.horizontalScrollBar().setValue(self.view.horizontalScrollBar().value() - delta.x())
            self.view.verticalScrollBar().setValue(self.view.verticalScrollBar().value() - delta.y())
            self.drag_start = event.pos()
        super().mouseMoveEvent(event)
    
    def mouseReleaseEvent(self, event):
        # 마우스 드래그 종료
        self.drag_start = None
        super().mouseReleaseEvent(event)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = CameraApp()
    window.show()
    sys.exit(app.exec())

# %%

import cv2
import numpy as np
import time

def hand_procs(frame):
    # BGR에서 HSV로 변환
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 피부색 범위를 설정 (HSV)
    lower_skin = np.array([0, 20, 70], dtype=np.uint8)
    upper_skin = np.array([20, 255, 255], dtype=np.uint8)

    # 피부색 범위에 해당하는 부분을 마스크로 추출
    mask = cv2.inRange(hsv, lower_skin, upper_skin)

    # 노이즈 제거를 위한 모폴로지 연산
    mask = cv2.erode(mask, np.ones((3, 3), np.uint8), iterations=2)
    mask = cv2.dilate(mask, np.ones((3, 3), np.uint8), iterations=2)

    # 가우시안 블러를 사용해 부드럽게 처리
    mask = cv2.GaussianBlur(mask, (5, 5), 100)

    # 윤곽선 검출
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # 가장 큰 윤곽선 찾기
    if contours:
        max_contour = max(contours, key=cv2.contourArea)

        # 손 주위에 사각형 그리기
        x, y, w, h = cv2.boundingRect(max_contour)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)

        # 손 윤곽선을 따라 그림
        cv2.drawContours(frame, [max_contour], -1, (0, 255, 0), 2)

# 카메라 캡처 설정
cap = cv2.VideoCapture(1)
mode_video = True

if mode_video:
    while True:
        start_time = time.time()

        ret, frame = cap.read()
        if ret:
            hand_procs(frame)

        finish_time = time.time()
        elapsed_time_ms = (finish_time - start_time) * 1000  # ms
        print(f'Elapsed time : {elapsed_time_ms:.3f} ms')

        cv2.imshow('Hand Detection', frame)

        # 'q' 키를 누르면 종료
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q') or key == ord('Q'):
            break

cap.release()
cv2.destroyAllWindows()

# %%
import numpy as np
import cv2
import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.image import img_to_array, load_img

# 데이터 생성 함수
def create_synthetic_data(num_images, save_path):
    if not os.path.exists(save_path):
        os.makedirs(save_path)

    categories = ['Rock', 'Paper', 'Scissors']
    for category in categories:
        category_path = os.path.join(save_path, category)
        if not os.path.exists(category_path):
            os.makedirs(category_path)

    for i in range(num_images):
        # Create a blank image
        image = np.zeros((150, 150, 3), dtype=np.uint8)

        # Draw a shape on the image
        color = np.random.randint(0, 255, size=3).tolist()
        thickness = np.random.randint(1, 10)
        shape = np.random.choice(['circle', 'rectangle'])
        category = np.random.choice(categories)
        
        if shape == 'circle':
            center = (np.random.randint(0, 150), np.random.randint(0, 150))
            radius = np.random.randint(10, 50)
            cv2.circle(image, center, radius, color, thickness)
        else:
            top_left = (np.random.randint(0, 75), np.random.randint(0, 75))
            bottom_right = (np.random.randint(75, 150), np.random.randint(75, 150))
            cv2.rectangle(image, top_left, bottom_right, color, thickness)
        
        # Save the image
        filename = os.path.join(save_path, category, f'image_{i}.jpg')
        cv2.imwrite(filename, image)

# 데이터 생성
create_synthetic_data(num_images=1000, save_path='synthetic_data')

# 데이터 전처리 및 생성
datagen = ImageDataGenerator(
    rescale=1./255,
    validation_split=0.2,
    rotation_range=40,
    width_shift_range=0.2,
    height_shift_range=0.2,
    shear_range=0.2,
    zoom_range=0.2,
    horizontal_flip=True,
    fill_mode='nearest'
)

train_generator = datagen.flow_from_directory(
    'synthetic_data',
    target_size=(150, 150),
    batch_size=32,
    class_mode='categorical',
    subset='training'
)

validation_generator = datagen.flow_from_directory(
    'synthetic_data',
    target_size=(150, 150),
    batch_size=32,
    class_mode='categorical',
    subset='validation'
)

# CNN 모델 설계
model = Sequential([
    Conv2D(32, (3, 3), activation='relu', input_shape=(150, 150, 3)),
    MaxPooling2D((2, 2)),
    Conv2D(64, (3, 3), activation='relu'),
    MaxPooling2D((2, 2)),
    Conv2D(128, (3, 3), activation='relu'),
    MaxPooling2D((2, 2)),
    Flatten(),
    Dense(512, activation='relu'),
    Dropout(0.5),
    Dense(3, activation='softmax')
])

model.compile(optimizer='adam',
              loss='categorical_crossentropy',
              metrics=['accuracy'])

# 모델 훈련
history = model.fit(
    train_generator,
    steps_per_epoch=train_generator.samples // train_generator.batch_size,
    epochs=10,
    validation_data=validation_generator,
    validation_steps=validation_generator.samples // validation_generator.batch_size
)

# 모델 저장
model.save('rock_paper_scissors_model.h5')

# 웹캠 실시간 예측 함수
def preprocess_image(image):
    image = cv2.resize(image, (150, 150))
    image = image / 255.0
    image = np.expand_dims(image, axis=0)
    return image

# 모델 로드
model = load_model('rock_paper_scissors_model.h5')

# 웹캠에서 실시간 예측
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if ret:
        processed_image = preprocess_image(frame)
        predictions = model.predict(processed_image)
        class_idx = np.argmax(predictions[0])
        class_labels = ['Rock', 'Paper', 'Scissors']
        gesture = class_labels[class_idx]

        cv2.putText(frame, gesture, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
        cv2.imshow('Rock Paper Scissors', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
# %%

#%%