#include "bookmarkmodel.h"

BookmarkModel::BookmarkModel(QObject *parent) : QAbstractListModel{parent} {}

int BookmarkModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return static_cast<int>(_bookmarks.size());
}

QVariant BookmarkModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant {};
    }
    switch (role) {
    case BeginTimeRole:
        return _bookmarks.at(index.row()).beginTimeStamp;
    case DurationRole:
        return _bookmarks.at(index.row()).duration;
    case Qt::DisplayRole:
        return _bookmarks.at(index.row()).count == 1 ? _bookmarks.at(index.row()).name :
               QString::number(_bookmarks.at(index.row()).count);
    case CountRole:
        return _bookmarks.at(index.row()).count;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BookmarkModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[BeginTimeRole] = "startTime";
    roles[DurationRole] = "duration";
    roles[CountRole] = "count";
    return roles;
}

void BookmarkModel::updateRows(std::vector<BookmarkModel::BookmarkView> items) {
    beginRemoveRows(QModelIndex(), 0, rowCount());
    _bookmarks.clear();
    endRemoveRows();
    beginInsertRows(QModelIndex(), 0, items.size());
    _bookmarks = items;
    endInsertRows();
}
