#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <QTime>
#include <fstream>
#include "event.h"

using namespace std;

void delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(50);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int checkIfSameFile(ofstream &ofs, QFileInfo file1, QFileInfo file2){

    if(file1.completeSuffix() == file2.completeSuffix() && file1.QFileInfo::birthTime() == file2.QFileInfo::birthTime()){
        if(file1.fileName() == file2.fileName() && file1.size() != file2.size()){
            Event event = Event("Edited", &file1);
            event.displayEvent(ofs);
            return 1;
        }
        if(file1.fileName() != file2.fileName() && file1.size() == file2.size()){
            Event event = Event("Renamed", &file1, &file2);
            event.displayEvent(ofs);
            return 1;
        }
        if(file1.fileName() == file2.fileName() && file1.size() == file2.size())
            return 1;
    }
    return 0;
}

void checkIfFolderChanged(ofstream &ofs, QList<QFileInfo> list_current, QList<QFileInfo> list_previous){
    int check_if_exists = 0;
    auto list1 = list_current;
    auto list2 = list_previous;
    QString event_type = "Created";

    if(list_current.size() < list_previous.size()){
        list1 = list_previous;
        list2 = list_current;
        event_type = "Deleted";
    }

    for(auto &file1 : list1){
        for(auto &file2 : list2)
            check_if_exists += checkIfSameFile(ofs, file1, file2);

        if(check_if_exists == 0){
            Event event = Event(event_type, &file1);
            event.displayEvent(ofs);
        }
        else
            check_if_exists = 0;
    }
}


int main(int argc, char *argv[])
{
    if(argc < 2){
        cerr << "Not enough input arguments" << endl;
        return 1;
    }

    ofstream ofs;
    ofs.open("logs.txt",ios_base::app);
    if(!ofs.good())
    {
        cerr << "We couldn't open the logs" << endl;
        return 1;
    }

    QDir directory(argv[1]);
    auto fileInfoList = directory.entryInfoList();
    auto fileInfoList_previous = fileInfoList;

    QString exit = "no";
    while(exit == "no"){
        fileInfoList_previous = fileInfoList;
        QDir directory(argv[1]);
        fileInfoList = directory.entryInfoList();

        checkIfFolderChanged(ofs, fileInfoList, fileInfoList_previous);

        delay();
    }

    ofs.close();
    return 0;
}
