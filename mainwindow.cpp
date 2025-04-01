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
    /*ui->setupUi(this);

    QPixmap pix(main_icon_address+"dentalunit.png");
    ui->Unit_Label->setPixmap(pix);

    QIcon icon_backrestbackward(main_icon_address+"backrestbackward.png");
    ui->BackrestBackward_PB->setIcon(icon_backrestbackward);
    ui->BackrestBackward_PB->setIconSize(QSize(icon_global_size, icon_global_size));
    ui->BackrestBackward_PB->setFlat(true);
    ui->BackrestBackward_PB->setStyleSheet("background-color: transparent; border: none;");

    QIcon icon_backrestforward(main_icon_address+"backrestforward.png");
    ui->BackrestForward_PB->setIcon(icon_backrestforward);
    ui->BackrestForward_PB->setIconSize(QSize(icon_global_size, icon_global_size));
    ui->BackrestForward_PB->setFlat(true);
    ui->BackrestForward_PB->setStyleSheet("background-color: transparent; border: none;");

    QIcon icon_chairupward(main_icon_address+"chairupward.png");
    ui->ChairUpward_PB->setIcon(icon_chairupward);
    ui->ChairUpward_PB->setIconSize(QSize(icon_global_size, icon_global_size));
    ui->ChairUpward_PB->setFlat(true);
    ui->ChairUpward_PB->setStyleSheet("background-color: transparent; border: none;");

    QIcon icon_chairdownward(main_icon_address+"chairdownward.png");
    ui->ChairDownward_PB->setIcon(icon_chairdownward);
    ui->ChairDownward_PB->setIconSize(QSize(icon_global_size, icon_global_size));
    ui->ChairDownward_PB->setFlat(true);
    ui->ChairDownward_PB->setStyleSheet("background-color: transparent; border: none;");

    QIcon icon_bowlrinsing(main_icon_address+"bowlrinsing.png");
    ui->BowlRinsing_PB->setIcon(icon_bowlrinsing);
    ui->BowlRinsing_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_cupfiller(main_icon_address+"cupfiller.png");
    ui->CupFiller_PB->setIcon(icon_cupfiller);
    ui->CupFiller_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_operatinglight(main_icon_address+"operatinglight.png");
    ui->OperatingLight_PB->setIcon(icon_operatinglight);
    ui->OperatingLight_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_waterheater(main_icon_address+"waterheater.png");
    ui->WaterHeater_PB->setIcon(icon_waterheater);
    ui->WaterHeater_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_presetposition1(main_icon_address+"presetposition1.png");
    ui->PresetPosition1_PB->setIcon(icon_presetposition1);
    ui->PresetPosition1_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_presetposition2(main_icon_address+"presetposition2.png");
    ui->PresetPosition2_PB->setIcon(icon_presetposition2);
    ui->PresetPosition2_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_presetposition3(main_icon_address+"presetposition3.png");
    ui->PresetPosition3_PB->setIcon(icon_presetposition3);
    ui->PresetPosition3_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_rinsingposition(main_icon_address+"rinsingposition.png");
    ui->RinsingPosition_PB->setIcon(icon_rinsingposition);
    ui->RinsingPosition_PB->setIconSize(QSize(icon_global_size, icon_global_size));

    QIcon icon_callassist(main_icon_address+"callassist.png");
    ui->CallAssist_PB->setIcon(icon_callassist);
    ui->CallAssist_PB->setIconSize(QSize(icon_global_size, icon_global_size));
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
    );*/

    ui->setupUi(this);

    // نمایش تصویر اصلی در QLabel
    QPixmap pix(main_icon_address + "dentalunit.png");
    ui->Unit_Label->setPixmap(pix);

    // دکمه‌هایی با آیکون و ظاهر شفاف
    setIconOnButton(ui->BackrestBackward_PB, "backrestbackward.png");
    setIconOnButton(ui->BackrestForward_PB,  "backrestforward.png");
    setIconOnButton(ui->ChairUpward_PB,      "chairupward.png");
    setIconOnButton(ui->ChairDownward_PB,    "chairdownward.png");

    // دکمه‌هایی با فقط آیکون (بدون نیاز به flat)
    setIconOnButton(ui->BowlRinsing_PB,      "bowlrinsing.png",     false, false);
    setIconOnButton(ui->CupFiller_PB,        "cupfiller.png",       false, false);
    setIconOnButton(ui->OperatingLight_PB,   "operatinglight.png",  false, false);
    setIconOnButton(ui->WaterHeater_PB,      "waterheater.png",     false, false);

    setIconOnButton(ui->PresetPosition1_PB,  "presetposition1.png", false, false);
    setIconOnButton(ui->PresetPosition2_PB,  "presetposition2.png", false, false);
    setIconOnButton(ui->PresetPosition3_PB,  "presetposition3.png", false, false);
    setIconOnButton(ui->RinsingPosition_PB,  "rinsingposition.png", false, false);

    // دکمه با استایل اختصاصی
    setIconOnButton(ui->CallAssist_PB, "callassist.png", false, false);
    ui->CallAssist_PB->setStyleSheet(
        "QPushButton {"
        "background-color: #2eccb6;"
        "border-radius: 10px;"
        "}"
    );

    // سایر دکمه‌ها با استایل خاص
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
