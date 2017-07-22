#include "glwidget.h"

GlWidget::GlWidget(QWidget * parent) : QGLWidget(parent){
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
}

void GlWidget::initializeGL(){
    glClearColor(0.5,0.5,0.5,1);
}

void GlWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    arrow();
    setTopMax();
    topMenu();
    overtopMenu();
    drawSign();
    horizontal();
    vertical();
    botMenu();
    topMenuText();
    botMenuText();
    overtopMenuText();
}

void GlWidget::resizeGL(int w, int h){
    WIDTH = GlWidget::width();
    HEIGHT = GlWidget::height();
    glViewport(0,0,WIDTH,HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(Grid::low-0.1,Grid::high+0.1,Grid::low-0.1,Grid::high+0.3);
    gluOrtho2D(Grid::low+Grid::left,Grid::high+Grid::right,Grid::low+Grid::bottom,Grid::high+Grid::top);
}

void GlWidget::mousePressEvent(QMouseEvent *event){
    mouseX = event->pos().x();
    mouseY = event->pos().y();
    //std::cout<<"mouseX: "<<mouseX<<" / mouseY: "<<mouseY<<std::endl;
    coords();
    createDbColumnString();
    mouseHandler(event);
}

void GlWidget::coords(){
    gridX = floor((10*((Grid::high+(-Grid::left+Grid::right))*mouseX)/WIDTH))-1;
    gridY = Grid::range - floor((10*((Grid::high+(-Grid::bottom+Grid::top))*mouseY)/HEIGHT))+5;
}

void GlWidget::mouseMoveEvent(QMouseEvent *event){
    mouseX = event->pos().x();
    mouseY = event->pos().y();
    coords();
    createDbColumnString();
    hover();
    if(event->buttons() == Qt::LeftButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1){
            Sign::sign[0][floor(gridX/Grid::split)][floor(gridY/Grid::split)] = 1;
            saveSign(dbColumn,QString::number(1),currentSign, dbName);
            //setSign(currentSign,dbName);
        }
    }
    if(event->buttons() == Qt::RightButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1){
            Sign::sign[0][floor(gridX/Grid::split)][floor(gridY/Grid::split)] = 0;
            saveSign(dbColumn,QString::number(0),currentSign, dbName);
            //setSign(currentSign,dbName);
        }
    }
}

void GlWidget::mouseHandler(QMouseEvent *event){
    onGrid(event);
    onBotMenu(event);
    onTopMenu(event);
    onArrow(event);
    onOverTopMenu(event);
}

void GlWidget::onGrid(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1){
            //Sign::sign[0][gridX][gridY] = 1;
            Sign::sign[0][floor(gridX/Grid::split)][floor(gridY/Grid::split)] = 1;
            //std::cout<<"x: "<<gridX<<" - x: "<<gridX/Grid::split<<" / y: "<<gridY<<" - y: "<<gridY/Grid::split<<std::endl;
            saveSign(dbColumn,QString::number(1),currentSign, dbName);
        }
    }
    if(event->buttons() == Qt::RightButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1){
            Sign::sign[0][floor(gridX/Grid::split)][floor(gridY/Grid::split)] = 0;
            saveSign(dbColumn,QString::number(0),currentSign, dbName);
        }
    }
}

void GlWidget::onTopMenu(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        for(int x=topMenuSpacer; x<topMax+topMenuSpacer; x++){
            if((int)gridX==x && (int)gridY-1==(int)(Grid::high+topMenuLow)*10){
                std::cout<<"topmenu: "<<x-topMenuSpacer<<std::endl;
                currentSign = QString::number(Sign::set[x-topMenuSpacer+shift]);
                setSign(currentSign, dbName);
            }
        }
    }
}

void GlWidget::onArrow(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        if((int)gridX==(int)(Grid::low*10) && (int)gridY==(int)((Grid::high+topMenuLow)*10)){
            std::cout<<"left arrow clicked"<<std::endl;
            if(shift) shift--;
        }
        if((int)(gridX-1)==(int)((Grid::high-.1)*10) && (int)gridY==(int)((Grid::high+topMenuLow)*10)){
            std::cout<<"right arrow clicked, size:"<<Sign::set.size()<<std::endl;
            if(shift<(int)Sign::set.size()-topMax) shift++;
        }
    }
}

void GlWidget::onBotMenu(QMouseEvent *event){
    bool del;
    if(event->buttons() == Qt::LeftButton){
        if((gridX>=Grid::low && gridX<Grid::high/2*10) && (gridY>=botBtnLow*10 && gridY<botBtnHigh*10)){
            addSign(dbName);
            setDistinctSigns(dbName);
            //std::cout<<"left clicked"<<std::endl;
        }
        if((gridX>=Grid::high/2*10 && gridX<Grid::high*10) && (gridY>botBtnLow*10 && gridY<botBtnHigh*10)){
            del = deleteAlert();
            if(del){
                removeSign(currentSign, dbName);
                setDistinctSigns(dbName);
                setSign(QString::number(Sign::set[0]), dbName);
            }
            //std::cout<<"right clicked "<<std::endl;
        }
        /*if((gridX>=Grid::low && gridX<Grid::high*10) && (gridY>=botBigLow*10 && gridY<botBigHigh*10)){
            std::cout<<"screene"<<std::endl;
        }*/
    }
}

void GlWidget::onOverTopMenu(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        if(((int)gridX>=(int)((Grid::low+0)*10) && (int)gridX<(int)((Grid::high/3)*10))
        && ( (int)gridY>=(int)(((Grid::high+overtopLow)*10)) && (int)gridY<(int)(((Grid::high+overtopHigh)*10)))){
            dbName = dbNameLarge,
            setDistinctSigns(dbName);
            Grid::split = 1;
        }
        if(((int)gridX>=(int)((Grid::high/3)*10) && (int)gridX<(int)((Grid::high/3*2)*10))
        && ( (int)gridY>=(int)(((Grid::high+overtopLow)*10)) && (int)gridY<(int)(((Grid::high+overtopHigh)*10)))){
            dbName = dbNameMedium;
            setDistinctSigns(dbName);
            Grid::split = 2;
        }
        if(((int)gridX>=(int)((Grid::high/3*2)*10) && (int)gridX<(int)((Grid::high)*10))
        && ( (int)gridY>=(int)(((Grid::high+overtopLow)*10)) && (int)gridY<(int)(((Grid::high+overtopHigh)*10)))){
            dbName = dbNameSmall;
            setDistinctSigns(dbName);
            Grid::split = 3;
        }
        //std::cout<<"OVERTOP x: "<<(Grid::low+0)*10<<" / y: "<<(Grid::high+.3)*10<<std::endl;
    }
}

void GlWidget::hover(){
    if((gridX>=Grid::low && gridX<Grid::high/2*10) && (gridY>=botBtnLow*10 && gridY<botBtnHigh*10)) botLeftHover = true;
    else botLeftHover = false;
    if((gridX>=Grid::high/2*10 && gridX<Grid::high*10) && (gridY>botBtnLow*10 && gridY<botBtnHigh*10)) botRightHover = true;
    else botRightHover = false;
    if((gridX>=Grid::low && gridX<Grid::high*10) && (gridY>=botBigLow*10 && gridY<botBigHigh*10)) botBigHover = true;
    else botBigHover = false;
    if((int)gridX==(int)(Grid::low*10) && (int)gridY==(int)((Grid::high+topMenuLow)*10)) leftArrowHover = true;
    else leftArrowHover = false;
    if((int)(gridX-1)==(int)((Grid::high-.1)*10) && (int)gridY==(int)((Grid::high+topMenuLow)*10)) rightArrowHover = true;
    else rightArrowHover = false;
    if(((int)gridX>=(int)((Grid::low+0)*10) && (int)gridX<(int)((Grid::high/3)*10))
    && ( (int)gridY>=(int)(((Grid::high+overtopLow)*10)) && (int)gridY<(int)(((Grid::high+overtopHigh)*10)))){
        bigRangeHover = true;
    }
    else bigRangeHover = false;
    if(((int)gridX>=(int)((Grid::high/3)*10) && (int)gridX<(int)((Grid::high/3*2)*10))
    && ( (int)gridY>=(int)(((Grid::high+overtopLow)*10)) && (int)gridY<(int)(((Grid::high+overtopHigh)*10)))){
        mediumRangeHover = true;
    }
    else mediumRangeHover = false;
    if(((int)gridX>=(int)((Grid::high/3*2)*10) && (int)gridX<(int)((Grid::high)*10))
    && ( (int)gridY>=(int)(((Grid::high+overtopLow)*10)) && (int)gridY<(int)(((Grid::high+overtopHigh)*10)))){
        smallRangeHover = true;
    }
    else smallRangeHover = false;
}

void GlWidget::createDbColumnString(){
    QString a, t;//, dbColumnT;
    if(gridX>=0 && gridX<Grid::range && gridY>=0 && gridY<Grid::range){
        //a = col[gridX];
        t = col[gridX/Grid::split];
        //dbColumn = a+QString::number(gridX)+QString::number(gridY);
        dbColumn = t+QString::number(floor(gridX/Grid::split))+QString::number(floor(gridY/Grid::split));
        //qDebug()<<"dbColumn: "<<dbColumn;
        //qDebug()<<"TdbColumn: "<<dbColumnT;
    }
}

bool GlWidget::deleteAlert(){
    QMessageBox msgBox;
    msgBox.setText("Do you really want to delete this?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch(ret){
      case QMessageBox::Ok: return true; break;
      case QMessageBox::Cancel: return false; break;
    }
}

void GlWidget::topMenuText(){
    float x, y;
    QString t;
    y = ((float)HEIGHT*3.65)/(Grid::range+-Grid::bottom+Grid::top);
    for(float i=1; i<=topMax; i++){
        t = QString::number(i+shift);
        x = ((float)WIDTH*((i+topMenuSpacer)/10))/(Grid::high+(-Grid::left+Grid::right));
        glColor3f(1,1,1);
        renderText(x,y,t);
    }
}

void GlWidget::botMenuText(){
    float x, y;
    y = 0.91 * HEIGHT;
    x = ((float)WIDTH*(0.45*Grid::high/2))/(Grid::high+(-Grid::left+Grid::right));
    glColor3f(1,1,1);
    renderText(x,y,botLeftText);
    x = ((float)WIDTH*(0.7*Grid::high))/(Grid::high+(-Grid::left+Grid::right));
    renderText(x,y,botRightText);
    y = 0.96 * HEIGHT;
    x = ((float)WIDTH*(0.45*Grid::high))/(Grid::high+(-Grid::left+Grid::right));
    renderText(x,y,botBigText);
}

void GlWidget::overtopMenuText(){
    float x, y;
    y = ((float)HEIGHT*2.0)/(Grid::range+-Grid::bottom+Grid::top);
    x = 0.15*WIDTH;
    glColor3f(1,1,1);
    renderText(x,y,largeText);
    x = 0.45*WIDTH;
    renderText(x,y,mediumText);
    x = 0.8*WIDTH;
    renderText(x,y,smallText);
}

