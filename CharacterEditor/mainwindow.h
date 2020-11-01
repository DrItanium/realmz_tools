#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <tuple>
#include <optional>
#include "../Character.h"
#include "../Caste.h"
#include "../RaceData.h"
#include "../CommonUIElements/PortraitModel.h"
#include "../CommonUIElements/TacticalsModel.h"
#include <memory>
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
    void on_portraitView_clicked(const QModelIndex &index);

    void on_combatIconView_clicked(const QModelIndex &index);

private: // routine names taken from GHIDRA

    bool question(const QString& message) noexcept;
    void flashMessage(const QString& message) noexcept;
    size_t skillLevel() noexcept;
    realmz::Gender gender() noexcept;
    realmz::CasteKind caste() noexcept;
    realmz::RaceKind race() noexcept;
    std::optional<QString> name() noexcept;
    int portrait() noexcept;
    int iconPictureIndex() noexcept;
private:
    void promptCasteDataLocation() noexcept;
    void promptRaceDataLocation() noexcept;
public:
    void closeEvent(QCloseEvent* event) override;
private:
    Ui::MainWindow *ui;
    std::unique_ptr<PortraitModel> pm;
    std::unique_ptr<TacticalsModel> tm;
};

#endif // MAINWINDOW_H
