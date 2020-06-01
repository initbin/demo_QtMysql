#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    //void on_pushButton_1_clicked();
    void pushButton_1_clicked();
    void pushButton_2_clicked();
    void pushButton_3_clicked();
    void pushButton_4_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
