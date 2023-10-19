// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"
#include "qspinbox.h"


// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>
#include <QtMath>
// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie lini w Qt");

    //Zmieniamy rozmiar okna
    resize(800,600);

    // Ustawiamy wymiary obrazka i wspolrzedne jego
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    poczX = 25;
    poczY = 25;

    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
    img = new QImage(szer,wys,QImage::Format_RGB32);
    imgkopia = new QImage(szer, wys, QImage::Format_RGB32);
    setMouseTracking(true);
    czysc();

    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+400));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski
    // draw1Button = new QPushButton("Rysuj 1");
    // draw2Button = new QPushButton("Rysuj 2");
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
 elipsaButton = new QPushButton("Elipsa");
 koloButton = new QPushButton("Kolo");
 spinBox = new QSpinBox(this);


    // Dodajemy przyciski do layoutu
    // boxLayout->addWidget(draw1Button);
    // boxLayout->addWidget(draw2Button);
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);
 boxLayout->addWidget(elipsaButton);
 boxLayout->addWidget(koloButton);
 boxLayout->addWidget(spinBox);
    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);


    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));

connect(elipsaButton,SIGNAL(clicked()),this,SLOT(slot_Elipsa()));
connect(koloButton,SIGNAL(clicked()),this,SLOT(slot_Kolo()));

connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));
    // connect(draw1Button,SIGNAL(clicked()),this,SLOT(slot_rysuj1()));

    //  connect(draw2Button,SIGNAL(clicked()),this,SLOT(slot_rysuj2()));


}

// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
    delete imgkopia;
}


// Funkcja "odmalowujaca" komponent
void MyWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    //p.drawImage(poczX,poczY,*img);
    if (klikniete)
    {
        p.drawImage(poczX, poczY, *imgkopia);
    }
    else {
        p.drawImage(poczX, poczY, *img);
    }

}

void MyWindow::onSpinBoxValueChanged(int nowyBok){

    iloscbokow = nowyBok;

}
void MyWindow::slot_Elipsa(){

    isElipsa=true;
}

void MyWindow::slot_Kolo(){

    isElipsa=false;
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku "Czysc" (cleanButton)
void MyWindow::slot_czysc()
{
    // Funkcja czysci (zamalowuje na bialo) obszar rysowania
    // definicja znajduje sie ponizej
    czysc();

    // Funkcja "update()" powoduje ponowne "namalowanie" calego komponentu
    // Wywoluje funkcje "paintEvent"
    update();
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku "Rysuj 1" (draw1Button)
/*void MyWindow::slot_rysuj1()
//{
//    rysuj1();
//    update();
}*/

// Funkcja (slot) wywolywana po nacisnieciu przycisku "Rysuj 2" (draw2Button)
/*void MyWindow::slot_rysuj2()
{
    rysuj2();
    update();
}*/

// Funkcja powoduje wyczyszczenie (zamalowanie na bialo)
// obszaru rysowania
void MyWindow::czysc()
{
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr, *ptrkopia;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();
    ptrkopia = imgkopia->bits();

    int i,j;

    // Przechodzimy po wszystkich wierszach obrazu
    for(i=0; i<wys; i++)
    {
        // Przechodzimy po pikselach danego wiersza
        // W kazdym wierszu jest "szer" pikseli (tzn. 4 * "szer" bajtow)
        for(j=0; j<szer; j++)
        {
            ptr[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptr[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptr[szer*4*i + 4*j + 2] = 255; // Skladowa RED

            ptrkopia[szer*4*i + 4*j]=255; // Skladowa BLUE
            ptrkopia[szer*4*i + 4*j + 1] = 255; // Skladowa GREEN
            ptrkopia[szer*4*i + 4*j + 2] = 255; // Skladowa RED

        }
    }
}


// Funkcja powoduje zamalowanie obszaru rysowania pewnym wzorem
/*void MyWindow::rysuj1()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0;i<wys;i++)
    {
        for(j=0;j<szer ;j++)
        {
            ptr[szer*4*i + 4*j]=i;
            ptr[szer*4*i + 4*j + 1] = j;
            ptr[szer*4*i + 4*j + 2] = i*j;
        }
    }
}
*/
// Funkcja powoduje zamalowanie obszaru rysowania pewnym wzorem
/*void MyWindow::rysuj2()
{
    unsigned char *ptr;
    ptr = img->bits();
    int szer = img->width();
    int wys = img->height();

    int i,j;
    for(i=0;i<wys;i++)
    {
        for(j=0;j<szer ;j++)
        {
            ptr[szer*4*i + 4*j]=i;
            ptr[szer*4*i + 4*j + 1] = j;
            ptr[szer*4*i + 4*j + 2] = i+j;
        }
    }
}*/

void MyWindow::kopia(QImage *image1, QImage *image2)
{
    unsigned char *ptr1, *ptr2;

    for (int i = 0; i < wys; i++)
    {
        ptr1 = image1->bits() + i * image1->bytesPerLine();
        ptr2 = image2->bits() + i * image2->bytesPerLine();

        for (int j = 0; j < szer; j++)
        {
            ptr1[4 * j] = ptr2[4 * j];
            ptr1[4 * j + 1] = ptr2[4 * j + 1];
            ptr1[4 * j + 2] = ptr2[4 * j + 2];
        }
    }
}


void MyWindow::pixel(int x, int y,  QImage *image)

{
    if ( x>=0 && y>=0 &&  y<wys && x<szer)
    {
        unsigned char *ptr;

        ptr=image->scanLine(y);

        ptr[ 4 * x]= 0;
        ptr[4 * x + 1]= 0;
        ptr[4 * x + 2]=255;

        update();
    }
}

void MyWindow::Linia(int x1, int y1, int x2,  int y2, QImage *image)

{
    double a, b;

    int x, y;

    if (x1 == x2)
    {
        x = x1;
        if (y1 < y2)
        {
            for (y = y1; y != y2; y += 1)
                pixel(x, y, image);
        }
        else
        {
            for (y = y1; y != y2; y -= 1)
                pixel(x, y, image);
        }
    }
    else

    {
        a = float (y1 - y2) / (x1 - x2);
        b = y1 - a * x1;

        if (a <= 1 && a >= -1)
        {
            if (x1 < x2)
            {
                for (x = x1; x != x2; x += 1)
                {
                    y = a * x + b;
                    pixel(x, (int)y + 0.5, image);
                }
            }
            else
            {
                for (x = x1; x != x2; x -= 1)
                {
                    y = a * x + b;
                    pixel (x, (int)y + 0.5, image);
                }
            }
        }
        else

        {
            if (y1 < y2)
            {
                for (y = y1; y != y2; y += 1)
                {
                    x = (y - b) / a;
                    pixel(x, (int)y + 0.5, image);
                }
            }
            else

            {
                for (y = y1; y != y2; y -= 1)
                {
                    x = (y - b) / a;
                    pixel(x, (int)y + 0.5,image);
                }
            }
        }

    }

    update();
}

void MyWindow::Kolo(int x1, int y1, int x2, int y2, QImage *image)
{
    int x;
    int y ;

    double promienpom =((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
    double promien = sqrt(promienpom);

    for (x = -promien; x <= promien; x++)

    {
        y = sqrt(pow(promien,2) - (pow(x,2))); //y = sqrt(R^2-x^2);

        pixel(x1+x, y1+y, image);
        pixel(x1+x, y1-y, image);
        pixel(x1-x, y1+y, image);
        pixel(x1-x, y1-y, image);

        pixel(x1+y, y1+x, image);
        pixel(x1+y, y1-x, image);
        pixel(x1-y, y1+x, image);
        pixel (x1-y, y1-x, image);

     /*   pixel(x1 + x, (int)floor( y1+y + 0.5), image);
        pixel(x1 + x, -(int)floor( y1-y + 0.5), image);
        pixel(x1 - x, (int)floor(y1+y + 0.5), image);
        pixel(x1 - x, -(int)floor(y1-y + 0.5), image);

        pixel(x1 + y, (int)floor(y1+x + 0.5), image);
        pixel(x1 + y, -(int)floor(y1-x + 0.5), image);
        pixel(x1 - y, (int)floor(y1+x + 0.5), image);
        pixel(x1 - y, -(int)floor( y1-x + 0.5), image);*/


    }
}
void MyWindow::Elipsa( int x1, int y1, int x2, int y2, QImage *image )
{
    const double kolo = 2 * M_PI;

    double a = kolo / iloscbokow;

    for (double i = 0; i <= kolo; i += a)
    {
        double X1 = round((x2-x1) * cos(i)); //pkt1
        double X2 = round((x2-x1) * cos(i + a));

        double Y1 = round((y2-y1) * sin(i)); //pkt1
        double Y2 = round((y2-y1) * sin(i + a));

        Linia(x1 + X1, y1 + Y1, x1 + X2, y1 + Y2, image);

    }

    update();
}

// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    // Pobieramy wspolrzedne punktu klikniecia
    // Sa to wspolrzedne wzgledem glownego okna
    int x = event->x();
    int y = event->y();

    // Przesuwamy je zeby nie rysowac od brzegu
    x = x - poczX;
    y = y - poczY;

    x1 = x;
    y1 = y;

    //    int kolor = 0;
    //   unsigned char *ptr;
    //   ptr = img->bits();

    // Sprawdzamy ktory przycisk myszy zostal klkniety
    klikniete = true;

    /*    if(event->button() == Qt::LeftButton)
    {
        // jezeli lewy to ustawiamy kolor na czarny
        kolor = 0;

    }
    else
    {
        // jezeli prawy to ustawiamy kolor na bialy
        kolor = 255;
    }

    // Sprawdzamy czy klikniecie nastapilo w granicach rysunku
    if ((x>=0)&&(y>=0)&&(x<szer)&&(y<wys))
    {
        // Ustawiamy kolor kliknietego piksela na bialy lub czarny
        ptr[szer*4*y + 4*x] = kolor;
        ptr[szer*4*y + 4*x + 1] = kolor;
        ptr[szer*4*y + 4*x + 2] = kolor;
    }

    // Odswiezamy komponent
    update();
*/
    update();
}
void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    x = x - poczX;
    y = y -  poczY;

    if (klikniete)

    {
        kopia(imgkopia, img);

        if (isElipsa)
            Elipsa(x1, y1, x, y, imgkopia);
        else
            Kolo(x1, y1, x, y, imgkopia);

        update();
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    klikniete = false;
    int x = event->x();
    int y = event->y();

    x = x - poczX;
    y = y - poczY;


    if (isElipsa)
        Elipsa(x1, y1, x, y, imgkopia);
    else
        Kolo(x1, y1, x, y, imgkopia);

    kopia(img, imgkopia);
}





