#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QPoint>

namespace Ui {
    class MainWindow;
}


/**
 * \class Mainwindow
 * @brief Classe décrivant la fenêtre principale de l'application.
 * \authors Mehdi Belhaj
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    void valider();
    void indice();
    void regles();
    void effacer();

private slots:
    void onValider();
    void onIndice();
    void onRegles();
    void onEffacer();

private:
    Ui::MainWindow *ui;

    /** \brief Un pointeur sur le bouton de la barre d'outil pour afficher les règles */
    QPushButton *m_toolbar_bouton_regles;

    /** \brief Un pointeur sur le bouton de la barre d'outil pour demander un indice */
    QPushButton *m_toolbar_bouton_indice;
    /** */
};

#endif // MAINWINDOW_H
