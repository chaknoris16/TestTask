#include "../include/db_manager.h"

DBManager::DBManager(QObject *parent)
    : QObject{parent}
{}

DBManager::~DBManager()
{
    closeDatabase();
}

void DBManager::closeDatabase()
{
    if (db.isValid() && db.isOpen()) {
        db.close();
    }
}

void DBManager::createTable(const QString& dbName)
{
    if (!db.isValid() || !db.isOpen()) {
        db = QSqlDatabase::addDatabase("QSQLITE", dbName + "_connection");
        db.setDatabaseName(dbName);

        if (!db.open()) {
            qDebug() << "Cannot open database";
        }
        QSqlQuery query(QSqlDatabase::database(dbName + "_connection"));
        query.exec("CREATE TABLE IF NOT EXISTS Images (id INTEGER PRIMARY KEY, image BLOB, hash TEXT, percentage INTEGER)");
    }

}

void DBManager::saveData(const QImage &image, int percentage)
{
    QSqlQuery query;

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    QByteArray hashData = QCryptographicHash::hash(imageData, QCryptographicHash::Md5).toHex();

    query.prepare("INSERT INTO Images (image, hash, percentage) VALUES (:image, :hash, :percentage)");
    query.bindValue(":image", imageData);
    query.bindValue(":hash", QString(hashData));
    query.bindValue(":percentage", percentage);

    if (!query.exec()) {
        qDebug() << "Error inserting data:" << query.lastError();
    }
}

QVector<QPair<QImage, int>> DBManager::loadImageDataFromDatabase()
{
    QVector<QPair<QImage, int>> imageModel;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open()) {
        qDebug() << "Cannot open database";
        return imageModel;
    }

    QSqlQuery query("SELECT image, hash, percentage FROM Images");

    while (query.next()) {
        QByteArray imageData = query.value("image").toByteArray();
        int percentage = query.value("percentage").toInt();

        QImage loadedImage;
        loadedImage.loadFromData(imageData);

        imageModel.append(QPair<QImage, int>(loadedImage, percentage));
    }
    return imageModel;
}



