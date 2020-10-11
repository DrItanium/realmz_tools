#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <tuple>
#include "../Character.h"
#include "../Caste.h"
#include "../RaceData.h"

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
    realmz::Gender gender() noexcept;
    realmz::CasteKind caste() noexcept;
    realmz::RaceKind race() noexcept;
private:
    void promptCasteDataLocation() noexcept;
public:
    void closeEvent(QCloseEvent* event) override;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
