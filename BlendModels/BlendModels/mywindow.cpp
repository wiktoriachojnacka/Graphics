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


poziomy.push_back(poziom(":/zdj11.jpg", "1 zdjecie"));
poziomy.push_back(poziom(":/zdj22.jpg", "2 zdjecie "));
poziomy.push_back(poziom(":/zdj33.jpg", "3 zdjecie"));
poziomy.push_back(poziom(":/zdj44.jpg", "4 zdjecie"));
poziomy.push_back(poziom(":/zdj55.jpg", "5 zdjecie"));
img = new QImage;
*img = *poziomy[poziomy.length() - 1].img;



    // Tworzymy obiekt klasy QImage, o odpowiedniej szerokosci
    // i wysokosci. Ustawiamy format bitmapy na 32 bitowe RGB
    // (0xffRRGGBB).
  // img = new QImage(szer,wys,QImage::Format_RGB32);
  // imgkopia = new QImage(szer, wys, QImage::Format_RGB32);
    setMouseTracking(true);
 //   czysc();

    // Tworzymy grupe elementow
    // Drugi parametr konstruktora to rodzic elementu
    grupa = new QGroupBox("Sterowanie",this);

    // Ustawiamy wymiary tej grupy i jej polozenie wzgledem glownego okna
    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+300));

    // Tworzymy nowy layout pionowy
    QVBoxLayout *boxLayout = new QVBoxLayout;

    // Tworzymy 4 przyciski
    // draw1Button = new QPushButton("Rysuj 1");
    // draw2Button = new QPushButton("Rysuj 2");
    cleanButton = new QPushButton("Czysc");
    exitButton = new QPushButton("Wyjscie");

    listWidget = new QListWidget();
sliderZdjec = new QSlider(Qt::Horizontal);
sliderZdjec->setRange(0,100);
comboBox = new QComboBox();

comboBox->addItem("Normal mode");
comboBox->addItem("Multiply mode");
comboBox->addItem("Lighten mode");
comboBox->addItem("Darken mode");
comboBox->addItem("Additive mode");
comboBox->addItem("Subtractive mode");

    // Dodajemy przyciski do layoutu
    // boxLayout->addWidget(draw1Button);
    // boxLayout->addWidget(draw2Button);
    boxLayout->addWidget(cleanButton);
    boxLayout->addWidget(exitButton);
boxLayout->addWidget(sliderZdjec);
boxLayout->addWidget(listWidget);
boxLayout->addWidget(comboBox);
    // Dodajemy layout do grupy
    grupa->setLayout(boxLayout);


    // Laczymy sygnal emitowany po nacisnieciu przycisku "Wyjscie"
    // ze slotem quit(). qApp to globalny wskaznik reprezentujacy aplikacje
    connect(exitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    // Laczymy sygnaly emitowane po nacisnieciu przyciskow z odpowiednimi slotami
    connect(cleanButton,SIGNAL(clicked()),this,SLOT(slot_czysc()));
connect(sliderZdjec,SIGNAL(valueChanged(int)),this,SLOT(sliderZdjecia(int)));
connect(listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(listWidgetZdjec(int)));
connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxZdjec(int)));


dodaj();


listWidget->setCurrentRow(0);
    // connect(draw1Button,SIGNAL(clicked()),this,SLOT(slot_rysuj1()));

    //  connect(draw2Button,SIGNAL(clicked()),this,SLOT(slot_rysuj2()));


}

void MyWindow::sliderZdjecia(int i)
{

    float alfa = (float) i / 100.0;

    poziomy[listWidget->currentRow()].alfa = alfa;

    for (int j = poziomy.length() - 1; j >= 0; j--)
    {

    BlenModels(j);

    }
    update();

}

void MyWindow::listWidgetZdjec(int i)
{

    sliderZdjec->setValue(poziomy[i].alfa * 100);
    comboBox->setCurrentIndex(poziomy[i].tryb);
}

void MyWindow::comboBoxZdjec(int i)
{

    poziomy [listWidget->currentRow()].tryb = i;

    for (int j = poziomy.length() - 1; j >= 0; j--)
    {
    BlenModels(j);
    update();
    }

}

/*poziom::poziom()
{
    //
}*/

poziom::poziom(QString sciezka, QString nazwa)

{
    img = new QImage(sciezka);
    this->nazwa = nazwa;
}


void MyWindow::dodaj()

{
    for(int i = 0; i <poziomy.length(); i++)

    listWidget -> addItem(poziomy[i].nazwa) ;
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
        ptr[4 * x + 2] = 147 ;

        update();
    }
}




void MyWindow::BlenModels(int poziom)

{

    QSize size = poziomy[0].img->size();

    unsigned char*ptr = poziomy[poziom].img-> bits();
    unsigned char *ptr1 = img->bits();

    int mode = poziomy[poziom].tryb;
    float alfa = poziomy[poziom].alfa;


    for (int i = 0; i < size.height() * size.width(); i++)
    {

     if (mode == 0) // Normal mode

     {
            //kolorR    = αR   ∗ kolor_pierwszoplanowyR + (1 − αR)   ∗ kolor_tłaR
            ptr1 [i * 4]= alfa * (float)ptr [i * 4]     + (1 - alfa) * ptr1 [i * 4];        //R
            ptr1 [i * 4 + 1]= alfa * (float)ptr [i * 4 + 1] +(1 - alfa) * ptr1 [i * 4 +1];  //G
            ptr1 [i * 4 + 2]=alfa * (float)ptr [i * 4  + 2] +(1 - alfa) * ptr1 [i * 4 +2];  //B

     }
     else if (mode == 1) // Multiply mode

     {
            ptr1 [i * 4]= alfa * (float)(ptr [i * 4] * ptr1 [i * 4] >> 8) + (1 - alfa) * ptr1 [i * 4];
            ptr1 [i * 4 + 1]= alfa * (float)(ptr [i * 4 + 1] * ptr1 [i * 4 + 1] >>8) + (1 - alfa) * ptr1 [i * 4 +1];
            ptr1 [i * 4 + 2]=alfa * (float)(ptr [i * 4 + 2] * ptr1 [i * 4 + 2] >>8) + (1 - alfa) * ptr1 [i * 4 +2];

     }
     else if (mode == 2) // Lighten mode

     {

            ptr1 [i * 4]= alfa * qMax((float)ptr [i * 4], (float)ptr1 [i * 4]) + (1 - alfa) * ptr1[i * 4];
            ptr1 [i * 4 + 1]= alfa * qMax((float)ptr [i * 4 + 1], (float)ptr1 [i * 4 + 1]) + (1 - alfa) * ptr1 [i * 4 +1];
            ptr1 [i * 4 + 2]= alfa * qMax((float)ptr [i * 4 + 2],(float) ptr1 [i * 4 + 2]) + (1 - alfa) * ptr1 [i * 4 +2];

     }
     else if (mode == 3) // Darken mode

     {
            ptr1 [i * 4]= alfa * qMin((float)ptr[i * 4], (float)ptr1 [i * 4]) + (1 - alfa) * ptr1[i * 4];
            ptr1 [i * 4 + 1]= alfa * qMin((float)ptr [i * 4 + 1], (float)ptr1 [i * 4 + 1]) + (1 - alfa) * ptr1 [i * 4 +1];
            ptr1 [i * 4 + 2]= alfa * qMin((float)ptr [i * 4 + 2], (float)ptr1 [i * 4 + 2]) + (1 - alfa) * ptr1 [i * 4 +2];

     }
     else if (mode == 4) // Additive mode

     {
            ptr1 [i * 4]= alfa * qMin(((float)(ptr [i * 4] + ptr1 [i * 4])), (float)255)+ (1 - alfa) * ptr1[i * 4];
            ptr1 [i * 4 + 1]= alfa * qMin((float)(alfa * ((float)(ptr [i * 4 + 1] + ptr1 [i * 4 + 1]))), (float)255)+ (1 - alfa) * ptr1 [i * 4 +1];
            ptr1 [i * 4 + 2]= alfa * qMin((float)(alfa * ((float)(ptr [i * 4 + 2] + ptr1 [i * 4 + 2]))), (float)255)+ (1 - alfa) * ptr1 [i * 4 +2];

     }
     else if (mode == 5) // Subtractive mode

     {
            ptr1 [i * 4]= alfa * qMax((float)(ptr1 [i * 4] + ptr [i * 4] - 255 ), (float)0)+ (1 - alfa) * ptr1 [i * 4];
            ptr1 [i * 4 + 1]= alfa * qMax((float)(ptr1 [i * 4 + 1] + ptr [i * 4 + 1] - 255 ), (float)0)+ (1 - alfa) * ptr1 [i * 4 +1];
            ptr1 [i * 4 + 2]=  alfa * qMax((float)(ptr1 [i * 4 + 2] + ptr [i * 4 + 2] - 255 ), (float)0)+ (1 - alfa) * ptr1 [i * 4 +2];

     }


    }
}
