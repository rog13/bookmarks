#ifndef BOOKMARKMODEL_H
#define BOOKMARKMODEL_H

#include <QAbstractListModel>
#include <vector>

class BookmarkModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum Roles {
        BeginTimeRole = Qt::UserRole + 1,
        DurationRole,
        CountRole
    };

    BookmarkModel(QObject *parent = nullptr);

    struct BookmarkView {
        int beginTimeStamp = 0;
        int duration = 0;
        QString name = "";
        int count = 0;

        BookmarkView(int _beginTimeStamp, int _duration, QString _name, int _count) :
            beginTimeStamp(_beginTimeStamp), duration(_duration), name(_name), count(_count) { }
    };

    int rowCount(const QModelIndex &parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //void appendBookmark(const Bookmark &bookmark);
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void updateRows(std::vector<BookmarkModel::BookmarkView> items);

private:
    std::vector<BookmarkView> _bookmarks;
};

#endif // BOOKMARKMODEL_H
