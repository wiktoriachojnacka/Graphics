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
    img2 = new QImage(":/kotekk.png");
    szer2 = img2->width();
    wys2 = img2->height();
    setMouseTracking(true);
    rysuj();

    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
  //  grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+100));

    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY +500));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    sliderTranslacja1 = new QSlider(Qt::Horizontal);
    sliderTranslacja1 -> setRange(-300,200);
    sliderTranslacja2 = new QSlider(Qt::Horizontal);
    sliderTranslacja2 -> setRange(-300,200);


    sliderSkalowanie1 = new QSlider(Qt::Horizontal);
    sliderSkalowanie1 -> setRange(-300,300);
    sliderSkalowanie2 = new QSlider(Qt::Horizontal);
    sliderSkalowanie2 -> setRange(-300,300);

    sliderPochylenie1 = new QSlider(Qt::Horizontal);
    sliderPochylenie1 -> setRange(-300,300);
    sliderPochylenie2 = new QSlider(Qt::Horizontal);
    sliderPochylenie2 -> setRange(-300,300);


    sliderObrot = new QSlider(Qt::Horizontal);
    sliderObrot -> setRange(-300,300);

;

    label1 = new QLabel("Translacja");
    boxLayout->addWidget(label1);
    boxLayout-> addWidget(sliderTranslacja1);
    boxLayout-> addWidget(sliderTranslacja2);


    label2 = new QLabel("Pochylenie");
    boxLayout->addWidget(label2 );
    boxLayout-> addWidget(sliderPochylenie1);
    boxLayout-> addWidget(sliderPochylenie2);

    label3 = new QLabel("Skalowanie");
    boxLayout->addWidget(label3 );
    boxLayout-> addWidget(sliderSkalowanie1);
    boxLayout-> addWidget(sliderSkalowanie2);



    label4 = new QLabel("Obr");
    boxLayout->addWidget(label4);



    boxLayout-> addWidget(sliderObrot);



    connect(sliderTranslacja1, SIGNAL(valueChanged(int)), this,  SLOT(translacjaSlider1(int)));
    connect(sliderTranslacja2, SIGNAL(valueChanged(int)), this,  SLOT(translacjaSlider2(int)));


    connect(sliderSkalowanie1, SIGNAL(valueChanged(int)), this,  SLOT(skalowanieSlider1(int)));
    connect(sliderSkalowanie2, SIGNAL(valueChanged(int)), this,  SLOT(skalowanieSlider2(int)));

    connect(sliderPochylenie1, SIGNAL(valueChanged(int)), this,  SLOT(pochylenieSlider2(int)));
    connect(sliderPochylenie2, SIGNAL(valueChanged(int)), this,  SLOT(pochylenieSlider2(int)));


    connect(sliderObrot, SIGNAL(valueChanged(int)), this,  SLOT(obrotSlider(int)));



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

void MyWindow::translacjaSlider1(int value)

{
    transX = value; rysuj();
}
void MyWindow::translacjaSlider2(int value)

{
    transY = value; rysuj();
}
void MyWindow::obrotSlider(int value)

{
    alfa = value * 3.141592 /60.0; rysuj();
}
void MyWindow::skalowanieSlider1(int value)

{
    skalowanieX = value/100.0; rysuj();
}
void MyWindow::skalowanieSlider2(int value)

{
    skalowanieY = value / 100.0; rysuj();
}
void MyWindow::pochylenieSlider1(int value)

{
    pochylenieX  = value / 100.0; rysuj();
}
void MyWindow::pochylenieSlider2(int value)

{
    pochylenieY = value / 100.0; rysuj();
}


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


void MyWindow::rysuj()
{
    unsigned char *ptr = img->bits();

    czysc();

    for (int i = -600; i < 600; i++)
    {
        for (int j = -600; j < 600; j++)
        {
            int moveX = i + transX, moveY = j + transY; // Translacja
            if (moveX >= 0 && moveX < szer && moveY >= 0 && moveY < wys)
            {
                // Obrot
                float x0 = i * cos(alfa) - j * sin(alfa);
                float y0 = i * sin(alfa) + j * cos(alfa);

                // Pochylenie
                float x1 = (pochylenieX  * szer2) / 60;
                float y1 = (pochylenieY * wys2) / 100;
                float x2 = (x0 + x1 + (y0 + y1) * pochylenieX );
                float y2 = (y0 + y1 + (x0 + x1) * pochylenieY);

                // Skalowanie
                x2 /= skalowanieX;
                y2 /= skalowanieY;

                if (x2 >= 0 && x2 < szer2 && y2 >= 0 && y2 < wys2)
                {

                    unsigned char *ptr2 = img2->bits();
                    int xx = int(x2), yy = int(y2);
                    int r = ptr2[szer2 * 4 * yy + 4 * xx + 2];
                    int g = ptr2[szer2 * 4 * yy + 4 * xx + 1];
                    int b = ptr2[szer2 * 4 * yy + 4 * xx];


                    unsigned char *ptr3 = img->bits();
                    int pixelIndex = szer * 4 * moveY + 4 * moveX;
                    ptr3[pixelIndex + 2] = r;  // R
                    ptr3[pixelIndex + 1] = g;  // G
                    ptr3[pixelIndex] = b;      // B
                }
            }
        }
    }

    update(); // Update the display
}


