#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *qnam;
    QNetworkReply *pokemonReply;
    QNetworkReply *pokemonReply_2;
    QNetworkReply *pokemonReply_3;
    QNetworkReply *pokemonReply_4;
    QString namePokemon;
    int pokemonId;
    int visual = 2;
    void getPokemon(int);
    void getPokemonTypes(int);
    void getPokemonSprite(QString);
    void getPokemonVisual();
    QString Maj(QString);


private slots:
    void managePokemonReply();
    void managePokemonSprite();
    void on_searchBar_returnPressed();
    void on_searchButton_clicked();
    void on_increment10_clicked();
    void on_decrement1_clicked();
    void on_decrement10_clicked();
    void on_increment1_clicked();
    void on_previousVisual_clicked();
    void on_nextVisual_clicked();

};

#endif // MAINWINDOW_H
