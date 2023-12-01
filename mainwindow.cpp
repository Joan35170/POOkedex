#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("POOkédex");

    setFixedSize(QSize(800, 542));
    QPixmap bkgnd(":/pokeRessources/pokedex_bg.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    ui->groupBox->setStyleSheet("border: 0; background: transparent;");
    ui->pokemonName->setStyleSheet("border: 0; background: transparent;");
    ui->pokemonTypes->setStyleSheet("border: 0; background: transparent;");
    ui->groupBox_2->setStyleSheet("border: 0; background: transparent;");
    ui->groupBox_3->setStyleSheet("border: 0; background: transparent;");
    ui->groupBox_4->setStyleSheet("border: 0; background: transparent;");
    ui->groupBox_5->setStyleSheet("border: 0; background: transparent;");
    ui->groupBox_6->setStyleSheet("border: 0; background: transparent;");
    ui->groupBox_7->setStyleSheet("border: 0; background: transparent;");
    ui->groupBox_8->setStyleSheet("border: 0; background: transparent;");
    ui->pokemonName->setStyleSheet("border: 0; background: transparent;");
    ui->pokemonTypes->setStyleSheet("border: 0; background: transparent;");
    ui->searchBar->setStyleSheet("border: 0; background: transparent;");
    ui->searchButton->setStyleSheet("border: 0; background: transparent;");
    ui->searchButton->setToolTip("Rechercher");
    ui->increment10->setStyleSheet("border: 0; background: transparent;");
    ui->increment10->setToolTip("+10");
    ui->decrement1->setStyleSheet("border: 0; background: transparent;");
    ui->decrement1->setToolTip("-1");
    ui->decrement10->setStyleSheet("border: 0; background: transparent;");
    ui->decrement10->setToolTip("-10");
    ui->increment1->setStyleSheet("border: 0; background: transparent;");
    ui->increment1->setToolTip("+1");

    qnam = new QNetworkAccessManager();
    getPokemon(25);
    ui->searchBar->setText(QString::number(25));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::Maj(QString namePokemon)
{
    namePokemon[0] = namePokemon[0].toUpper();
    return namePokemon;
}

void MainWindow::getPokemon(int id)
{
    if(id < 1) {
        getPokemon(898);
        ui->searchBar->setText(QString::number(1));

        QMessageBox msgBoxId;
        msgBoxId.setText("Pokémon inexistant vérifier l'id saisi !");
        msgBoxId.exec();
    }
    else if(id > 898) {
        getPokemon(1);
        ui->searchBar->setText(QString::number(898));

        QMessageBox msgBoxId;
        msgBoxId.setText("Pokémon inexistant vérifier l'id saisi !");
        msgBoxId.exec();
    }

    pokemonId = id;
    pokemonReply = qnam->get(QNetworkRequest(QUrl("https://pokeapi.co/api/v2/pokemon/" + QString::number(id))));
    connect(pokemonReply, SIGNAL(finished()), this, SLOT(managePokemonReply()));
}

void MainWindow::getPokemonTypes(int id)
{
    pokemonReply_2 = qnam->get(QNetworkRequest(QUrl("https://pokeapi.co/api/v2/pokemon/" + QString::number(id))));
    connect(pokemonReply_2, SIGNAL(finished()), this, SLOT(managePokemonReply()));
}

void MainWindow::getPokemonSprite(QString name)
{
    pokemonReply_3 = qnam->get(QNetworkRequest(QUrl("https://img.pokemondb.net/sprites/sword-shield/icon/" + name + ".png")));
    connect(pokemonReply_3, SIGNAL(finished()), this, SLOT(managePokemonSprite()));
}

void MainWindow::on_searchBar_returnPressed()
{
    getPokemon(ui->searchBar->text().toInt());
}

void MainWindow::on_searchButton_clicked()
{
    getPokemon(ui->searchBar->text().toInt());
}

void MainWindow::on_increment10_clicked()
{
    if(pokemonId < 1) {
        getPokemon(898);
        ui->searchBar->setText(QString::number(898));
    }

    int incre10;

    incre10 = ui->searchBar->text().toInt();
    incre10 += 10;

    ui->searchBar->setText(QString::number(incre10));
    getPokemon(incre10);
}

void MainWindow::on_decrement1_clicked()
{
    if(pokemonId < 1) {
        getPokemon(898);
        ui->searchBar->setText(QString::number(898));

    }

    int decre;

    decre = ui->searchBar->text().toInt();
    decre--;

    ui->searchBar->setText(QString::number(decre));
    getPokemon(decre);
}

void MainWindow::on_decrement10_clicked()
{
    if(pokemonId > 898) {
        getPokemon(1);
        ui->searchBar->setText(QString::number(1));
    }

    int decre10;

    decre10 = ui->searchBar->text().toInt();
    decre10 -= 10;

    ui->searchBar->setText(QString::number(decre10));
    getPokemon(decre10);
}

void MainWindow::on_increment1_clicked()
{
    if(pokemonId > 898) {
        getPokemon(1);
        ui->searchBar->setText(QString::number(1));
    }

    int incre;

    incre = ui->searchBar->text().toInt();
    incre++;

    ui->searchBar->setText(QString::number(incre));
    getPokemon(incre);
}

void MainWindow::on_previousVisual_clicked()
{
    if(visual == 0) {
        visual = 2;
        getPokemonVisual();
    }
    else {
    visual--;
    getPokemonVisual();
    }
}

void MainWindow::on_nextVisual_clicked()
{
    if(visual == 2) {
        visual = 0;
        getPokemonVisual();
    }
    else {
    visual++;
    getPokemonVisual();
    }
}

void MainWindow::managePokemonReply()
{
    QString source = pokemonReply->readAll();
    QJsonObject pokeData;
    QJsonDocument doc = QJsonDocument::fromJson(source.toUtf8());

    if(!doc.isNull()) {
        if(doc.isObject()) {
            pokeData = doc.object();

            // Travailler à partir d’ici avec l’objet pokeData

            if(pokeData.contains("name") && pokeData["name"].isString()) {
                namePokemon = pokeData["name"].toString();
                getPokemonSprite(namePokemon);
                ui->pokemonName->setText(Maj(namePokemon));
            }

            // Type du Pokemon
            if(pokeData.contains("types") && pokeData["types"].isArray()) {
                QJsonArray types = pokeData["types"].toArray();
                QString display = "";
                for(int i = 0; i < types.count(); i++) {
                    QJsonObject nType = types[i].toObject();
                    QJsonObject type = nType["type"].toObject();
                    display += (i == 0 ? "" : ", ") + type["name"].toString();
                    ui->pokemonTypes->setText("(" + display + ")");
                }
            }
        }
        else {
            qDebug() << "La réponse n’est pas correctement formée." << "\n";
        }
    }
    else {
        qDebug() << "La requête a renvoyé une réponse vide." << "\n";
    }
}

void MainWindow::managePokemonSprite()
{
    QByteArray imgData = pokemonReply_3->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(imgData);

    if(!pixmap.isNull()) {
        ui->pokemonSprite->clear();
        ui->pokemonSprite->setPixmap(pixmap.scaled(ui->pokemonSprite->size(), Qt::KeepAspectRatio));
    }
    else {
        qDebug() << "La réponse n’est pas correctement formée." << "\n";
    }
}

void MainWindow::getPokemonVisual()
{
    QString url;

    switch(visual)
    {
    case 0:
        url = "https://img.pokemondb.net/sprites/home/normal/" + namePokemon + ".png";
        qDebug() << "Visual 0" << "\n";
        break;
    case 1:
        url = "https://img.pokemondb.net/artwork/vector/large/" + namePokemon + ".png";
        qDebug() << "Visual 1" << "\n";
        break;
    case 2:
        url = "https://img.pokemondb.net/sprites/sword-shield/icon/" + namePokemon + ".png";
        qDebug() << "Visual 2" << "\n";
        break;

    }
    pokemonReply_3 = qnam->get(QNetworkRequest(QUrl(url)));
    connect(pokemonReply_3, SIGNAL(finished()), this, SLOT(managePokemonSprite()));
}





