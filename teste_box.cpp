#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QThread>
#include <QProcess>
#include <QDebug>

// Classe para rodar o comando no terminal
class TerminalCommandRunner : public QThread {
    void run() override {
        // Comando a ser executado no terminal
        QProcess::execute("echo Terminal rodando...");
    }
};

// Função principal
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Cria a janela principal
    QWidget window;
    window.setWindowTitle("Checkbox Example");

    // Layout vertical
    QVBoxLayout *layout = new QVBoxLayout();

    // Cria as checkboxes
    QCheckBox *checkbox1 = new QCheckBox("Opção 1");
    QCheckBox *checkbox2 = new QCheckBox("Opção 2");
    QCheckBox *checkbox3 = new QCheckBox("Opção 3");

    // Adiciona as checkboxes ao layout
    layout->addWidget(checkbox1);
    layout->addWidget(checkbox2);
    layout->addWidget(checkbox3);

    // Define o layout na janela
    window.setLayout(layout);

    // Executa o comando no terminal em uma thread separada
    TerminalCommandRunner terminalRunner;
    terminalRunner.start();

    // Mostra a janela
    window.show();

    // Roda a aplicação
    return app.exec();
}
