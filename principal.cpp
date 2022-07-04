#include "principal.h"
#include "ui_principal.h"

#define DEFAULT_ANCHO 3 //ancho por defecto del pincel

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Instanciando la imagen (creando)
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied); //Qimage se refiere al formato en este caso png
    // Rellenar la imagen de color blanco
    mImagen->fill(Qt::white);
    // Instanciar el Painter a partir de la imagen
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing); //antialiasing mejora las imagenes en dispositovos LSD
    // Inicializar otras variables
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;
    m_porGuardar =false;

}

Principal::~Principal()
{
    //SON para borrar los objetos no pasa nada si no pones
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    // Crear el painter de la ventana principal, esto es para dibujar en la imagen
    QPainter painter(this);
    // Dibujar la imagen
    painter.drawImage(0, 0, *mImagen);
    // Acepatr el evento
    event->accept();
    //levantar bandera
    m_porGuardar = true;
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    //levanta la bandera (para que se pueda dibujar)
    mPuedeDibujar = true; //mpuededinajar es la bandera para dibujar o no dibujar
    //captura la posicion(punto x,y)del mouse
    mInicial = event->pos();
    //acepta el evento
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    // Validar si se puede dibujar
    if ( !mPuedeDibujar ) {
        //acepta el evento
        event->accept();
        //salgo del metodo
        return;
    }
    // Capturar el punto a donde se mueve el mouse
    mFinal = event->pos(); //mfinal es un punto
    // Crear un pincel y establecer atributos
    QPen pincel;
    pincel.setColor(mColor);
    pincel.setWidth(mAncho);
    // Dibujar una linea
    mPainter->setPen(pincel); //establece el ancho inicial
    mPainter->drawLine(mInicial, mFinal);
    // Mostrar el número de líneas en la barra de estado
    ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
    // Actualizar la interfaz (repintar con paintEvent)
    update();
    // actualizar el punto inicial
    mInicial = mFinal;


}

void Principal::mouseReleaseEvent(QMouseEvent *event) //esto es cuando dejas presionar el click
{
    //Bajar la bandera (no se puede dibujar)
    mPuedeDibujar = false;
    // Aceptar el vento
    event->accept();

}

void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  mAncho,
                                  1, 20);
}

void Principal::on_actionSalir_triggered()
{
    if(m_porGuardar){
        int respuesta = QMessageBox::warning(this,
                                             "Nuevo",
                                             "¿Desea guardar el archivo actual?","Si","No");
        if(respuesta == QMessageBox::AcceptRole){
            on_actionGuardar_triggered();
        }
    }
    this->close();
}

void Principal::on_actionColor_triggered()
{
    //es para que aparezaca el cuadro de dialgo de colores
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    if(m_porGuardar){
        int respuesta = QMessageBox::warning(this,
                                             "Nuevo",
                                             "¿Desea guardar el archivo actual?","Si","No");
        if(respuesta == QMessageBox::AcceptRole){
            on_actionGuardar_triggered();
        }
    }
    mImagen->fill(Qt::white); //pinta toda la imagen o el formulario de blanco para empezar de nuevo
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    //Abrir cuadro de dialogo para obtener el nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes .png (*.png)");
   //validar que el nombre del archivo no sea vacio
    if ( !nombreArchivo.isEmpty() ){ // inEmpty signifca "esta vacio"
       //guardar imagen
        if (mImagen->save(nombreArchivo))
            //Si todo va bien muestra un mensaje de informacion
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
       m_porGuardar = false;
        }else{
            //si hay un error muestro advertencia
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}

void Principal::on_actionLineas_triggered()
{


    /*if ( !mPuedeDibujar ) {
        //acepta el evento
        linea->accept();
        //salgo del metodo
        return;
    }
    mInicial = linea->pos();
      mFinal = linea->pos(); //mfinal es un punto
         mPainter->drawLine(mInicial, mFinal);
         update();*/

          /* QAction *drawLineAction = new QAction("Lineas");
           drawLineAction->setIcon(QIcon("Lineas"));
           drawLineAction->setToolTip(tr("Lineas"));
           drawLineAction->setStatusTip(tr("Lineas"));
           drawLineAction->setCheckable(true);
           drawLineAction->setChecked(true);
           pintorlinea = drawLineAction;*/

 /*mPainter->drawPoint(mInicial);
 mPainter->drawPoint(mFinal);
 mPainter->drawLine(mInicial, mFinal);*/
}

