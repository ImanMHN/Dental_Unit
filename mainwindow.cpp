#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>
#include <QFile>
#include <string>

static QString main_icon_address = "/opt/DentalUnit/bin/icon/";
static int icon_global_size = 70;

// تابع کمکی برای تنظیم آیکون روی دکمه
void setIconOnButton(QPushButton *button, const QString &iconName, bool flat = true, bool transparent = true) {
    QIcon icon(main_icon_address + iconName);
    button->setIcon(icon);
    button->setIconSize(QSize(icon_global_size, icon_global_size));
    if (flat) button->setFlat(true);
    if (transparent) button->setStyleSheet("background-color: transparent; border: none;");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QPixmap pix(main_icon_address + "dentalunit.png");
    ui->Unit_Label->setPixmap(pix);

    setIconOnButton(ui->BackrestBackward_PB, "backrestbackward.png");
    setIconOnButton(ui->BackrestForward_PB,  "backrestforward.png");
    setIconOnButton(ui->ChairUpward_PB,      "chairupward.png");
    setIconOnButton(ui->ChairDownward_PB,    "chairdownward.png");

    setIconOnButton(ui->BowlRinsing_PB,      "bowlrinsing.png",     false, false);
    setIconOnButton(ui->CupFiller_PB,        "cupfiller.png",       false, false);
    setIconOnButton(ui->OperatingLight_PB,   "operatinglight.png",  false, false);
    setIconOnButton(ui->WaterHeater_PB,      "waterheater.png",     false, false);

    setIconOnButton(ui->PresetPosition1_PB,  "presetposition1.png", false, false);
    setIconOnButton(ui->PresetPosition2_PB,  "presetposition2.png", false, false);
    setIconOnButton(ui->PresetPosition3_PB,  "presetposition3.png", false, false);
    setIconOnButton(ui->RinsingPosition_PB,  "rinsingposition.png", false, false);

    setIconOnButton(ui->CallAssist_PB, "callassist.png", false, false);
    ui->CallAssist_PB->setStyleSheet(
        "QPushButton {"
        "background-color: #2eccb6;"
        "border-radius: 10px;"
        "}"
    );

    ui->Setting_PB->setStyleSheet(
        "QPushButton {"
        "background-color: #2ecc71;"
        "color: white;"
        "border: none;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #27ae60;"
        "}"
    );

    ui->Reset_PB->setStyleSheet(
        "QPushButton {"
        "background-color: #cc2e2e;"
        "color: white;"
        "border: none;"
        "border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "background-color: #ae2727;"
        "}"
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}
