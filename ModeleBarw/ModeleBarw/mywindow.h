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
#include <QtMath>
#include <QSlider>
#include <QLabel>


// MyWindow jest podklasa klasy QWidget
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

private:

    // Pole przechowujace obrazek
    QImage *img, *imgkopia;

    // Przyciski
    //QPushButton *draw1Button;
    // QPushButton *draw2Button;
    QPushButton *cleanButton;
    QPushButton *exitButton;

//QSlider *slider;
QSlider *sliderRGB1;
QSlider *sliderRGB2;
QSlider *sliderRGB3;
QSlider *sliderHSV1;
QSlider *sliderHSV2;
QSlider *sliderHSV3;

    // Grupa przyciskow
    QGroupBox *grupa;
QGroupBox *RGBgrupa;
QGroupBox *HSVgrupa;
QLabel *label;


    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;
    int x1;
    int y1;

    int red = 255;
    int green = 255;
    int blue = 255;

    int czerwony = 0;
    int zielony = 0;
    int niebieski = 0;
    double hue = 0;
    double saturation = 0;
    double value = 0;

    bool klikniete = false;
    void czysc();
    void kopia(QImage *image1, QImage *image2);
    void pixel(int x, int y, QImage *image);


    //void rysuj1();
    // void rysuj2();

    void Konwersja_z_HSV_do_RGB (int H, double S, double V);

    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka

private slots:

    void slot_czysc();
    void RGBsliderRed(int r);
    void RGBsliderGreen(int g);
    void RGBsliderBlue(int b);
    void HSVsliderHue(int h);
    void HSVsliderSaturation(int s);
    void HSVsliderValue(int v);
    //void slot_rysuj1();
    //void slot_rysuj2();

    void paintEvent(QPaintEvent*);


};

