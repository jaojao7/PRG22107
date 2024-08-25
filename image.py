from PySide2.QtWidgets import QApplication, QLabel, QMainWindow
from PySide2.QtGui import QPixmap
import sys

class ImageWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        # Configura a janela
        self.setWindowTitle('PARABÉNS')
        self.setGeometry(100, 100, 800, 600)  # Definindo o tamanho da janela
        
        # Cria um widget de QLabel
        label = QLabel(self)
        pixmap = QPixmap('WIN.jpg')  # Carrega a imagem
        label.setPixmap(pixmap)  # Define a imagem no QLabel
        
        # Ajusta o tamanho do QLabel para a imagem
        label.resize(pixmap.width(), pixmap.height())
        
        # Centraliza o QLabel na janela
        self.setCentralWidget(label)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = ImageWindow()
    window.show()
    sys.exit(app.exec_())
