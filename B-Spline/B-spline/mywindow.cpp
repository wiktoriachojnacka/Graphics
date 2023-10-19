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

    punkty.clear();
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


    }
}



int MyWindow::wybierzKolko(Point punktWybrania) {
    int closestIndex = -1;
    int minDistance = 6; // minimalna odległość + 1 (aby się upewnić, że poleKolkaX i poleKolkaY na pewno są mniejsze)

    for (int i = 0; i < punkty.size(); i++) {
        int poleKolkaX = abs(punkty[i].x - punktWybrania.x);
        int poleKolkaY =  abs(punkty[i].y - punktWybrania.y);

        if (poleKolkaX <= 5 && poleKolkaY <= 5 && poleKolkaX + poleKolkaY < minDistance) {
            minDistance = poleKolkaX + poleKolkaY;
            closestIndex = i;
        }
    }

    return closestIndex;
}

Point obliczPunktBspine(const Point &p1, const Point &p2, const Point &p3, const Point &p4, double t)
{
    double t2 = t * t;
    double t3 = t2 * t;

    double b0 = (1.0 - t) * (1.0 - t) * (1.0 - t) / 6.0;
    double b1 = (3.0 * t3 - 6.0 * t2 + 4.0) / 6.0;
    double b2 = (-3.0 * t3 + 3.0 * t2 + 3.0 * t + 1.0) / 6.0;
    double b3 = t3 / 6.0;
      Point wynik;

   wynik.x = b0 * p1.x + b1 * p2.x + b2 * p3.x + b3 * p4.x;
    wynik.y = b0 * p1.y + b1 * p2.y + b2 * p3.y + b3 * p4.y;

   return wynik;
}


void MyWindow::bSpline(QImage *image)
{

   for (int i = 0; i < punkty.size(); i++)
   {
        Point p = punkty[i];
        Point pc = { p.x + 5, p.y + 5 };
        Kolo(p.x, p.y, pc.x, pc.y, image);
   }


    if (punkty.size() < 4)
        return;

    for (int i = 0; i < punkty.size() - 3; i++)
    {
        Point p1 = punkty[i];
        Point p2 = punkty[i + 1];
        Point p3 = punkty[i + 2];
        Point p4 = punkty[i + 3];

        for (double t = 0.0; t <= 1.0; t += 0.01)
        {
            Point P = obliczPunktBspine(p1, p2, p3, p4, t);
            Point Q = obliczPunktBspine(p1, p2, p3, p4, t + 0.01);

            Linia(P.x, P.y, Q.x, Q.y, image);
        }
    }
}


// Funkcja (slot) wywolywana po nacisnieciu przycisku myszy (w glownym oknie)
void MyWindow::mousePressEvent(QMouseEvent *event)
{


    int x = event->x();
    int y = event->y();

    p1.x = x - poczX;
    p1.y = y - poczY;


    klikniete = true;

    if (wybierzKolko(p1) != -1)
    {
        selectedIndex = wybierzKolko(p1);
    }
    else
    {
        punkty.append(p1);
        bSpline(imgkopia);
        kopia(img, imgkopia);
        klikniete = false;
    }


    update();
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();

    p2.x = x - poczX;
    p2.y = y - poczY;


    if (selectedIndex != -1 && klikniete)
    {
        czysc();
        punkty.replace(selectedIndex,p2);
        bSpline(imgkopia);
        update();
    }

}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{

    klikniete = false;
    int x = event->x();
    int y = event->y();

    p2.x = x - poczX;
    p2.y = y - poczY;

    //draw
    kopia(img, imgkopia);
    selectedIndex = -1;

}



