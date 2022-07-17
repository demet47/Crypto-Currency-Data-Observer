#include "myclass.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QRegExp>
#include <QJsonArray>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>

MyClass::MyClass(QWidget *parent) : QLabel(parent)
{

     label = new QLabel("Connecting");
     QHBoxLayout *layout = new QHBoxLayout;

     layout->addWidget(label);
     setLayout(layout);

     manager = new QNetworkAccessManager(this) ;

     connect(manager, SIGNAL(finished(QNetworkReply *)),this, SLOT(replyFinished(QNetworkReply *)));

     // Initiate retrieval of  the data from the web page.
     // When completed, slot replyFinished will be called.
     manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/simple/price?ids=01coin&vs_currencies=usd,eur,gbp")));
}

void MyClass::replyFinished(QNetworkReply *reply)  {

     QString str = "https://api.coingecko.com/api/v3/simple/price?ids=";
     QString symbol = "01coin";
     QString pattern = "\"usd\":([^,]+),\"eur\":([^,]+),\"gbp\":([^\\}]+)";
     //pattern.append(symbol);
     //pattern.append("\"[^\\}]*");
     // read the data fetched from the web site
     QString data = (QString) reply->readAll();

     //"{\\Wid\\W:\\W(.+)\\".+"
     // use pattern matching to extract the rate
     QRegularExpression rx(pattern);
     QRegularExpressionMatch match = rx.match(data);
     bool hasmatch = match.hasMatch();
     if ( hasmatch ) {
       str.append(match.captured(1));
       str.append("&vs_currencies=usd,eur,gbp");
     }
     else {
       str = QString("Error") ;
     }

     QResource common("C:\Users\Demet\OneDrive\Masaüstü\Term_4_Lecture_Files\CMPE260\ödevler_ve_projeler\Racket\feedback.txt");

     QFile commonFile(common.absoluteFilePath());

     if (!commonFile.open(QIODevice::ReadOnly | QIODevice::Text))
     {
         qDebug() << "Unable to open file: " << commonFile.fileName() << " besause of error " << commonFile.errorString() << endl;
     }

     QTextStream in(&commonFile);

     QString content = in.readAll();
     // set the text of the label
     label->setText(str) ;
}
