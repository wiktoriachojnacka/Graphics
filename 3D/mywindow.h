// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji

#include <QApplication>

// Dolaczamy plik naglowkowy klasy QWidget,
// Jest to klasa bazowa wszystkich elementow GUI
#include <QWidget>

// Dolaczamy plik naglowkowy klasy QPushButton
// (standardowy przycisk)
#include <QPushButton>

// Dolaczamy plik naglowkowy klasy QGroupBox
// (do grupowania komponentow GUI)
#include <QGroupBox>

// QPainter to klasa umozliwiajaca niskopoziomowe rysowanie
// na elementach GUI
#include <QPainter>

// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,
// Bedziemy jej uzywali do tworzenia i przechowywania
// naszych rysunkow
#include <QImage>

// QMouseEvent to klasa obslugujaca zdarzenia zwiazane z myszka
// klikniecia, ruch myszka itp.
#include <QMouseEvent>
#include <QtWidgets>
#include <QSlider>
#include <QtCore>
#include <QtMath>
#include <QSlider>
#include <QLabel>
#include <QVector>

using namespace std;

struct Wspolrzedna {

    double x, y, z, w;

    Wspolrzedna (double x = 0, double y = 0, double z = 0, double w = 0)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

      void normalizuj() {
        if (w != 0)
        {
              x/=w;
            y/=w;
              z/=w;
        }
    }
};


struct operacjeMacierzy

{
    double tab[4][4];

    operacjeMacierzy(double a[4][4])
    {
        int index = 0;

        for (int i = 0; i < 4; ++i)
        {
              for (int j = 0; j < 4; ++j)
              {
                  tab[i][j] = a[index / 4][index % 4];

                  index++;
              }
        }
    }

    operacjeMacierzy(int a)

    {
        for (int i = 0; i < 4; ++i)
        {
              for (int j = 0; j < 4; ++j)
              {
                  if (i == j)

                      tab[i][j] = a;

                  else

                      tab[i][j] = 0.0;
              }
        }
    }

    static operacjeMacierzy rzutowaniePerspektywiczne(double d = 450)
    {
        double a[4][4] =
            {
                {1, 0, 0, 0},
                {0, 1, 0, 0,},
                {0, 0, 1, 0},
                {0, 0, 1 / d, 1}
            };

        return operacjeMacierzy(a);
    }

    static operacjeMacierzy przesuniecie (double x, double y, double z)
    {
        double a[4][4] =
        {

          {1, 0, 0, x},
          {0, 1, 0, y},
          {0, 0, 1, z},
          {0, 0, 0, 1}

        };

        return operacjeMacierzy(a);
    }

    static operacjeMacierzy skalowanie(double x, double y, double z)
    {

        double a[4][4] =
        {
         {x, 0, 0, 0},
         {0, y, 0, 0},
         {0, 0, z, 0},
         {0, 0, 0, 1}
        };

        return operacjeMacierzy(a);
    }

    static operacjeMacierzy obrotX(double x)
    {
        x = x * M_PI / 180;

  //      operacjeMacierzy Macierz = operacjeMacierzy(1);

        double a[4][4] =
            {
                {1, 0, 0, 0},
                {0, cos(x), -sin(x), 0},
                {0, sin(x), cos(x), 0},
                {0, 0, 0, 1}
            };

    //   Macierz = Macierz.macierz(operacjeMacierzy(a));

        return  operacjeMacierzy(a);
    }

    static operacjeMacierzy obrotY(double y)
    {
        y = y * M_PI / 180;

        operacjeMacierzy Macierz = operacjeMacierzy(1);

        double b[4][4] =
            {
                {cos(y), 0, sin(y), 0},
                {0, 1, 0, 0},
                {-sin(y), 0, cos(y), 0},
                {0, 0, 0, 1}
            };

       Macierz = Macierz.macierz(operacjeMacierzy(b));

        return Macierz;
    }

    static operacjeMacierzy obrotZ(double z)
    {
        z = z * M_PI / 180;

        operacjeMacierzy Macierz = operacjeMacierzy(1);

        double c[4][4] =
            {
                {cos(z), -sin(z), 0, 0},
                {sin(z), cos(z), 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            };

        Macierz = Macierz.macierz(operacjeMacierzy(c));

        return Macierz;
    }

    static operacjeMacierzy obrot(double x, double y, double z)
    {
        operacjeMacierzy Macierz = operacjeMacierzy(1);
        Macierz = Macierz.macierz(obrotX(x));
        Macierz = Macierz.macierz(obrotY(y));
        Macierz = Macierz.macierz(obrotZ(z));

        return Macierz;
    }

    Wspolrzedna macierz(Wspolrzedna Punkt2) {

        Wspolrzedna Punkt1 = Wspolrzedna();
        operacjeMacierzy Macierz = *this;

             Punkt1.x = Macierz.tab[0][0] * Punkt2.x;
             Punkt1.x += Macierz.tab[0][1] * Punkt2.y;
             Punkt1.x += Macierz.tab[0][2] * Punkt2.z;
             Punkt1.x += Macierz.tab[0][3] * Punkt2.w;

             Punkt1.y = Macierz.tab[1][0] * Punkt2.x;
             Punkt1.y += Macierz.tab[1][1] * Punkt2.y;
             Punkt1.y += Macierz.tab[1][2] * Punkt2.z;
             Punkt1.y += Macierz.tab[1][3] * Punkt2.w;

             Punkt1.z = Macierz.tab[2][0] * Punkt2.x;
             Punkt1.z += Macierz.tab[2][1] * Punkt2.y;
             Punkt1.z += Macierz.tab[2][2] * Punkt2.z;
             Punkt1.z += Macierz.tab[2][3] * Punkt2.w;

             Punkt1.w = Macierz.tab[3][0] * Punkt2.x;
             Punkt1.w += Macierz.tab[3][1] * Punkt2.y;
             Punkt1.w += Macierz.tab[3][2] * Punkt2.z;
             Punkt1.w += Macierz.tab[3][3] * Punkt2.w;

        Punkt1.normalizuj();

        return Punkt1;
    }

    operacjeMacierzy macierz(operacjeMacierzy pomocniczaMacierz)

    {
        operacjeMacierzy nowaMacierz = operacjeMacierzy(0);
        operacjeMacierzy kopiaMacierzy = *this;


        for (int i = 0; i < 4; ++i)
        {

          for (int j = 0; j < 4; ++j)
          {
             for (int k = 0; k < 4; ++k)

             nowaMacierz.tab[i][j] += kopiaMacierzy.tab[i][k] * pomocniczaMacierz.tab[k][j];
          }

        }

        return nowaMacierz;
    }
};

struct BokiSzescianu {

    Wspolrzedna *wierzcholek1;
    Wspolrzedna *wierzcholek2;
    Wspolrzedna *wierzcholek3;
    Wspolrzedna *wierzcholek4;


/*    BokiSzescianu()
    {
        //
    }*/

    BokiSzescianu(Wspolrzedna &Punkt1, Wspolrzedna &Punkt2, Wspolrzedna &Punkt3, Wspolrzedna &Punkt4)

    {
        this->wierzcholek1 = &Punkt1;
        this->wierzcholek2 = &Punkt2;
        this->wierzcholek3 = &Punkt3;
        this->wierzcholek4 = &Punkt4;


    }
};

struct Szescian {

    QVector<Wspolrzedna> Wspolrzednas = QVector<Wspolrzedna>(8);
    QVector<BokiSzescianu> boki =QVector<BokiSzescianu>(6);

    void ustaw() {
        int wspolrzedneWierzcholkow[8][3] =
        {
            {-100, -100, -100},
            {-100, -100,  100},
            {-100,  100,  100},
            {-100,  100, -100},
            { 100, -100, -100},
            { 100, -100,  100},
            { 100,  100,  100},
            { 100,  100, -100}
        };

        for (int i = 0; i < 8; ++i) {
          Wspolrzednas[i] = Wspolrzedna(wspolrzedneWierzcholkow[i][0], wspolrzedneWierzcholkow[i][1], wspolrzedneWierzcholkow[i][2], 1);
        }

        int wierzcholkiNaBoki[6][4] =
        {
            {0, 1, 2, 3},
            {0, 1, 5, 4},
            {1, 2, 6, 5},
            {2, 3, 7, 6},
            {3, 0, 4, 7},
            {4, 5, 6, 7}
        };

        for (int i = 0; i < 6; ++i) {
          boki[i] = {Wspolrzednas[wierzcholkiNaBoki[i][0]], Wspolrzednas[wierzcholkiNaBoki[i][1]],
                      Wspolrzednas[wierzcholkiNaBoki[i][2]], Wspolrzednas[wierzcholkiNaBoki[i][3]]};
        }
    }
};


class MyWindow : public QWidget
{
    // Makro ktore musimy dodac jezeli definiujemy wlasne sygnaly lub sloty
    Q_OBJECT


public:
    // Typowa deklaracja konstruktora w Qt.
    // Parametr "parent" okresla rodzica komponenetu.
    // W przypadku naszej klasy parametr ten wskazuje na null
    // co oznacza, ze komponenet nie ma rodzica, jest to
    // komponenet najwyzszego poziomu
    MyWindow(QWidget *parent = 0);

    // Deklaracja destruktora
    ~MyWindow();

private slots:

    void paintEvent(QPaintEvent*);
    void czysc();

    void zrobSzescian();

    void ustawTranslacje1(int value);
    void ustawTranslacje2(int value);
    void ustawTranslacje3(int value);

    void ustawSkalowanie1(int value);
    void ustawSkalowanie2(int value);
    void ustawSkalowanie3(int value);

    void ustawRotacje1(int value);
    void ustawRotacje2(int value);
    void ustawRotacje3(int value);

private:
    QGroupBox *grupa;

    QImage *img;
    Szescian szescian = Szescian();
    int startX, startY, szer, wys, PrzesuniecieX=0, PrzesuniecieY=0, PrzesuniecieZ=0, obrotX=30, obrotY=30, obrotZ=0;
    float  skalowanieX=1, skalowanieY=1, skalowanieZ=1;
    bool isTextured = false;
    void Linia(int x1, int y1, int x2, int y2);
    void Linia(Wspolrzedna Punkt1, Wspolrzedna Punkt2);

    void drawPixel(int x, int y);
    void drawPixel(Wspolrzedna P, int a = 2, int b = 0);

    int pixel(int x, int y);
    int pixel(Wspolrzedna P);


    QSlider *sliderPrzesuniecie1;
    QSlider *sliderPrzesuniecie2;
    QSlider *sliderPrzesuniecie3;
    QSlider *sliderSkalowanie1;
    QSlider *sliderSkalowanie2;
    QSlider *sliderSkalowanie3;
    QSlider *sliderObrot1;
    QSlider *sliderObrot2;
    QSlider *sliderObrot3;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

};

