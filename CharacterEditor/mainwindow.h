#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <tuple>

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

    void on_actionAbout_Realmz_Character_Editor_triggered();

    void on_actionGenerate_New_Character_triggered();
private: // routine names taken from GHIDRA

    bool question(const QString& message) noexcept;
    void flashMessage(const QString& message) noexcept;
    size_t skillLevel() noexcept;
    enum class CharacterGender { Male, Female, };
    CharacterGender gender() noexcept;

public:
    void closeEvent(QCloseEvent* event) override;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
