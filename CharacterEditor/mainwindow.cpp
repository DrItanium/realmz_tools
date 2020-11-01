#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QInputDialog>
#include <QCloseEvent>
#include <QFileDialog>
#include <optional>
#include <memory>
#include "casteinfopanel.h"
#include "racestatsview.h"
#include "../CommonUIElements/ApplicationUtilities.h"
#include "../CommonUIElements/TacticalsModel.h"
#include "../CommonUIElements/PortraitModel.h"
#include "characterrepresentationselector.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pm(new PortraitModel()),
    tm(new TacticalsModel())
{
    ui->setupUi(this);
    ui->portraitView->setModel(pm.get());
    ui->portraitView->resizeRowsToContents();
    ui->portraitView->resizeColumnsToContents();
    ui->combatIconView->setModel(tm.get());
    ui->combatIconView->resizeRowsToContents();
    ui->combatIconView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    // @todo ask questions about if you've saved your game or not
    flashMessage("Thank you for supporting Fantasoft!");
   QApplication::exit(0);
}

void MainWindow::on_actionAbout_Realmz_Character_Editor_triggered()
{
    /// @todo make sure that we play the informational sound as well
    QMessageBox::about(this, "About Realmz Character Editor", "You're looking at it!");
}

bool
MainWindow::question(const QString &message) noexcept
{
    /// @todo play the sound effects associated with prompting for a question as done in realmz
    return QMessageBox::question(this, tr("Question"), message) == QMessageBox::Yes;
}

void
MainWindow::flashMessage(const QString &message) noexcept
{
    /// @todo play sounds as needed
    QMessageBox::information(this,"Information", message);
}

size_t
MainWindow::skillLevel() noexcept
{
    QStringList skillLevels;
    skillLevels << "1"
                << "3"
                << "5"
                << "7"
                << "9"
                << "11"
                << "13"
                << "15"
                << "17"
                << "20"
                << "25"
                << "30";
    return QInputDialog::getItem(this,
                                 tr("Select Starting Skill Level"),
                                 tr("Starting Skill Level"),
                                 skillLevels).toInt();
}

realmz::Gender
MainWindow::gender() noexcept
{
    QStringList genderOptions;
    genderOptions << "Male"
                  << "Female";
    auto selection = QInputDialog::getItem(this,
                                           tr("Gender"),
                                           tr("Select Gender"),
                                           genderOptions);
    if (selection == "Male") {
        return realmz::Gender::Male;
    } else {
        return realmz::Gender::Female;
    }
}

void
MainWindow::promptCasteDataLocation() noexcept {
    if (!realmz::casteDataLocationSet()) {
        std::filesystem::path thePath(getBinaryResourcesDir() / "Data Caste");
        if (!std::filesystem::exists(thePath)) {
            QMessageBox::information(this, tr("Note"), QString(thePath.string().c_str()) + tr(" does not exist"));
            auto qPath = QFileDialog::getOpenFileName(this, tr("Location of Caste Data"));
            thePath = qPath.toStdString();
        }
        realmz::setCasteDataLocation(thePath);
    }
}

void
MainWindow::promptRaceDataLocation() noexcept {
    if (!realmz::raceDataLocationSet()) {
        std::filesystem::path thePath(getBinaryResourcesDir() / "Data Race");
        if (!std::filesystem::exists(thePath)) {
            auto qPath = QFileDialog::getOpenFileName(this, tr("Location of Race Data"));
            thePath = qPath.toStdString();
        }
        realmz::setRaceDataLocation(thePath);
    }
}

std::optional<QString>
MainWindow::name() noexcept
{
    QString name;
    bool needToPrompt = true;
    while (needToPrompt) {
        name = QInputDialog::getText(this, tr("Name?"), tr("Name"));
        needToPrompt = false;
        if (name.isEmpty()) {
            if (question(tr("Would you like to cancel character generation?"))) {
                return std::nullopt;
            } else {
                needToPrompt = true;
                continue;
            }
        } else {
            if (name.length() > 16) {
                QMessageBox::information(this,
                                         tr("Whoa there!"),
                                         tr("Name too long!"));
                needToPrompt = true;
                continue;
            }
        }
    }
    return name;
}
void
MainWindow::on_actionGenerate_New_Character_triggered()
 {
   // there are several phases to this process, GHIDRA has been invaluable!
    /// @todo check and question about saving the current character
    /// @todo lookup the character data listing to see if a character with this name already exists
    auto nameResult = name();
    if (!nameResult) {
        return;
    }
    QString theName = *nameResult;
    realmz::Character theChar;
    theChar.setName(theName.toStdString());
    theChar.setSkillLevel(skillLevel());
    theChar.setGender(gender());
    theChar.setCaste(caste());
    theChar.setRace(race());
    // compute the defualt portrait index
    theChar.setPortraitIndex(portrait());
    theChar.setIconPictureIndex(iconPictureIndex());
    /// @todo implement caste selection, will need to read in the information from the resource fork data
    /// @todo implement race selection, will need to read in the information from the resource fork data
    /// @todo implement portrait selection, will need to read in the information from the resource fork data
    /// @todo implement character combat icon select, will need to read in the information from the resource fork data
}

realmz::CasteKind
MainWindow::caste() noexcept {
    /// @todo check the result of the exec call (accepted or rejected)
    promptCasteDataLocation();
    CasteInfoPanel cif(this);
    cif.exec();
    auto result = cif.getSelectedCasteKind();
    return result;
}

realmz::RaceKind
MainWindow::race() noexcept {
    /// @todo check the result of the exec call (accepted or rejected)
    promptRaceDataLocation();
    RaceStatsView rsv(this);
    rsv.exec();
    auto result = rsv.getSelectedRaceKind();
    return result;
}

void
MainWindow::closeEvent(QCloseEvent *event) {
    // this message comes from the original executable when you shutdown, doesn't show right in wine but I remember it
    // plus GHIDRA "mentions" it
    //flashMessage("Thank you for supporting Fantasoft!");
    event->accept();
}

int
MainWindow::portrait() noexcept
{
    CharacterRepresentationSelector csr(this);
    csr.setModel(pm.get());
    csr.exec();
    return csr.getSelectedRepresentation();
}

int
MainWindow::iconPictureIndex() noexcept
{
    CharacterRepresentationSelector csr(this);
    csr.setModel(tm.get());
    csr.exec();
    return csr.getSelectedRepresentation();
}

void MainWindow::on_portraitView_clicked(const QModelIndex &index)
{

}

void MainWindow::on_combatIconView_clicked(const QModelIndex &index)
{

}
