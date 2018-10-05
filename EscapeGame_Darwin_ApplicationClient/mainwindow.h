#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QList>

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


private:
    Ui::MainWindow *ui;

    /** */
};

#endif // MAINWINDOW_H
