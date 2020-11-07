#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include "../CommonUIElements/ApplicationUtilities.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pcm(new PrimaryCharacterModel(nullptr, this))
{
    ui->setupUi(this);
    ui->tableView->setModel(pcm.get());
    realmz::setCasteDataLocation(getBinaryResourcesDir() / "Data Caste");
    realmz::setRaceDataLocation(getBinaryResourcesDir() / "Data Race");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
   QApplication::quit();
}

void MainWindow::on_actionClose_triggered()
{
    currentCharacter.reset();
    pcm->setTargetCharacter(currentCharacter);
}

void MainWindow::on_actionOpen_triggered()
{
    if (auto path = QFileDialog::getOpenFileName(this); !path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        } else {
            constexpr auto bufferSizeInShorts = std::tuple_size_v<realmz::CharacterDataBuffer>;
            constexpr auto bufferSizeInBytes = bufferSizeInShorts * 2;
            realmz::CharacterDataBuffer buf;
            auto amount = file.read((char *) buf.data(), bufferSizeInBytes);
            if (amount != bufferSizeInBytes) {
                return;
            }
            auto swap = [](int16_t value) noexcept {
                auto lower = value & 0xFF;
                auto upper = (value >> 8) & 0xFF;
                return ((lower << 8) | upper);
            };
            // swap all of the shorts to be correctly described
            for (int i = 0; i < bufferSizeInShorts; ++i) {
                buf[i] = swap(buf[i]);
            }
            currentCharacter = std::make_shared<realmz::Character>(buf);
            pcm->setTargetCharacter(currentCharacter);
        }
    }
}
