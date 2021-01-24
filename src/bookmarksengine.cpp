#include "bookmarksengine.h"
#include <QtConcurrent/QtConcurrent>

BookmarksEngine::BookmarksEngine(QObject *parent) : QObject(parent) {}

void BookmarksEngine::generateData(int count, int hourWidht) {
    _bookmarks.clear();
    for (int i = 0; i < count; i++) {
        _bookmarks.push_back({rand() % 24, 1 + rand() % 3, QString("Bookmark %1").arg(i)});
    }
    std::sort(_bookmarks.begin(), _bookmarks.end());
    prepareData(hourWidht);
}

void BookmarksEngine::prepareData(int hourWidht) {
    setHourWidht(hourWidht);
    QtConcurrent::run([this]() {
        _bookmarksView.clear();
        BookmarkModel::BookmarkView currentView(-101, 0, "", 0);
        for (const auto &item : _bookmarks) {
            if ((item.beginTimeStamp - currentView.beginTimeStamp) * _hourWidht >= 100) {
                if (currentView.beginTimeStamp >= 0) {
                    _bookmarksView.push_back(currentView);
                }
                currentView = BookmarkModel::BookmarkView(item.beginTimeStamp, item.duration, item.name, 1);
            } else {
                currentView.count++;
                int currentFinish = currentView.beginTimeStamp + currentView.duration;
                int itemFinish = item.beginTimeStamp + item.duration;
                if (currentFinish < itemFinish) {
                    currentView.duration += (itemFinish - currentFinish);
                }
            }
        }
        _bookmarksView.push_back(currentView);
        emit dataViewChanges(_bookmarksView);
    });
}

void BookmarksEngine::setHourWidht(int hourWidht) {
    _hourWidht = hourWidht;
}
