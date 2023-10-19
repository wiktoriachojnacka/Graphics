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

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+100));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski
    // draw1Button = new QPushButton("Rysuj 1");
    // draw2Button = new QPushButton("Rysuj 2");
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");

    // Dodajemy przyciski do layoutu
    // boxLayout->addWidget(draw1Button);
    // boxLayout->addWidget(draw2Button);
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);

    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);


    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));

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
    wsp.clear();
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

        ptr[4 * x] = 255;
        ptr[4 * x + 1] = 20;
        ptr[4 * x + 2] = 147;

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

void MyWindow::scanLine(QImage* image)
{
    Bok bok;
    QVector<Bok> boki;

    for (int i = 0; (int)wsp.size() - 1 > i; i++)
    {

        bok.min = wsp.at (i);
        bok.max = wsp.at (i + 1);
        boki.push_back(bok);
    }


    bok.min = wsp.at((int)wsp.size() - 1);
    bok.max = wsp.at(0);
    boki.push_back(bok);

    int ymin = minY();
    int ymax = maxY();

   // boki.push_back(bok);

    for (int y = ymin; y <= ymax; y++)
    {
        QVector<Wspolrzedna> przeciecia = przeciecieLinii(y, boki);
        std::sort(przeciecia.begin(), przeciecia.end(), [](const Wspolrzedna& p, const Wspolrzedna& q) { return p.x < q.x; });

        if ((int)przeciecia.size() >= 2)
        {
            for (int i = 0;  (int)przeciecia.size() - 1 > i; i += 2)
            {
                Linia(przeciecia.at(i).x, y, przeciecia.at(i + 1).x, y, image);
            }
        }
    }
}

int MyWindow::minY()

{
    if ((int) wsp.size() > 0)
    {
        int y =wsp.at(0).y;

        for (int i=0;  (int) wsp.size() > i; i++)

        {
         if (y > wsp.at(i).y)
          y = wsp.at(i).y;
        }

        return y;
    }

    else
        return -1 ;
}

int MyWindow::maxY()

{
    if ((int) wsp.size() > 0)
    {
        int y =wsp.at(0).y;

        for (int i=0;  (int) wsp.size() > i; i++)

        {
         if (y < wsp.at(i).y)
          y = wsp.at(i).y;
        }

        return y;
    }

    else
        return -1;
}


QVector<Wspolrzedna> MyWindow::przeciecieLinii(int y, QVector<Bok> boki)
{
    Wspolrzedna p;
    QVector<Wspolrzedna> lista;

    for (int i=0; i<(int)boki.size(); i++)
    {

        bool czyBokAktywny = (boki.at(i).min.y <= y && boki.at(i).max.y > y) ||
                          (boki.at(i).min.y > y && boki.at(i).max.y <= y);

        bool czyWierzcholek = (boki.at(i).max.y - boki.at(i).min.y) != 0;

        if ( czyBokAktywny && czyWierzcholek)
        {

            float x_diff = (float)(boki.at(i).max.x - boki.at(i).min.x);
            float y_diff = (float)(boki.at(i).max.y - boki.at(i).min.y);

            p.x = boki.at(i).min.x + (y - boki.at(i).min.y) * (x_diff / y_diff);
            p.y = y;

            lista.push_back(p);
        }
    }
    return lista;
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

 //   x1 = x;
 //   y1 = y;

    Wspolrzedna p;
    p.x = x;
    p.y = y;

    wsp.push_back(p);

    if (!isScanline)
    {
       if (wsp.size() > 2 && (abs(x - wsp[0].x) <= 20 && abs(y - wsp[0].y) <= 20))

        {
            isScanline = true;
            wsp.pop_back();
            wsp.push_back(wsp.at(0));
        }
    }

    for (int i = 0; i<(int) wsp.size()-1; i++)

    {
        Linia (wsp.at(i).x, wsp.at(i).y, wsp.at(i + 1).x, wsp.at(i + 1).y , imgkopia);

        kopia (img, imgkopia);
    }

    if (isScanline)

    {
        scanLine (imgkopia);
        kopia (img, imgkopia);

        isScanline = false;
        wsp.clear();
    }
}

