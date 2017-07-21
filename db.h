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
    void createTable();
    void setDistinctSigns();
    void setSign(QString name);
    void addSign();
    void removeSign(QString name);
    void saveSign(QString dbColumn, QString type, QString name);

    std::vector<QString> col = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","x","z","aa","ab","ac","ad"};
private:
    QString dbName = "a1";

};

#endif // DB_H
