#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bookmarkmodel.h"
#include "bookmarksengine.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    qmlRegisterType<BookmarksEngine>("rogov", 1, 0, "Bookmarksengine");
    qRegisterMetaType<std::vector<BookmarkModel::BookmarkView>>("std::vector<BookmarkModel::BookmarkView>");

    auto bEngine = new BookmarksEngine();

    QVariantList rulerData;
    for (int i = 0; i < 24; ++i) {
        rulerData << QString("%1%2").arg(i).arg("h");
    }

    auto bookmarks = new BookmarkModel();
    QObject::connect(bEngine, &BookmarksEngine::dataViewChanges, bookmarks, &BookmarkModel::updateRows);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("bookmarksModel", bookmarks);
    engine.rootContext()->setContextProperty("rulerData", rulerData);
    engine.rootContext()->setContextProperty(QStringLiteral("bookmarksEngine"), bEngine);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
