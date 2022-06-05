#ifndef EVENT_H
#define EVENT_H

#include <QDir>
#include <iostream>
#include <fstream>

class Event
{
public:
    Event(QString type, QFileInfo *file1, QFileInfo *file2 = NULL);
    void displayEvent(std::ofstream &ofs);

private:
    QString event_type;
    QString event_date;
    QString file_type;
    QString file_location;
    QFileInfo *file;
    QFileInfo *file_renamed;

    friend std::ostream& operator<<(std::ostream &ost, Event &e);
};

#endif // EVENT_H
