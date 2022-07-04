#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLineF>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void paintEvent(QPaintEvent *event) override; //override siginifica que sobreescribe
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //void mousePressEventlinea(QMouseEvent *event);
private slots:
    void on_actionAncho_triggered();

    void on_actionSalir_triggered();

    void on_actionColor_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionLineas_triggered();

private:
    Ui::Principal *ui;
    QImage *mImagen;        // Imagen sobre la que se va a dibujar
    QPainter *mPainter;     // Painter de la imagen
    QPoint mInicial;        // Punto incial para dibujar la línea
    QPoint mFinal;          // Punto final para dibujar la línea
    bool mPuedeDibujar;     // Determina si debe o no dibujar
    int mAncho;             // Define el ancho del pincel
    QColor mColor;          // Define el color del pincel
    int mNumLineas;         // Cuenta el número de líneas
    bool m_porGuardar;      //para guardar imagen actual
    bool m_linea;
};
#endif // PRINCIPAL_H
