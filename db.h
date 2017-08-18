#ifndef DB_H
#define DB_H

#include "global.h"
#include "grid.h"
#include "sign.h"

class Db
{
public:
    Db();

    void connectDb();
    void createLargeTable();
    void createMediumTable();
    void createSmallTable();
    void setDistinctSigns(QString db);
    void setSign(QString name, QString db);
    void addSign(QString db);
    void removeSign(QString name, QString db, QString master);
    void saveSign(QString dbColumn, QString type, QString name, QString db, QString master);
    void setMaster(QString db);
    void addMaster(QString db);

    std::vector<QString> col = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","x","z","aa","ab","ac","ad"};

    QString dbName = "a1";
    QString dbNameLarge = "a1";
    QString dbNameMedium = "a2";
    QString dbNameSmall = "a3";
    QString masterId = "0";

    void setMinSign(QString db);
    QString minSign;
};

#endif // DB_H
