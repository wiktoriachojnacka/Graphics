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
    QImage *img, *imgkopia, *img2;

    // Przyciski
    //QPushButton *draw1Button;
    // QPushButton *draw2Button;
    QPushButton *cleanButton;
    QPushButton *exitButton;

    // Grupa przyciskow
    QGroupBox *grupa;

    // Pola przechowujace szerokosc i wysokosc rysunku
    // oraz wspolrzedne jego lewego gornego naroznika
    int szer;
    int wys;
    int poczX;
    int poczY;
    int x1;
    int y1;
    int szer2, wys2, startX, startY,transX = 180, transY = 180;

    bool klikniete = false;
    void czysc();
    void kopia(QImage *image1, QImage *image2);
    void pixel(int x, int y, QImage *image);
    void Linia(int x1, int y1, int x2, int y2, QImage *image);
    float skalowanieX = 1.0, skalowanieY = 1.0, alfa = 0, pochylenieX  = 0, pochylenieY = 0;

     void rysuj();
    //void rysuj1();
    // void rysuj2();


    QSlider *sliderTranslacja1;
    QSlider *sliderTranslacja2;

    QSlider *sliderSkalowanie1;
    QSlider *sliderSkalowanie2;

    QSlider *sliderPochylenie1;
    QSlider *sliderPochylenie2;

    QSlider *sliderObrot;


    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;

    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
    //void slot_rysuj1();
    //void slot_rysuj2();

    void paintEvent(QPaintEvent*);
    void translacjaSlider1(int value);
    void translacjaSlider2(int value);
    void obrotSlider(int value);
    void skalowanieSlider1(int value);
    void skalowanieSlider2(int value);
    void pochylenieSlider1(int value);
    void pochylenieSlider2(int value);






};

