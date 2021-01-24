#ifndef BOOKMARKSENGINE_H
#define BOOKMARKSENGINE_H

#include <QObject>

#include "bookmarkmodel.h"

class BookmarksEngine : public QObject {
    Q_OBJECT

public:
    struct Bookmark {
        int beginTimeStamp = 0;
        int duration = 0;
        QString name = "";
        Bookmark(int _beginTimeStamp, int _duration, QString _name) :
            beginTimeStamp(_beginTimeStamp), duration(_duration), name(_name) { }
        bool operator<(const Bookmark &rhs) const {
            return beginTimeStamp < rhs.beginTimeStamp;
        }
    };

    BookmarksEngine(QObject *parent = nullptr);

    Q_INVOKABLE void generateData(int count, int hourWidht);
    Q_INVOKABLE void prepareData(int hourWidht);
    void setHourWidht(int hourWidht);

signals:
    void dataViewChanges(std::vector<BookmarkModel::BookmarkView>);

private:
    std::vector<Bookmark> _bookmarks;
    std::vector<BookmarkModel::BookmarkView> _bookmarksView;
    int _hourWidht = 0;
    bool _hourWidhtLess = false;
};

#endif // BOOKMARKSENGINE_H
