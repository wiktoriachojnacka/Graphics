// Dolaczamy plik naglowkowy naszej klasy MyWindow
#include "mywindow.h"


// Dolaczamy plik naglowkowy komponentu layoutu pionowego
// Komponent ten sluzy do rozmieszczania elementow GUI w oknie
#include <QVBoxLayout>

// Definicja konstruktora, wywolujemy najpierw
// konstruktor klasy nadrzednej
MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    // Ustawiamy tytul okna
    setWindowTitle("Rysowanie lini w Qt");

    //Zmieniamy rozmiar okna
    resize(800,700);

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



RGBgrupa = new QGroupBox("RGB", this);
HSVgrupa = new QGroupBox("HSV", this);


    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+100));
RGBgrupa->setGeometry(QRect(poczX+szer+poczX,(poczY+130),800-szer-2*poczX,poczY+200));
HSVgrupa->setGeometry(QRect(poczX+szer+poczX,(poczY+355),800-szer-2*poczX,poczY+200));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;
QVBoxLayout *layoutRGB = new QVBoxLayout();
    QVBoxLayout *layoutHSV = new QVBoxLayout();

    // Tworzymy 4 przyciski
    // draw1Button = new QPushButton("Rysuj 1");
    // draw2Button = new QPushButton("Rysuj 2");
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
sliderRGB1 = new QSlider(Qt::Horizontal);
sliderRGB1->setRange(0,255);
sliderRGB1->setSingleStep(1);
sliderRGB2 = new QSlider(Qt::Horizontal);
sliderRGB2->setRange(0,255);
sliderRGB3 = new QSlider(Qt::Horizontal);
sliderRGB3->setRange(0,255);
sliderHSV1 = new QSlider(Qt::Horizontal);
sliderHSV1->setRange(0,360);
sliderHSV2 = new QSlider(Qt::Horizontal);
sliderHSV2->setRange(0,1000);
sliderHSV3 = new QSlider(Qt::Horizontal);
sliderHSV3->setRange(0,1000);

label = new QLabel("Wartość: 0");
layoutRGB->addWidget(label);
    // Dodajemy przyciski do layoutu
    // boxLayout->addWidget(draw1Button);
    // boxLayout->addWidget(draw2Button);
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);
layoutRGB -> addWidget(sliderRGB1);
layoutRGB-> addWidget(sliderRGB2);
layoutRGB-> addWidget(sliderRGB3);
layoutHSV-> addWidget(sliderHSV1);
layoutHSV-> addWidget(sliderHSV2);
layoutHSV-> addWidget(sliderHSV3);


    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);
RGBgrupa->setLayout(layoutRGB);
HSVgrupa->setLayout(layoutHSV);



    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
connect(sliderRGB1, SIGNAL(valueChanged(int)), this, SLOT(RGBsliderRed(int)));
connect(sliderRGB2, SIGNAL(valueChanged(int)), this, SLOT(RGBsliderGreen(int)));
connect(sliderRGB3, SIGNAL(valueChanged(int)), this, SLOT(RGBsliderBlue(int)));
connect(sliderHSV1, SIGNAL(valueChanged(int)), this, SLOT(HSVsliderHue(int)));
connect(sliderHSV2, SIGNAL(valueChanged(int)), this, SLOT(HSVsliderSaturation(int)));
connect(sliderHSV3, SIGNAL(valueChanged(int)), this, SLOT(HSVsliderValue(int)));

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
    int szer = img->szer();
    int wys = img->wys();

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
    int szer = img->szer();
    int wys = img->wys();

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

void MyWindow::pixel(int x, int y, QImage *image)

{
    if ( x>=0 && y>=0 &&  y<wys && x<szer)
    {
        unsigned char *ptr;

        ptr=image->scanLine(y);

        ptr[4 * x] = czerwony;
        ptr[4 * x + 1] =  zielony;
        ptr[4 * x + 2] = niebieski;
        update();
    }
}

void MyWindow::RGBsliderRed(int r)

{
    red = r;
    for(int i = 0; i < szer; i++)
    {
        for (int j = 0; j < wys; j++)
        {

            czerwony = red;
            zielony = j/2.5;
            niebieski = i/2.5;
            pixel(i, j, img);
        }
    }
}

void MyWindow::RGBsliderGreen(int g)

{
    green = g;
    for(int i = 0; i < szer; i++)
    {
        for (int j = 0; j < wys; j++)
        {

            czerwony = i/2.5;
            zielony = green;
            niebieski = j/2.5;
            pixel(i, j, img);
        }
    }
}

void MyWindow::RGBsliderBlue(int b)

{
    blue = b;
    for(int i = 0; i < szer; i++)
    {
        for (int j = 0; j < wys; j++)
        {

            czerwony = i/2.5;
            zielony = j/2.5;
            niebieski = blue;
            pixel(i, j, img);
        }
    }
}

void MyWindow::HSVsliderHue(int h)

{
    hue = h;
    for (int i = 0; i < szer; i++)
    {
        for (int j = 0; j < wys; j++)
        {
            Konwersja_z_HSV_do_RGB
                (hue, (double) j / wys, (double) i / szer);
            pixel(i, j, img);
        }
    }
}

void MyWindow::HSVsliderSaturation(int s)

{
    saturation = s/(double) 1000;
    for (int i = 0; i < szer; i++)
    {
        for (int j = 0; j < wys; j++)
        {
            Konwersja_z_HSV_do_RGB
                 ((double) i/1.666, saturation, (double) j / szer);
            pixel(i, j, img);
        }
    }
}

void MyWindow::HSVsliderValue(int v)

{
    value = v/(double) 1000;
    for (int i = 0; i < szer; i++)
    {
        for (int j = 0; j < wys; j++)
        {
            Konwersja_z_HSV_do_RGB
               ((double) i/1.666, (double) j / wys, value);
            pixel(i, j, img);
        }
    }
}

void MyWindow::Konwersja_z_HSV_do_RGB

(int H, double S, double V)

{

    double r;
    double g;
    double b;
    double C = V * S;
    double H1 = (double)H / double(60);
    double X = C * (1 - abs(fmod((double)H/(double)60.0, 2) - 1));
    double m = V - C;


    if ( H1<= 1  && H1 >= 0) // 0 - 60
    {
        r = C;
        g = X;
        b = 0;
    }
        else if (H1 > 1 && H1 <= 2) //61-120
        {
         r = X;
         g = C;
         b = 0;
        }

         else if  (H1 > 2 && H1 <= 3) //121 - 180
        {
         r = 0;
         g = C;
         b = X;
        }

         else if (H1 > 3 && H1 <= 4) //181-240
        {
         r = 0;
         g = X;
         b = C;
        }

         else if (H1 > 4 && H1 <= 5) //241 - 300
        {
         r = X;
         g = 0;
         b = C;
        }

         else if (H1 > 5 && H1 <= 6) // 301 - 360
        {
         r = C;
         g = 0;
         b = X;
        }
        else
        {
        r = 0;
        g = 0;
        b = 0;
        }

    czerwony = 255 * (r + m);
    zielony =  255 * (g + m);
    niebieski = 255 * (b + m);


}
