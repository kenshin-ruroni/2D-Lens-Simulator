#include "dialogeditcircle.h"
#include "ui_dialogeditcircle.h"
#include "circle.h"
#include "source.h"

DialogEditCircle::DialogEditCircle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditCircle)
{
    ui->setupUi(this);
    ui->textEdit->setText( QString::number(GetRefractiveIndex()));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this,SLOT(RefractiveIndexHasChanged()));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int )),this,SLOT(RefractiveIndexHasChanged(int )));
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(CheckStateChanged(int)) );
}

DialogEditCircle::~DialogEditCircle()
{
    delete ui;
}


bool DialogEditCircle::IsPurelyReflexive()
{
    return ui->checkBox->isChecked() ;
}

double DialogEditCircle::GetRefractiveIndex()
{
    double v = (double) ui->horizontalSlider->value();
    v /= 1000;
    return v;
}

void  DialogEditCircle::RefractiveIndexHasChanged()
{

    ui->textEdit->setText( QString::number(GetRefractiveIndex()));
    if ( myCircle == NULL )
    {
        return;
    }
    if ( myCircle->theSource != NULL)
    {
        myCircle->theSource->UpdateRays();
    }
}

void  DialogEditCircle::RefractiveIndexHasChanged(int value)
{
    ui->horizontalSlider->setValue(value);
    ui->textEdit->setText( QString::number(GetRefractiveIndex()));
    if ( myCircle == NULL )
    {
        return;
    }
    if ( myCircle->theSource != NULL)
    {
        myCircle->theSource->UpdateRays();
    }
}

void DialogEditCircle::CheckStateChanged(int state)
{

    if ( myCircle->theSource != NULL)
    {
        myCircle->theSource->UpdateRays();
    }
}
