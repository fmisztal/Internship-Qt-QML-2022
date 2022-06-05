#include "event.h"

#include <QDir>
#include <QTime>
#include <iostream>
#include <fstream>

using namespace std;

Event::Event(QString type, QFileInfo *file1, QFileInfo *file2){
    file = file1;
    file_location = file1->filePath();
    file_renamed = file2;
    event_type = type;
    event_date = QDate::currentDate().toString() + " " + QTime::currentTime().toString();
    if(file->isFile())
        file_type = "File";
    else if(file->isDir())
        file_type = "Folder";
    else
        file_type = "Unrecognized";
}

void Event::displayEvent(ofstream &ofs){
    cout << *this;
    ofs << *this;
}

ostream& operator<<(ostream &ost, Event &e){
    ost << e.event_type.toStdString() << " - ";
    if(e.file_renamed)
        ost << e.file_type.toStdString() << " " << e.file_renamed->baseName().toStdString()<< " to "
            << e.file->baseName().toStdString() << " " << e.file->size() << " " << e.event_date.toStdString() << endl;
    else
        ost << e.file_type.toStdString() << " " << e.file->fileName().toStdString()
            << " " << e.file->size() << " " << e.event_date.toStdString() << endl;
    return ost;
};
