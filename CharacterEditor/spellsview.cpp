#include "spellsview.h"
#include "ui_spellsview.h"

SpellsView::SpellsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpellsView)
{
    ui->setupUi(this);
}

SpellsView::~SpellsView()
{
    delete ui;
}

void SpellsView::on_s0_toggled(bool checked)
{

}
