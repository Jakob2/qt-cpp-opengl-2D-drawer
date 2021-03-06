#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "global.h"
#include "grid.h"
#include "menu.h"
#include "sign.h"
#include "db.h"

class GlWidget : public QGLWidget, public Grid, public Menu, public Sign, public Db
{
public:
    explicit GlWidget(QWidget * parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QTimer timer;

    void mousePressEvent(QMouseEvent *event);
    int mouseX;
    int mouseY;
    void coords();
    float gridX, gridY;
    void mouseMoveEvent(QMouseEvent *event);
    void mouseToGrid(float mouseX, float mouseY);
    float glX, glY;

    void mouseHandler(QMouseEvent *event);
    void onGrid(QMouseEvent *event);
    void onTopMenu(QMouseEvent *event);
    void onArrow(QMouseEvent *event);
    void onBotMenu(QMouseEvent *event);
    void onOverTopMenu(QMouseEvent *event);
    void onLeftMenu(QMouseEvent *event);
    void hover();

    void createDbColumnString();
    QString dbColumn;

    QString currentSign = "0";

    bool deleteAlert();

    QString botLeftText = "Add Sign";
    QString botRightText = "Delete Sign";
    QString botBigText = "Create New Set";
    QString largeText = "Large";
    QString mediumText = "Medium";
    QString smallText = "Small";
    void topMenuText();
    void botMenuText();
    void overtopMenuText();
};

#endif // GLWIDGET_H
