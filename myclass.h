#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtGui>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class MyClass : public QLabel
{
    Q_OBJECT

    public:
      MyClass(QWidget *parent = 0);


    public slots:
      void replyFinished(QNetworkReply * reply) ;

    private:
      QLabel *label;
      QNetworkAccessManager *manager ;
} ;
#endif
