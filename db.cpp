#include "db.h"

Db::Db(){
    connectDb();
    //createLargeTable();
    //createMediumTable();
    //createSmallTable();
    setSign(QString::number(1), dbNameLarge, masterId);
    setDistinctSigns(dbNameLarge, masterId);
    setMinSign(dbName);
    setMaster(dbName);
}

void Db::connectDb(){
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/home/ok/jakob/QT4/DATABASES/trasci");
    if(!m_db.open()) std::cout<< "Error: connection with database fail"<<std::endl;
    else std::cout<< "Database: connection ok"<<std::endl;
}

void Db::createLargeTable(){
    QSqlQuery query;
    if(query.exec("create table if not exists "+dbNameLarge+" (`0` int)")) std::cout<<"table created"<<std::endl;
    else qDebug()<<"create table error: "<<query.lastError()<<" / "<<query.lastQuery();
    for(int x=0; x<Grid::range; x++){
        for(int y=0; y<Grid::range; y++){
            if(query.exec("alter table "+dbNameLarge+" add column `"+col[x]+""+QString::number(x)+""+QString::number(y)+"` int")) std::cout<<"columns created"<<std::endl;
            else qDebug()<<"create column error: "<<query.lastError()<<" / "<<query.lastQuery();
        }
    }
    if(query.exec("alter table "+dbNameLarge+" add column name int")) std::cout<<"name column added"<<std::endl;
    else qDebug()<<"add name column error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::createMediumTable(){
    QSqlQuery query;
    if(query.exec("create table if not exists "+dbNameMedium+" (`0` int)")) std::cout<<"table created"<<std::endl;
    else qDebug()<<"create table error: "<<query.lastError()<<" / "<<query.lastQuery();
    for(int x=0; x<Grid::range/2; x++){
        for(int y=0; y<Grid::range/2; y++){
            if(query.exec("alter table "+dbNameMedium+" add column `"+col[x]+""+QString::number(x)+""+QString::number(y)+"` int")) std::cout<<"columns created"<<std::endl;
            else qDebug()<<"create column error: "<<query.lastError()<<" / "<<query.lastQuery();
        }
    }
    if(query.exec("alter table "+dbNameMedium+" add column name int")) std::cout<<"name column added"<<std::endl;
    else qDebug()<<"add name column error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::createSmallTable(){
    QSqlQuery query;
    if(query.exec("create table if not exists "+dbNameSmall+" (`0` int)")) std::cout<<"table created"<<std::endl;
    else qDebug()<<"create table error: "<<query.lastError()<<" / "<<query.lastQuery();
    for(int x=0; x<Grid::range/3; x++){
        for(int y=0; y<Grid::range/3; y++){
            if(query.exec("alter table "+dbNameSmall+" add column `"+col[x]+""+QString::number(x)+""+QString::number(y)+"` int")) std::cout<<"columns created"<<std::endl;
            else qDebug()<<"create column error: "<<query.lastError()<<" / "<<query.lastQuery();
        }
    }
    if(query.exec("alter table "+dbNameSmall+" add column name int")) std::cout<<"name column added"<<std::endl;
    else qDebug()<<"add name column error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::setDistinctSigns(QString db, QString master){
    Sign::set.clear();
    QSqlQuery query;
    if(query.exec("select distinct name from "+db+" where master = "+master)) std::cout<<"distinct signs selected"<<std::endl;
    else qDebug()<<"select distinct signs error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Sign::set.push_back(query.value(0).toInt());
    }
}

void Db::setSign(QString name, QString db, QString master){
    Sign::sign.clear();
    Sign::initSigns();
    int index, c;
    index = 0;
    c = 1;
    QSqlQuery query;
    if(query.exec("select * from "+db+" where name = "+name+" and master = "+master)) qDebug()<<"sign selected "<<query.lastQuery();
    else qDebug()<<"select sign error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        for(int x=0; x<Grid::range/Grid::split; x++){
            for(int y=0; y<Grid::range/Grid::split; y++){
               Sign::sign[index][x][y] = query.value(c).toInt();
               c++;
            }
        }
    }
    index++;
}

void Db::addSign(QString db, QString master){
    int name;
    QSqlQuery query;
    if(query.exec("select max(name) from "+db)) std::cout<<"max sign name selected"<<std::endl;
    else qDebug()<<"select max sign error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        name = query.value(0).toInt()+1;
    }
    if(query.exec("insert into "+dbName+" (name, master) values ("+QString::number(name)+", "+master+")")) std::cout<<"new sign inserted"<<std::endl;
    else qDebug()<<"new sign error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::removeSign(QString name, QString db, QString master){
    QSqlQuery query;
    if(query.exec("delete from "+db+" where name = "+name+" and master = "+master)) qDebug()<<"sign deleted "<<query.lastQuery();
    else qDebug()<<"delete sign error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::saveSign(QString dbColumn, QString type, QString name, QString db, QString master){
    QSqlQuery query;
    if(query.exec("update "+db+" set "+dbColumn+" = "+type+" where name ="+name+" and master ="+master)) qDebug()<<"sign updated"<<query.lastQuery();
    else qDebug()<<"update error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::setMaster(QString db){
    Sign::master.clear();
    QSqlQuery query;
    if(query.exec("select distinct master from "+db)) qDebug()<<"master selected"<<query.lastQuery();
    else qDebug()<<"select master error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Sign::master.push_back(query.value(0).toInt());
    }
    /*for(int i=0; i<(int)Sign::master.size(); i++){
        std::cout<<"master set: "<<Sign::master[i]<<std::endl;
    }*/
}

void Db::addMaster(QString db){
    int l;
    QString max;
    QSqlQuery query;
    if(query.exec("select max(master) from "+db)) qDebug()<<"max master selected"<<query.lastQuery();
    else qDebug()<<"select max master error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        l = query.value(0).toInt();
        l++;
        max = QString::number(l);
    }
    if(query.exec("insert into "+db+" (master) values("+max+")")) qDebug()<<"master selected"<<query.lastQuery();
    else qDebug()<<"select master error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::setMinSign(QString db){
    QSqlQuery query;
    if(query.exec("select min(name) from "+db)) qDebug()<<"min sign selected"<<query.lastQuery();
    else qDebug()<<"select min sign error: "<<query.lastError()<<" / "<<query.lastQuery();
    query.next();
    minSign = QString::number(query.value(0).toInt());
}

