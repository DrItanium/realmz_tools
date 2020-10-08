#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QInputDialog>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

MainWindow::CharacterGender
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
        return CharacterGender::Male;
    } else {
        return CharacterGender::Female;
    }
}

void
MainWindow::on_actionGenerate_New_Character_triggered()
 {
   // there are several phases to this process, GHIDRA has been invaluable!
    /// @todo check and question about saving the current character
    QString name;
    bool needToPrompt = true;
    while (needToPrompt) {
        name = QInputDialog::getText(this, tr("Name?"), tr("Name"));
        needToPrompt = false;
        if (name.isEmpty()) {
            if (question(tr("Would you like to cancel character generation?"))) {
                return;
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
    /// @todo lookup the character data listing to see if a character with this name already exists
    auto characterSkillLevel = skillLevel();
    auto characterGender = gender();
    /// @todo implement caste selection, will need to read in the information from the resource fork data
    /// @todo implement race selection, will need to read in the information from the resource fork data
    /// @todo implement portrait selection, will need to read in the information from the resource fork data
    /// @todo implement character combat icon select, will need to read in the information from the resource fork data
}

void
MainWindow::closeEvent(QCloseEvent *event) {
    flashMessage("Thank you for supporting Fantasoft!");
    event->accept();
}