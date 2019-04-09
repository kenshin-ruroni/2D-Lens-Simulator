#ifndef DIALOGEDITCIRCLE_H
#define DIALOGEDITCIRCLE_H

#include <QDialog>

class Circle;

namespace Ui {
class DialogEditCircle;
}

class DialogEditCircle : public QDialog
{
    Q_OBJECT

public:

    Circle *myCircle;
    explicit DialogEditCircle(QWidget *parent = nullptr);
    ~DialogEditCircle();

    bool IsPurelyReflexive();
    double GetRefractiveIndex();

   public slots :
    void RefractiveIndexHasChanged();
    void  RefractiveIndexHasChanged(int value);
    void CheckStateChanged(int);
private:
    Ui::DialogEditCircle *ui;
};

#endif // DIALOGEDITCIRCLE_H
