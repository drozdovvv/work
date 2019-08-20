#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>

namespace Ui {
class MainWindow;
}

class OpenGlWidget : public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit OpenGlWidget(QWidget *parent = 0);
    ~OpenGlWidget();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void LoadGLTextures(const QString name);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    QOpenGLContext *m_context;
    QOpenGLFunctions *m_functions;
    QString m_currentImagePath;
    GLuint texture[1];
    double m_oldX=0;
    double m_oldY=0;
    double m_xRot=0;
    double m_yRot=0;
    double m_width = 0;
    double m_height = 0;

};

#endif // MAINWINDOW_H
