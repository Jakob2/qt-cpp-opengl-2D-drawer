#include "db.h"

Db::Db(){
    connectDb();
    //createTable();
    setSign(QString::number(1));
    setDistinctSigns();
}

void Db::connectDb(){
    QSqlDatabase m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/home/ok/jakob/QT4/DATABASES/trasci");
    if(!m_db.open()) std::cout<< "Error: connection with database fail"<<std::endl;
    else std::cout<< "Database: connection ok"<<std::endl;
}

void Db::createTable(){
    QSqlQuery query;
    if(query.exec("create table if not exists "+dbName+" (`0` int)")) std::cout<<"table created"<<std::endl;
    else qDebug()<<"create table error: "<<query.lastError()<<" / "<<query.lastQuery();
    for(int x=0; x<Grid::range; x++){
        for(int y=0; y<Grid::range; y++){
            if(query.exec("alter table a1 add column `"+col[x]+""+QString::number(x)+""+QString::number(y)+"` int")) std::cout<<"columns created"<<std::endl;
            else qDebug()<<"create column error: "<<query.lastError()<<" / "<<query.lastQuery();
        }
    }
    if(query.exec("alter table a1 add column name int")) std::cout<<"name column added"<<std::endl;
    else qDebug()<<"add name column error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::setDistinctSigns(){
    Sign::set.clear();
    QSqlQuery query;
    if(query.exec("select distinct name from "+dbName)) std::cout<<"distinct signs selected"<<std::endl;
    else qDebug()<<"select distinct signs error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        Sign::set.push_back(query.value(0).toInt());
    }
}

void Db::setSign(QString name){
    Sign::sign.clear();
    Sign::initSigns();
    int index, c;
    index = 0;
    c = 1;
    QSqlQuery query;
    if(query.exec("select * from "+dbName+" where name = "+name)) qDebug()<<"sign selected "<<query.lastQuery();
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

void Db::addSign(){
    int name;
    QSqlQuery query;
    if(query.exec("select max(name) from "+dbName)) std::cout<<"max sign name selected"<<std::endl;
    else qDebug()<<"select max sign error: "<<query.lastError()<<" / "<<query.lastQuery();
    while(query.next()){
        name = query.value(0).toInt()+1;
    }
    if(query.exec("insert into "+dbName+" (name) values ("+QString::number(name)+")")) std::cout<<"new sign inserted"<<std::endl;
    else qDebug()<<"new sign error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::removeSign(QString name){
    QSqlQuery query;
    if(query.exec("delete from "+dbName+" where name = "+name)) qDebug()<<"sign deleted "<<query.lastQuery();
    else qDebug()<<"delete sign error: "<<query.lastError()<<" / "<<query.lastQuery();
}

void Db::saveSign(QString dbColumn, QString type, QString name){
    QSqlQuery query;
    if(query.exec("update "+dbName+" set "+dbColumn+" = "+type+" where name ="+name)) std::cout<<"sign updated"<<std::endl;
    else qDebug()<<"update error: "<<query.lastError()<<" / "<<query.lastQuery();
}

