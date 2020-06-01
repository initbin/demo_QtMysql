#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<< QSqlDatabase::drivers();
    setWindowTitle("qt_sql");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("exp");

    if(!db.open())
    {
        QMessageBox::warning(this,"警告","打开数据库失败");
    }
    else
    {
        ui->textEdit->setText("数据库打开成功");
    }


    connect(ui->pushButton_1,&QPushButton::clicked,this,pushButton_1_clicked);
    connect(ui->pushButton_2,&QPushButton::clicked,this,pushButton_2_clicked);
    connect(ui->pushButton_3,&QPushButton::clicked,this,pushButton_3_clicked);
    connect(ui->pushButton_4,&QPushButton::clicked,this,pushButton_4_clicked);
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::on_pushButton_1_clicked()
//{
//    QMessageBox::warning(this,"警告","test");
//}

void Widget::pushButton_1_clicked()
{
    //QMessageBox::warning(this,"警告","test");
    QString namestr = ui->lineEdit_1->text();
    int number = ui->lineEdit_2->text().toInt();
    double score = ui->lineEdit_3->text().toDouble();

    if(namestr==nullptr || number==0 || ui->lineEdit_3==nullptr)
    {
        ui->textEdit->setText("请输入完整的数据信息");
    }
    else
    {
        QString str = QString("insert into students(name,score,number)values('%1','%2','%3')").arg(namestr).arg(score).arg(number);
        QSqlQuery query;
        bool res = query.exec(str);
        if(res)
        {
            ui->lineEdit_1->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->textEdit->setText("插入成功");
        }
        else
        {
            QMessageBox::warning(this,"警告","插入失败");
        }

    }
}

void Widget::pushButton_2_clicked()
{
    QString name = ui->lineEdit_1->text();
    if(name == nullptr)
    {
        ui->textEdit->setText("请输入名字进行删除");
    }
    else
    {
        QSqlQuery query;
        QString str = QString("select * from students where name = '%1'").arg(name);
        query.exec(str);
        QString deletename;
        while(query.next())  //.next()获得数据库检索后的数据的一行
        {
            deletename = query.value(0).toString();
        }
        if(deletename==nullptr)
        {
            QString str1 = QString("没有 %1 这个人的信息，删除失败").arg(name);
            ui->textEdit->setText(str1);
        }
        else
        {
            QString del = QString("delete from students where name = '%1'").arg(name);
            query.exec(del);
            ui->textEdit->setText("删除成功");
        }
        ui->lineEdit_1->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }


}
void Widget::pushButton_3_clicked()
{
    QString name = ui->lineEdit_1->text();
    if(name == nullptr)
    {
        ui->textEdit->setText("请输入名字进行删除");
    }
    else
    {
        QSqlQuery query;
        QString str = QString("select * from students where name = '%1'").arg(name);
        query.exec(str);
        QString namestr;
        int number;
        double score;
        while(query.next())  //.next()获得数据库检索后的数据的一行
        {
            name = query.value(0).toString();
            number = query.value(1).toInt();
            score = query.value(2).toDouble();
        }
        if(name==nullptr)
        {
            QString str1 = QString("没有 %1 这个人的信息，查询失败").arg(name);
            ui->textEdit->setText(str1);
        }
        else
        {
            QString show = QString("姓名：%1  学号：%2  分数：%3").arg(name).arg(number).arg(score);
            ui->textEdit->setText(show);
        }
        ui->lineEdit_1->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();

    }
}
void Widget::pushButton_4_clicked()
{


    QSqlQuery query;
    QString str = QString("select * from students");
    query.exec(str);
    QString namestr[100];
    int number[100];
    double score[100];
    int i=0;
    while(query.next())  //.next()获得数据库检索后的数据的一行
    {
        namestr[i] = query.value(0).toString();
        number[i] = query.value(1).toInt();
        score[i] = query.value(2).toDouble();
        i++;
    }
    if(namestr[0]==nullptr)
    {
        QString str1 = QString("表为空");
        ui->textEdit->setText(str1);
    }
    else
    {
        ui->textEdit->clear();
        for(int j=0;j<i;j++)
        {
            QString show = QString("姓名：%1  学号：%2  分数：%3").arg(namestr[j]).arg(number[j]).arg(score[j]);
            ui->textEdit->append(show);
        }

    }

}
