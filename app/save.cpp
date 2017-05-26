#include "save.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


using namespace std;
Save::Save(QString filename){
    filename_ =filename;
}

void Save::saveBest(int score, int difficulty, QString playerName){
    QFile file(filename_);
    if (file.open(QFile::Append | QFile::Text)) {
        QTextStream myfile(&file);
        myfile <<score<<"|"<<difficulty<<"|"<<playerName<<endl;
    }
    else qDebug() << "Unable to open file";
}

QString Save::getBest(int difficulty){
    int max=0;//meilleur score temporaire
    QString final="";
    QStringList temp;
    QFile inputFile(filename_);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            temp=line.split("|");
            if (temp[1].toInt()==difficulty){
                if (temp[0].toInt()>max){
                    final=("Joueur :"+temp[2]+", score : "+temp[0]);
                    max=temp[0].toInt();
                }
            }
        }
        inputFile.close();
    }
    return final;
}
