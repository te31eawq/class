import sys
import cv2
import numpy as np
from PySide6.QtWidgets import (QApplication, QMainWindow, QLabel, QPushButton, 
                               QVBoxLayout, QWidget, QSlider)
from PySide6.QtCore import QTimer, Qt
from PySide6.QtGui import QImage, QPixmap

class CameraInspectionApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Camera Module Inspection")
        self.setGeometry(100, 100, 800, 600)

        # Create central widget
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        # Create layout
        self.layout = QVBoxLayout(self.central_widget)

        # Camera feed label
        self.camera_label = QLabel(self)
        self.layout.addWidget(self.camera_label)

        # Add brightness control slider
        self.brightness_slider = QSlider(Qt.Horizontal)
        self.brightness_slider.setMinimum(0)
        self.brightness_slider.setMaximum(255)
        self.brightness_slider.setValue(128)  # default brightness value
        self.brightness_slider.setTickPosition(QSlider.TicksBelow)
        self.brightness_slider.setTickInterval(10)
        self.brightness_slider.valueChanged.connect(self.change_brightness)
        self.layout.addWidget(self.brightness_slider)

        # Add a button to start diagnostics
        self.diagnostics_button = QPushButton("Run Diagnostics")
        self.diagnostics_button.clicked.connect(self.run_diagnostics)
        self.layout.addWidget(self.diagnostics_button)

        # Initialize camera
        self.cap = cv2.VideoCapture(0)

        # Set a timer to display the camera feed
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.display_camera_feed)
        self.timer.start(20)  # 50 FPS

    def display_camera_feed(self):
        ret, frame = self.cap.read()
        if ret:
            # Convert frame from BGR (OpenCV) to RGB (for PySide6)
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            # Adjust brightness from slider value
            brightness = self.brightness_slider.value()
            frame = cv2.convertScaleAbs(frame, alpha=1, beta=brightness - 128)

            # Convert frame to QImage
            height, width, channel = frame.shape
            bytes_per_line = 3 * width
            q_img = QImage(frame.data, width, height, bytes_per_line, QImage.Format_RGB888)

            # Display the QImage on the label
            self.camera_label.setPixmap(QPixmap.fromImage(q_img))

    def change_brightness(self):
        # Simply update the brightness when the slider is changed
        pass

    def run_diagnostics(self):
        # Example: Simple diagnostics logic
        ret, frame = self.cap.read()
        if ret:
            # Convert frame to grayscale for basic diagnostics
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            blur = cv2.GaussianBlur(gray, (5, 5), 0)
            edges = cv2.Canny(blur, 50, 150)

            # Show diagnostics result (edges detected) in a new window
            cv2.imshow("Diagnostics - Edge Detection", edges)

    def closeEvent(self, event):
        self.cap.release()
        cv2.destroyAllWindows()

# Main execution
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = CameraInspectionApp()
    window.show()
    sys.exit(app.exec())
