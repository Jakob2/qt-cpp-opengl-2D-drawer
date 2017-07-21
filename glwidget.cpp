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
    topMenu();
    drawSign();
    horizontal();
    vertical();
    botMenu();
    glColor3f(1,1,1);
    renderText(floor((float)WIDTH/4), HEIGHT-25, botLeftText);
    renderText(floor(((float)WIDTH/4)+(float)WIDTH/2.5), HEIGHT-25, botRightText);
    topMenuText();
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
    gridY = Grid::range - floor((10*((Grid::high+(-Grid::bottom+Grid::top))*mouseY)/HEIGHT))+2;
    //std::cout<<"x: "<<gridX<<" / y: "<<gridY<<std::endl;
}

void GlWidget::mouseMoveEvent(QMouseEvent *event){
    mouseX = event->pos().x();
    mouseY = event->pos().y();
    coords();
    createDbColumnString();
    hover();
    if(event->buttons() == Qt::LeftButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1) Sign::sign[0][gridX][gridY] = 1;
        saveSign(dbColumn,QString::number(1),currentSign);
    }
    if(event->buttons() == Qt::RightButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1) Sign::sign[0][gridX][gridY] = 0;
        saveSign(dbColumn,QString::number(0),currentSign);
    }
}

void GlWidget::mouseHandler(QMouseEvent *event){
    onGrid(event);
    onBotMenu(event);
    onTopMenu(event);
}

void GlWidget::onGrid(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1){
            Sign::sign[0][gridX][gridY] = 1;
            saveSign(dbColumn,QString::number(1),currentSign);
        }
    }
    if(event->buttons() == Qt::RightButton){
        if(gridX>=0 && gridX<=Grid::range-1 && gridY>=0 && gridY<=Grid::range-1){
            Sign::sign[0][gridX][gridY] = 0;
            saveSign(dbColumn,QString::number(0),currentSign);
        }
    }
}

void GlWidget::onTopMenu(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        for(int x=topMenuSpacer; x<(int)Sign::set.size()+topMenuSpacer; x++){
            if((int)gridX==x && (int)gridY-1==(int)(Grid::high+topMenuLow)*10){
                std::cout<<"topmenu: "<<x-topMenuSpacer<<std::endl;
                currentSign = QString::number(x-topMenuSpacer+1);
                setSign(currentSign);
            }
        }
    }
}

void GlWidget::onBotMenu(QMouseEvent *event){
    bool del;
    if(event->buttons() == Qt::LeftButton){
        if((gridX>=Grid::low && gridX<Grid::high/2*10) && (gridY>=botBtnLow*10 && gridY<botBtnHigh*10)){
            addSign();
            setDistinctSigns();
            std::cout<<"left clicked"<<std::endl;
        }
        if((gridX>=Grid::high/2*10 && gridX<Grid::high*10) && (gridY>botBtnLow*10 && gridY<botBtnHigh*10)){
            del = deleteAlert();
            if(del){
                removeSign(currentSign);
                setDistinctSigns();
            }
            std::cout<<"right clicked "<<std::endl;

        }
    }
}

void GlWidget::hover(){
    if((gridX>=Grid::low && gridX<Grid::high/2*10) && (gridY>=botBtnLow*10 && gridY<botBtnHigh*10)) botLeftHover = true;
    else botLeftHover = false;
    if((gridX>=Grid::high/2*10 && gridX<Grid::high*10) && (gridY>botBtnLow*10 && gridY<botBtnHigh*10)) botRightHover = true;
    else botRightHover = false;
}

void GlWidget::createDbColumnString(){
    QString a;
    if(gridX>=0 && gridX<Grid::range && gridY>=0 && gridY<Grid::range){
        a = col[gridX];
        dbColumn = a+QString::number(gridX)+QString::number(gridY);
        qDebug()<<"dbColumn: "<<dbColumn;
    }
}

bool GlWidget::deleteAlert(){
    QMessageBox msgBox;
    msgBox.setText("Do you really want to delete this?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch(ret){
      case QMessageBox::Ok:
          std::cout<<"Ok"<<std::endl;
          return true;
          break;
      case QMessageBox::Cancel:
          std::cout<<"Cancel"<<std::endl;
          return false;
          break;
    }
}

void GlWidget::topMenuText(){
    float x, y;
    y = 25;
    QString t;
    for(float i=1; i<=(int)Sign::set.size(); i++){
        t = QString::number(i);
        x = ((float)WIDTH*(i/10))/(Grid::high+(-Grid::left+Grid::right))+50;
        renderText(x,y,t);
    }
}

