import sys
from PyQt5.QtWidgets import QApplication, QPushButton, QWidget, QVBoxLayout
# First Import your flowgraph
from test import test

class FM(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt5 Simple FM Example")

        # Instantiate FM Receiver App
        self.tb = test()
        self.setMinimumSize(700, 500)

        # State variable
        self.listening = False 

        # Layout
        layout = QVBoxLayout()

        # Button
        self.button = QPushButton("Start Listening")
        self.buttonZ = QPushButton("zmen hodnotu")
        self.button.clicked.connect(self.toggle_listening)  # connect click event
        self.buttonZ.clicked.connect(self.zhod)
        layout.addWidget(self.button)
        layout.addWidget(self.buttonZ)

        self.setLayout(layout)

    def toggle_listening(self):
        """Toggle listening state and update button text."""
        self.listening = not self.listening

        if self.listening:
            self.button.setText("Stop Listening")
            print("Listening started...")
            self.tb.start()
            self.tb.show()
        else:
            self.button.setText("Start Listening")
            print("Listening stopped.")
            self.tb.stop()
            self.tb.wait()

    def zhod(self):
        self.tb.set_HODNOTA(1)
        print("hodnota sa zmenila")
        print(self.tb.get_HODNOTA())


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = FM()
    window.show()
    sys.exit(app.exec_())
