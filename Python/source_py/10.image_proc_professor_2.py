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
