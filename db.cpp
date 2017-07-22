#include "db.h"

Db::Db(){
    connectDb();
    //createLargeTable();
    //createMediumTable();
    //createSmallTable();
    setSign(QString::number(1), dbNameLarge);
    setDistinctSigns(dbNameLarge);
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
    for(int x=0; x<30; x++){
        for(int y=0; y<30; y++){
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
    for(int x=0; x<20; x++){
        for(int y=0; y<20; y++){
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
    for(int x=0; x<10; x++){
        for(int y=0; y<10; y++){
            if(query.exec("alter table "+dbNameSmall+" add column `"+col[x]+""+QString::number(x)+""+QString::number(y)+"` int")) std::cout<<"columns created"<<std::endl;
            else qDebug()<<"create column error: "<<query.lastError()<<" / "<<query.lastQuery();
        }
    }
    if(query.exec("alter table "+dbNameSmall+" add column name int")) std::cout<<"name column added"<<std::endl;
    else qDebug()<<"add name column error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::setDistinctSigns(QString db){
    Sign::set.clear();
    QSqlQuery query;
    if(query.exec("select distinct name from "+db)) std::cout<<"distinct signs selected"<<std::endl;
    else qDebug()<<"select distinct signs error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Sign::set.push_back(query.value(0).toInt());
    }
}

void Db::setSign(QString name, QString db){
    Sign::sign.clear();
    Sign::initSigns();
    int index, c;
    index = 0;
    c = 1;
    QSqlQuery query;
    if(query.exec("select * from "+db+" where name = "+name)) qDebug()<<"sign selected "<<query.lastQuery();
    else qDebug()<<"select sign error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        for(int x=0; x<Grid::range; x++){
            for(int y=0; y<Grid::range; y++){
               Sign::sign[index][x][y] = query.value(c).toInt();
               c++;
            }
        }
    }
    index++;
}

void Db::addSign(QString db){
    int name;
    QSqlQuery query;
    if(query.exec("select max(name) from "+db)) std::cout<<"max sign name selected"<<std::endl;
    else qDebug()<<"select max sign error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        name = query.value(0).toInt()+1;
    }
    if(query.exec("insert into "+dbName+" (name) values ("+QString::number(name)+")")) std::cout<<"new sign inserted"<<std::endl;
    else qDebug()<<"new sign error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::removeSign(QString name, QString db){
    QSqlQuery query;
    if(query.exec("delete from "+db+" where name = "+name)) qDebug()<<"sign deleted "<<query.lastQuery();
    else qDebug()<<"delete sign error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::saveSign(QString dbColumn, QString type, QString name, QString db){
    QSqlQuery query;
    if(query.exec("update "+db+" set "+dbColumn+" = "+type+" where name ="+name)) std::cout<<"sign updated"<<std::endl;
    else qDebug()<<"update error: "<<query.lastError()<<" / "<<query.lastQuery();
}

