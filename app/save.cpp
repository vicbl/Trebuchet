#include "save.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


using namespace std;
Save::Save(QString filename){
   this->filename_ =filename;
}

void Save::saveBest(int score, int difficulty, QString playerName){
    QFile file(this->filename_);
    if (file.open(QFile::Append | QFile::Text)) {
        QTextStream myfile(&file);
        myfile <<score<<"|"<<difficulty<<"|"<<playerName<<endl;
    }
    else qDebug() << "Unable to open file";
}

QString Save::getBestName(int difficulty){
    int max=0;//meilleur score temporaire
    QString final="";
    QStringList temp;
    QFile inputFile(this->filename_);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            temp=line.split("|");
            if (temp[1].toInt()==difficulty){
                if (temp[0].toInt()>max){
                    final=temp[2];
                    max=temp[0].toInt();
                }
            }
        }
        inputFile.close();
    }
    return final;
}
int Save::getBestScore(int difficulty){
    int max=0;//meilleur score temporaire
    QStringList temp;
    QFile inputFile(this->filename_);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            temp=line.split("|");
            if (temp[1].toInt()==difficulty){
                if (temp[0].toInt()>max){

                    max=temp[0].toInt();
                }
            }
        }
        inputFile.close();
    }
    return max;
}
