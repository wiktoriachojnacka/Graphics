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
#include <QVector>
#include <vector>

struct Point { public: double x, y; };
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
    int selectedIndex = -1, kolor = 0;

    void Kolo(int x1, int y1, int x2, int y2, QImage *image);
    bool klikniete = false;
    void czysc();
    void kopia(QImage *image1, QImage *image2);
    void pixel(int x, int y, QImage *image);
    void Linia(int x1, int y1, int x2, int y2, QImage *image);
    //void rysuj1();
    //void rysuj2();

    Point p1, p2;
    QVector <Point> punkty;
    int wybierzKolko(Point punktWybrania);
    void deletePoint(int i, QImage *image);
    void bSpline(QImage *image);

    // Deklaracje slotow, czyli funkcji wywolywanych
    // po wystapieniu zdarzen zwiazanych z GUI
    // np. klikniecie na przycisk, ruch myszka
private slots:
    void slot_czysc();
    //void slot_rysuj1();
    //void slot_rysuj2();
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

