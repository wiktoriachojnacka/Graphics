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
    img2 = new QImage(":/kotek.jpg");
    setMouseTracking(true);
    czysc();
    on_obrazButton_clicked();

    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+700));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski
    // draw1Button = new QPushButton("Rysuj 1");
    // draw2Button = new QPushButton("Rysuj 2");
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");
erozjaButton = new QPushButton("Erozja");
dylatacjaButton = new QPushButton("Dylatacja");
otwarcieButton = new QPushButton("Otwarcie");
zamkniecieButton = new QPushButton("Zamkniecie");
obrazBinarnyButton = new QPushButton("Resetuj obraz");

mooreCheckBox= new QCheckBox("moore");


    // Dodajemy przyciski do layoutu
    // boxLayout->addWidget(draw1Button);
    // boxLayout->addWidget(draw2Button);
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);
    boxLayout->addWidget(mooreCheckBox);
boxLayout->addWidget(erozjaButton);
boxLayout->addWidget(dylatacjaButton);
boxLayout->addWidget(otwarcieButton);
boxLayout->addWidget(zamkniecieButton);
boxLayout->addWidget(obrazBinarnyButton);

    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);


    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny ptraznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));

     connect(erozjaButton,SIGNAL(clicked()),this,SLOT(slot_Erozja()));
     connect(dylatacjaButton,SIGNAL(clicked()),this,SLOT(slot_Dylatacja()));
     connect(otwarcieButton,SIGNAL(clicked()),this,SLOT(otwarcie()));
     connect(zamkniecieButton,SIGNAL(clicked()),this,SLOT(zamkniecie()));
     connect(obrazBinarnyButton,SIGNAL(clicked()),this,SLOT(on_obrazButton_clicked()));
    connect(mooreCheckBox,SIGNAL(stateChanged(int)),this,SLOT(slot_Moore(int)));
     //connect(draw1Button,SIGNAL(clicked()),this,SLOT(slot_rysuj1()));
    //  connect(draw2Button,SIGNAL(clicked()),this,SLOT(slot_rysuj2()));


}



// Definicja destruktora
MyWindow::~MyWindow()
{
    delete img;
    delete imgkopia;
}


void MyWindow::slot_Moore(int i){

    if (i==Qt::Checked){

        moore=true;
    }
    else {
        moore=false;
    }
}


void MyWindow::slot_Erozja(){

    Erozja(img);

    update();

}

void MyWindow::slot_Dylatacja(){

    Dylatacja(img);

    update();

}

void MyWindow::otwarcie(){

     Erozja(img);
     Dylatacja(img);

    update();

}

void MyWindow::zamkniecie(){
    Erozja(img);
    Dylatacja(img);

 update();


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
    // ptraznik za pomoca, ktorego bedziemy modyfikowac obraz
    unsigned char *ptr, *ptrkopia;

    // Funkcja "bits()" zwraca ptraznik do pierwszego piksela danych
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

void MyWindow::pixel(int x, int y, QImage *image, bool isWhite)

{
    if ( x>=0 && y>=0 &&  y<wys && x<szer)
    {
        unsigned char *ptr;

        ptr=image->scanLine(y);

        if(isWhite){
            ptr[4 * x] = 255;
            ptr[4 * x + 1] = 255;
            ptr[4 * x + 2] = 255;
        }
        else{
            ptr[4 * x] = 0;
            ptr[4 * x + 1] = 0;
            ptr[4 * x + 2] = 0;
        }
        update();
    }
}

void MyWindow::sprawdzPixelUstawBialy(int x, int y, const unsigned char *ptr, bool &isWhite, int x_off, int y_off) {
    if (x + x_off > 0 && x + x_off < 600 && y + y_off > 0 && y + y_off < 600) {
        int r = ptr[600 * 4 * (y + y_off) + 4 * (x + x_off) + 2];
        int g = ptr[600 * 4 * (y + y_off) + 4 * (x + x_off) + 1];
        int b = ptr[600 * 4 * (y + y_off) + 4 * (x + x_off)];
        if (r == 255 && g == 255 && b == 255)
            isWhite = true;
    }
}

void MyWindow::Erozja(QImage *img) {
    bool isWhite = true;
    QImage *imgtemp = new QImage(600, 600, QImage::Format_RGB32);
    int r, g, b;

    for (int y = 0; y < 600; y++) {
        for (int x = 0; x < 600; x++) {
            if (moore == false) {
                unsigned char *ptr = img->bits();

                sprawdzPixelUstawBialy(x, y, ptr, isWhite, -1, 0);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 1, 0);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 0, -1);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 0, 1);

                if (isWhite == true)
                    pixel(x, y, imgtemp, isWhite);

                isWhite = false;
            } else {
                unsigned char *ptr = img->bits();

                sprawdzPixelUstawBialy(x, y, ptr, isWhite, -1, 0);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 1, 0);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 0, -1);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 0, 1);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, -1, -1);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 1, 1);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, 1, -1);
                sprawdzPixelUstawBialy(x, y, ptr, isWhite, -1, 1);

                if (isWhite == true)
                    pixel(x, y, imgtemp, isWhite);

                isWhite = false;
            }
        }
    }

    unsigned char *in, *out;
    in = imgtemp->bits();
    out = img->bits();

    for (int y = 0; y < 600; y++)
    {
        for (int x = 0; x < 600; x++) {
            out[600 * 4 * y + 4 * x] = in[600 * 4 * y + 4 * x];
            out[600 * 4 * y + 4 * x + 1] = in[600 * 4 * y + 4 * x + 1];
            out[600 * 4 * y + 4 * x + 2] = in[600 * 4 * y + 4 * x + 2];
        }
    }

    update();
}

void MyWindow::sprawdzUstawNieBialy(int x, int y, const unsigned char *ptr, bool &isWhite, int x_off, int y_off)
{
    if (x + x_off > 0 && x + x_off < 600 && y + y_off > 0 && y + y_off < 600) {
        int r = ptr[600 * 4 * (y + y_off) + 4 * (x + x_off) + 2];
        int g = ptr[600 * 4 * (y + y_off) + 4 * (x + x_off) + 1];
        int b = ptr[600 * 4 * (y + y_off) + 4 * (x + x_off)];
        if (r != 255 && g != 255 && b != 255)
            isWhite = false;
    }
}



void MyWindow::Dylatacja(QImage *img)
{
    bool isWhite = true;

    QImage *imgtemp = new QImage(600, 600, QImage::Format_RGB32);

    int r, g, b;

    for (int y = 0; y < 600; y++) {
        for (int x = 0; x < 600; x++) {
            if (!moore) {
                unsigned char *ptr = img->bits();

                sprawdzUstawNieBialy(x, y, ptr, isWhite, -1, 0);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 1, 0);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 0, -1);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 0, 1);

                if (isWhite)
                    pixel(x, y, imgtemp, isWhite);
                else
                    pixel(x, y, imgtemp, isWhite);

                isWhite = true;
            } else {
                unsigned char *ptr = img->bits();

                sprawdzUstawNieBialy(x, y, ptr, isWhite, -1, 0);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 1, 0);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 0, -1);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 0, 1);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, -1, -1);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 1, 1);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, 1, -1);
                sprawdzUstawNieBialy(x, y, ptr, isWhite, -1, 1);

                if (isWhite)
                    pixel(x, y, imgtemp, isWhite);
                else
                    pixel(x, y, imgtemp, isWhite);

                isWhite = true;
            }
        }
    }

    unsigned char *in, *out;
    in = imgtemp->bits();
    out = img->bits();

    for (int y = 0; y < 600; y++) {
        for (int x = 0; x < 600; x++) {

            out[600 * 4 * y + 4 * x] = in[600 * 4 * y + 4 * x];
            out[600 * 4 * y + 4 * x + 1] = in[600 * 4 * y + 4 * x + 1];
            out[600 * 4 * y + 4 * x + 2] = in[600 * 4 * y + 4 * x + 2];
        }
    }

    update();
}



void MyWindow::on_obrazButton_clicked()
{


        *img = img2->scaled(600, 600);

        unsigned char *ptr;

        for (int y = 0; y < 600; y++)
        {
            ptr = img->scanLine(y);

            for (int x = 0; x < 600; x++)
            {
                int r = ptr[4 * x];
                int g = ptr[4 * x + 1];
                int b = ptr[4 * x + 2];

                bool isWhite = (r + g + b) / 3 > 128;
                pixel(x, y, img, isWhite);
            }
        }

}

