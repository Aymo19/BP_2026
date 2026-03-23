from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

app = QApplication([])

# Styl
app.setStyle("Windows")

# Main container
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.setWindowTitle("GR MENU")

        #self.setFixedSize(QSize(400, 300))
        self.setMinimumSize(QSize(600, 400))
        self.setMaximumSize(QSize(800, 600))

        # BTN
        topBtn = QPushButton("Top")
        bottomBtn = QPushButton("Bottom")

        

        # WINDOW
        centralWidget = QWidget()
        self.setCentralWidget(centralWidget)

        # BOX
        modulaciaBox = QGroupBox("Modulacia")
        kodovanieBox = QGroupBox("Kodovanie")
        simulaciaBox = QGroupBox("Simulacia")
        teoriaBox = QGroupBox("Teoria")
        
        modLay = QVBoxLayout()
        kodLay = QVBoxLayout()
        simLay = QVBoxLayout()
        teoLay = QVBoxLayout()
        
        # WINDOWS - LAYOUT
        gbox = QGridLayout()
        centralWidget.setLayout(gbox)

        # BOX - LAYOUT - ADD BTN
        modLay.addWidget(topBtn)
        modLay.addWidget(bottomBtn)

        # WINDOW - LAYOUT - ADD BOX
        modulaciaBox.setLayout(modLay)
        kodovanieBox.setLayout(kodLay)
        simulaciaBox.setLayout(simLay)
        teoriaBox.setLayout(teoLay)
       
        # ROZLOZENIE PRIDANE NA WINDOW
        gbox.addWidget(modulaciaBox, 1, 1)
        gbox.addWidget(kodovanieBox, 1, 2)
        gbox.addWidget(simulaciaBox, 2, 1)
        gbox.addWidget(teoriaBox, 2, 2)

        topBtn.clicked.connect(on_button_clicked)

# On click -> msg box
def on_button_clicked():
    alert = QMessageBox()
    alert.setText("Meow :3")
    alert.exec()

window = MainWindow()
window.show()

app.exec()
