#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "../Character.h"
#include "../CommonUIElements/PrimaryCharacterModel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionClose_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<PrimaryCharacterModel> pcm;
    std::shared_ptr<realmz::Character> currentCharacter = nullptr;
};

#endif // MAINWINDOW_H
