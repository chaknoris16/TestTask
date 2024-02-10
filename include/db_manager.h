#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>
#include <QCryptographicHash>

class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QObject *parent = nullptr);
    void createTable(const QString& dbName);
    void saveData(const QImage& image, int percentage);
    QVector<QPair<QImage, int>> loadImageDataFromDatabase();
    ~DBManager();
private:
    QSqlDatabase db;
    void closeDatabase();
};

#endif // DBMANAGER_H
