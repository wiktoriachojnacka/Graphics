#include "mywindow.h"


MyWindow::MyWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Rysowanie lini w Qt");

    //Zmieniamy rozmiar okna
    resize(800,700);

    // Ustawiamy wymiary obrazka i wspolrzedne jego
    // lewego gornego naroznika ramki
    // (wzgledem glownego okna)
    szer = 600;
    wys = 600;
    startX = 25;
    startY = 25;

    img = new QImage(szer, wys, QImage::Format_RGB32);
    grupa = new QGroupBox("Sterowanie",this);

    grupa->setGeometry(QRect(startX+szer +startX,startY ,800-szer-2*startX,startY +300));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    grupa->setLayout(boxLayout);


    sliderPrzesuniecie1 = new QSlider(Qt::Horizontal);
    sliderPrzesuniecie1 -> setRange(-300,200);
    sliderPrzesuniecie2 = new QSlider(Qt::Horizontal);
    sliderPrzesuniecie2 -> setRange(-300,200);
    sliderPrzesuniecie3 = new QSlider(Qt::Horizontal);
    sliderPrzesuniecie3 -> setRange(-300,200);

    sliderSkalowanie1 = new QSlider(Qt::Horizontal);
    sliderSkalowanie1 -> setRange(-300,300);
    sliderSkalowanie2 = new QSlider(Qt::Horizontal);
    sliderSkalowanie2 -> setRange(-300,300);
    sliderSkalowanie3 = new QSlider(Qt::Horizontal);
    sliderSkalowanie3 -> setRange(-300,300);

    sliderObrot1 = new QSlider(Qt::Horizontal);
    sliderObrot1 -> setRange(-300,300);
    sliderObrot2 = new QSlider(Qt::Horizontal);
    sliderObrot2 -> setRange(-300,300);
    sliderObrot3 = new QSlider(Qt::Horizontal);
    sliderObrot3 -> setRange(-300,300);

    label1 = new QLabel("Przesuniecie");
    boxLayout->addWidget(label1);

    boxLayout-> addWidget(sliderPrzesuniecie1);
    boxLayout-> addWidget(sliderPrzesuniecie2);
    boxLayout-> addWidget(sliderPrzesuniecie3);

    label2 = new QLabel("Skalowanie");
    boxLayout->addWidget(label2 );

    boxLayout-> addWidget(sliderSkalowanie1);
    boxLayout-> addWidget(sliderSkalowanie2);
    boxLayout-> addWidget(sliderSkalowanie3);


    label3 = new QLabel("Obrot");
    boxLayout->addWidget(label3);


    boxLayout-> addWidget(sliderObrot1);
    boxLayout-> addWidget(sliderObrot2);
    boxLayout-> addWidget(sliderObrot3);

    connect(sliderPrzesuniecie1, SIGNAL(valueChanged(int)), this, SLOT(ustawTranslacje1(int)));
    connect(sliderPrzesuniecie2, SIGNAL(valueChanged(int)), this, SLOT(ustawTranslacje2(int)));
    connect(sliderPrzesuniecie3, SIGNAL(valueChanged(int)), this, SLOT(ustawTranslacje3(int)));

    connect(sliderSkalowanie1, SIGNAL(valueChanged(int)), this, SLOT(ustawSkalowanie1(int)));
    connect(sliderSkalowanie2, SIGNAL(valueChanged(int)), this, SLOT(ustawSkalowanie2(int)));
    connect(sliderSkalowanie3, SIGNAL(valueChanged(int)), this, SLOT(ustawSkalowanie3(int)));

    connect(sliderObrot1, SIGNAL(valueChanged(int)), this, SLOT(ustawRotacje1(int)));
    connect(sliderObrot2, SIGNAL(valueChanged(int)), this, SLOT(ustawRotacje2(int)));
    connect(sliderObrot3, SIGNAL(valueChanged(int)), this, SLOT(ustawRotacje3(int)));

    zrobSzescian();
    update();

}


MyWindow::~MyWindow() { delete img; }
void MyWindow::paintEvent(QPaintEvent*) { QPainter p(this); p.drawImage(startX, startY, *img); }
void MyWindow::czysc() {
    // Wskaznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr;

    // Funkcja "bits()" zwraca wskaznik do pierwszego piksela danych
    ptr = img->bits();


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

        }
    }
}

void MyWindow::drawPixel(int x, int y) {
    {
        if ( x>=0 && y>=0 &&  y<wys && x<szer)
        {
            unsigned char *ptr;

            ptr=img->scanLine(y);

            ptr[4 * x] = 255;
            ptr[4 * x + 1] = 20;
            ptr[4 * x + 2] = 147;

            update();
        }
    }

}

void MyWindow::ustawTranslacje1(int value)

{
    PrzesuniecieX = value;
    zrobSzescian();
}

void MyWindow::ustawTranslacje2(int value)

{
    PrzesuniecieY = value;
    zrobSzescian();
}

void MyWindow::ustawTranslacje3(int value)

{
    PrzesuniecieZ = value;
    zrobSzescian();
}

void MyWindow::ustawSkalowanie1(int value)

{
    skalowanieX = value/100.0;
    zrobSzescian();
}

void MyWindow::ustawSkalowanie2(int value)
{
    skalowanieY = value/100.0;
    zrobSzescian();
}

void MyWindow::ustawSkalowanie3(int value)
{
    skalowanieZ = value/100.0;
    zrobSzescian();
}

void MyWindow::ustawRotacje1(int value)
{
    obrotX = value;
    zrobSzescian();
}

void MyWindow::ustawRotacje2(int value)
{
    obrotY = value;
    zrobSzescian();
}

void MyWindow::ustawRotacje3(int value)
{
    obrotZ = value;
    zrobSzescian();
}


void MyWindow::Linia(int x1, int y1, int x2,  int y2)

{
    double a, b;

    int x, y;

    if (x1 == x2)
    {
        x = x1;
        if (y1 < y2)
        {
            for (y = y1; y != y2; y += 1)
                drawPixel(x, y);
        }
        else
        {
            for (y = y1; y != y2; y -= 1)
                drawPixel(x, y);
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
                    drawPixel(x, (int)y + 0.5);
                }
            }
            else
            {
                for (x = x1; x != x2; x -= 1)
                {
                    y = a * x + b;
                    drawPixel (x, (int)y + 0.5);
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
                    drawPixel(x, (int)y + 0.5);
                }
            }
            else

            {
                for (y = y1; y != y2; y -= 1)
                {
                    x = (y - b) / a;
                    drawPixel(x, (int)y + 0.5);
                }
            }
        }

    }

    update();
}

void MyWindow::zrobSzescian() {

    int liczbaScian = 6;
    czysc();

   operacjeMacierzy transformacjaMacierzy =operacjeMacierzy(1);
    transformacjaMacierzy = transformacjaMacierzy
                           .macierz(operacjeMacierzy::rzutowaniePerspektywiczne())
                           .macierz(operacjeMacierzy::obrot(obrotX, obrotY, obrotZ))
                           .macierz(operacjeMacierzy::skalowanie(skalowanieX, skalowanieY, skalowanieZ))
                           .macierz(operacjeMacierzy::przesuniecie(PrzesuniecieX, PrzesuniecieY, PrzesuniecieZ));

    szescian.ustaw();

    for (int i = 0; i < liczbaScian; ++i) {

        BokiSzescianu S = szescian.boki[i];

        Wspolrzedna wierzcholek1 = transformacjaMacierzy.macierz(*S.wierzcholek1);
        Wspolrzedna wierzcholek2 =transformacjaMacierzy.macierz(*S.wierzcholek2);
        Wspolrzedna wierzcholek3 = transformacjaMacierzy.macierz(*S.wierzcholek3);
        Wspolrzedna wierzcholek4 = transformacjaMacierzy.macierz(*S.wierzcholek4);

        Linia(wierzcholek1.x + szer / 2, wierzcholek1.y + wys / 2, wierzcholek2.x + szer / 2, wierzcholek2.y + wys / 2);
        Linia(wierzcholek2.x + szer / 2, wierzcholek2.y + wys / 2, wierzcholek3.x + szer / 2, wierzcholek3.y + wys / 2);
        Linia(wierzcholek3.x + szer / 2, wierzcholek3.y + wys / 2, wierzcholek4.x + szer / 2, wierzcholek4.y + wys / 2);
        Linia(wierzcholek4.x + szer / 2, wierzcholek4.y + wys / 2, wierzcholek1.x + szer / 2, wierzcholek1.y + wys / 2);
    }

    update();
}

