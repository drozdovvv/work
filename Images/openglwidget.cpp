#include "openglwidget.h"
#include <QFileDialog>
#include <QtGui>


OpenGlWidget::OpenGlWidget(QWidget *parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);

    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    m_context->create();
    m_context->makeCurrent(this);
    m_functions = m_context->functions();
}

OpenGlWidget::~OpenGlWidget()
{

}


void OpenGlWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Q)
    {   //naciskasz Q
        //odkrywa sie dialog plikowy, gdzie mozna wybrac image formatu: (nie zamykac okno, jezeli image nie jest wybrany )
        m_currentImagePath = QFileDialog::getOpenFileName(nullptr, "Select image", "./", tr("All files (*.*);;JPEG (*.jpg *.jpeg);;TIFF (*.tif)" ));
        // laduje obrany image jak teksture
        // funkcja:
        LoadGLTextures(m_currentImagePath);
        update();
        paintGL();
    }
	
    // Сtrl + W -> powiększenie szerokosci image
    else if(event->key() == Qt::Key_W && QGuiApplication::queryKeyboardModifiers() & Qt::ControlModifier)
    {
        m_width += 0.01;
    }
	
    // Shift + W -> zmniejszenie szerokosci image
    else if(event->key() == Qt::Key_W && QGuiApplication::queryKeyboardModifiers() & Qt::ShiftModifier)
    {
        m_width -= 0.01;
    }
	
	
    // Shift + H -> zmniejszenie wysokosci image
    else if(event->key() == Qt::Key_H && QGuiApplication::queryKeyboardModifiers() & Qt::ShiftModifier)
    {
        m_height -= 0.01;
    }
	
    // Сtrl + Н -> powiększenie wysokosci image
    else if(event->key() == Qt::Key_H && QGuiApplication::queryKeyboardModifiers() & Qt::ControlModifier)
    {
        m_height += 0.01;
    }
	
    // Сtrl + D -> powiększenie wysokosci i szerokosci image(powiekszenie za przekatna)
    else if(event->key() == Qt::Key_D && QGuiApplication::queryKeyboardModifiers() & Qt::ControlModifier)
    {
        m_width += 0.01;
        m_height += 0.01;
    }
	
    // Shift + D -> zmniejszenie wysokosci i szerokosci image(zmniejszenie za przekatna)
    else if(event->key() == Qt::Key_D && QGuiApplication::queryKeyboardModifiers() & Qt::ShiftModifier)
    {
        m_width -= 0.01;
        m_height -= 0.01;
    }
	
    // Ctrl + R -> reset modyfikation (poczatkowy stan image)
    else if(event->key() == Qt::Key_R && QGuiApplication::queryKeyboardModifiers() & Qt::ControlModifier)
    {
        m_width = 0.0;
        m_height = 0.0;
        m_xRot = 0;
        m_yRot = 0;
    }
    else
    {
        return;
    }
    update();
    paintGL();
}

void OpenGlWidget::LoadGLTextures( const QString name )
{
    QImage img;

    if(!img.load(name)){
        //std::cerr << "ERROR in loading image" << std::endl;
    }

    // nalozenie image jak opengl texture

    QImage t = QGLWidget::convertToGLFormat(img);

    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());

    // ustawianie parametrow

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

// funkcja oswietlenia, pozycji swiatla
void OpenGlWidget::initializeGL()
{
        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT2);
        glEnable(GL_MULTISAMPLE);
        static GLfloat lightPosition2[4] = { 0.5, 5.0,7.0, 1 };
        glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
        m_functions->initializeOpenGLFunctions();
}


// zdarzenie nacisnecia+ruchu myszy
// nacisk lewego przycisku+ruch = ruch image
void OpenGlWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        int dx = event->x() - m_oldX;
        int dy = event->y() - m_oldY;
        if (event->buttons() & Qt::LeftButton) {
                m_xRot += 3 * dy;
                m_yRot += 3 * dx;
            } else if (event->buttons() & Qt::RightButton) {
                m_xRot += 3 * dy;
                m_yRot += 3 * dx;
            }

            m_oldX = event->pos().x();
            m_oldY = event->pos().y();
        update();
        paintGL();

    }
}

void OpenGlWidget::resizeGL(int width, int height)
{

}

void OpenGlWidget::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // oglaszam two-dimensional model, wlaczam swiatlo, lampe zerowa..., tesr na glebokosc, 2D teksture...

    glShadeModel( GL_FLAT );
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);                // wybiaram teksryre jak aktywna do nakladania ja na objekty
	
    // maciez odwrocenia image -> m_xRot, m_yRot sie zmieniaja, kiedy krecisz image myszka.
    glRotatef(m_xRot, 1, 0, 0);
    glRotatef(m_yRot, 0, 1, 0);
	
    // tworzenie prostokatu
    // wyznaczam konstrukcje, na jaka bede nakladac image
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f , 1.0f ); glVertex2f(-0.5f - m_width/2, 0.5f + m_height/2);  // vertex 1
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f - m_width/2, -0.5f - m_height/2); // vertex 2
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f + m_width/2, -0.5f - m_height/2); // vertex 3
    glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f + m_width/2, 0.5f + m_height/2); // vertex 4
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glFlush();
}

void OpenGlWidget::resizeEvent(QResizeEvent *event)
{

}

void OpenGlWidget::paintEvent(QPaintEvent *event)
{
paintGL();
}
