#include "mainwindow.h"
#include "ui_mainwindow.h"

static QString main_icon_address = "/opt/DentalUnit/bin/icon/";
static uint8_t icon_global_size = 70;

void setIconOnButton(QPushButton *button, const QString &iconName, bool flat = true, bool transparent = true) {
    QIcon icon(main_icon_address + iconName);
    button->setIcon(icon);
    button->setIconSize(QSize(icon_global_size, icon_global_size));
    if (flat) button->setFlat(true);
    if (transparent) button->setStyleSheet("background-color: transparent; border: none;");
}

void setNormalStateStyle(QPushButton *button, bool circle = true){

    if (circle) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: transparent;"
                    "border: 5px solid black;"
                    "color: black;"
                    "border-radius: 40px;"
                    "}"
        );
    }else{
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: transparent;"
                    "border: 5px solid black;"
                    "color: black;"
                    "border-radius: 10px;"
                    "}"
        );
    }
}

void setActiveStateStyle(QPushButton *button, bool circle = true){

    if (circle) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #37c7f9;"
                    "border: 5px solid black;"
                    "color: white;"
                    "border-radius: 40px;"
                    "}"
        );
    }else{
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #37c7f9;"
                    "border: 5px solid black;"
                    "color: white;"
                    "border-radius: 10px;"
                    "}"
        );
    }
}

void MainWindow::setupSerialPort()
{
    serial = new QSerialPort(this);

    serial->setPortName("/dev/ttyS2");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::WriteOnly)) {
        qDebug() << "Serial port opened successfully.";
    } else {
        qDebug() << "Failed to open serial port:" << serial->errorString();
    }
}

void MainWindow::sendCommand(uint8_t command)
{
    uint8_t startByte = 0x7F;
    uint8_t crc = startByte + command;
    QByteArray data;
    data.append((char)startByte);
    data.append((char)command);
    data.append((char)crc);

    serial->write(data);
    qDebug() << "Command sent:" << data.toHex();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QPixmap pix(main_icon_address + "dentalunit.png");
    ui->Unit_Label->setPixmap(pix);

    setIconOnButton(ui->BackrestBackward_PB,    "backrestbackward.png");
    setIconOnButton(ui->BackrestForward_PB,     "backrestforward.png");
    setIconOnButton(ui->ChairUpward_PB,         "chairupward.png");
    setIconOnButton(ui->ChairDownward_PB,       "chairdownward.png");

    setIconOnButton(ui->BowlRinsing_PB,     "bowlrinsing.png",      false, true);
    setIconOnButton(ui->CupFiller_PB,       "cupfiller.png",        false, true);
    setIconOnButton(ui->OperatingLight_PB,  "operatinglight.png",   false, true);
    setIconOnButton(ui->WaterHeater_PB,     "waterheater.png",      false, true);
    setIconOnButton(ui->FilmViewer_PB,      "filmviewer.png",       false, true);

    setIconOnButton(ui->PresetPosition1_PB, "presetposition1.png", false, true);
    setIconOnButton(ui->PresetPosition2_PB, "presetposition2.png", false, true);
    setIconOnButton(ui->PresetPosition3_PB, "presetposition3.png", false, true);
    setIconOnButton(ui->RinsingPosition_PB, "rinsingposition.png", false, true);

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

    setActiveStateStyle(ui->PresetPositionGroupA_PB, false);
    setNormalStateStyle(ui->PresetPositionGroupB_PB, false);
    setNormalStateStyle(ui->PresetPositionGroupC_PB, false);
    setNormalStateStyle(ui->PresetPositionGroupD_PB, false);

    setNormalStateStyle(ui->PresetPosition1_PB, false);
    setNormalStateStyle(ui->PresetPosition2_PB, false);
    setNormalStateStyle(ui->PresetPosition3_PB, false);
    setNormalStateStyle(ui->RinsingPosition_PB, false);

    setNormalStateStyle(ui->WaterHeater_PB      , true);
    setNormalStateStyle(ui->CupFiller_PB        , true);
    setNormalStateStyle(ui->OperatingLight_PB   , true);
    setNormalStateStyle(ui->BowlRinsing_PB      , true);
    setNormalStateStyle(ui->FilmViewer_PB       , false);

    setupSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PresetPositionGroupA_PB_clicked()
{
    if (isPresetPositionGroupA_Active) {
        // Normal (OFF) state
//        setNormalStateStyle(ui->PresetPositionGroupA_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->PresetPositionGroupA_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupB_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupC_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupD_PB, false);

        setNormalStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->PresetPosition3_PB, false);
        setNormalStateStyle(ui->RinsingPosition_PB, false);

        isPresetPositionGroupA_Active = true;
        isPresetPositionGroupB_Active = false;
        isPresetPositionGroupC_Active = false;
        isPresetPositionGroupD_Active = false;
    }

//    setNormalStateStyle(ui->PresetPosition1_PB, false);
//    setNormalStateStyle(ui->PresetPosition2_PB, false);
//    setNormalStateStyle(ui->PresetPosition3_PB, false);
//    setNormalStateStyle(ui->RinsingPosition_PB, false);

    // Change the state
//    isPresetPositionGroupA_Active = !isPresetPositionGroupA_Active;
}

void MainWindow::on_PresetPositionGroupB_PB_clicked()
{
    if (isPresetPositionGroupB_Active) {
        // Normal (OFF) state
//        setNormalStateStyle(ui->PresetPositionGroupB_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->PresetPositionGroupB_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupA_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupC_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupD_PB, false);

        setNormalStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->PresetPosition3_PB, false);
        setNormalStateStyle(ui->RinsingPosition_PB, false);

        isPresetPositionGroupA_Active = false;
        isPresetPositionGroupB_Active = true;
        isPresetPositionGroupC_Active = false;
        isPresetPositionGroupD_Active = false;
    }

//    setNormalStateStyle(ui->PresetPosition1_PB, false);
//    setNormalStateStyle(ui->PresetPosition2_PB, false);
//    setNormalStateStyle(ui->PresetPosition3_PB, false);
//    setNormalStateStyle(ui->RinsingPosition_PB, false);

    // Change the state
//    isPresetPositionGroupB_Active = !isPresetPositionGroupB_Active;
}


void MainWindow::on_PresetPositionGroupC_PB_clicked()
{
    if (isPresetPositionGroupC_Active) {
        // Normal (OFF) state
//        setNormalStateStyle(ui->PresetPositionGroupC_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->PresetPositionGroupC_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupA_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupB_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupD_PB, false);

        setNormalStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->PresetPosition3_PB, false);
        setNormalStateStyle(ui->RinsingPosition_PB, false);

        isPresetPositionGroupA_Active = false;
        isPresetPositionGroupB_Active = false;
        isPresetPositionGroupC_Active = true;
        isPresetPositionGroupD_Active = false;
    }

//    setNormalStateStyle(ui->PresetPosition1_PB, false);
//    setNormalStateStyle(ui->PresetPosition2_PB, false);
//    setNormalStateStyle(ui->PresetPosition3_PB, false);
//    setNormalStateStyle(ui->RinsingPosition_PB, false);

    // Change the state
//    isPresetPositionGroupC_Active = !isPresetPositionGroupC_Active;
}


void MainWindow::on_PresetPositionGroupD_PB_clicked()
{
    if (isPresetPositionGroupD_Active) {
        // Normal (OFF) state
//        setNormalStateStyle(ui->PresetPositionGroupD_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->PresetPositionGroupD_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupA_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupB_PB, false);
        setNormalStateStyle(ui->PresetPositionGroupC_PB, false);

        setNormalStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->PresetPosition3_PB, false);
        setNormalStateStyle(ui->RinsingPosition_PB, false);

        isPresetPositionGroupA_Active = false;
        isPresetPositionGroupB_Active = false;
        isPresetPositionGroupC_Active = false;
        isPresetPositionGroupD_Active = true;
    }

//    setNormalStateStyle(ui->PresetPosition1_PB, false);
//    setNormalStateStyle(ui->PresetPosition2_PB, false);
//    setNormalStateStyle(ui->PresetPosition3_PB, false);
//    setNormalStateStyle(ui->RinsingPosition_PB, false);

    // Change the state
//    isPresetPositionGroupD_Active = !isPresetPositionGroupD_Active;
}


void MainWindow::on_PresetPosition1_PB_clicked()
{
    if (isPresetPosition1Active) {
        // Normal (OFF) state
        setNormalStateStyle(ui->PresetPosition1_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->PresetPosition3_PB, false);
        setNormalStateStyle(ui->RinsingPosition_PB, false);
    }

    // Change the state
    isPresetPosition1Active = !isPresetPosition1Active;
}


void MainWindow::on_PresetPosition2_PB_clicked()
{
    if (isPresetPosition2Active) {
        // Normal (OFF) state
        setNormalStateStyle(ui->PresetPosition2_PB, false);
    } else {
        // Active (ON) state


        setActiveStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition3_PB, false);
        setNormalStateStyle(ui->RinsingPosition_PB, false);
    }

    // Change the state
    isPresetPosition2Active = !isPresetPosition2Active;
}


void MainWindow::on_PresetPosition3_PB_clicked()
{
    if (isPresetPosition3Active) {
        // Normal (OFF) state
        setNormalStateStyle(ui->PresetPosition3_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->PresetPosition3_PB, false);
        setNormalStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->RinsingPosition_PB, false);
    }

    // Change the state
    isPresetPosition3Active = !isPresetPosition3Active;
}


void MainWindow::on_RinsingPosition_PB_clicked()
{
    if (isRinsingPosition1Active) {
        // Normal (OFF) state
        setNormalStateStyle(ui->RinsingPosition_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->RinsingPosition_PB, false);
        setNormalStateStyle(ui->PresetPosition1_PB, false);
        setNormalStateStyle(ui->PresetPosition2_PB, false);
        setNormalStateStyle(ui->PresetPosition3_PB, false);
    }

    // Change the state
    isRinsingPosition1Active = !isRinsingPosition1Active;
}



void MainWindow::on_WaterHeater_PB_clicked()
{
    sendCommand(WATERHEATER);
    qDebug() << "--> Water heater.";

    if (isWaterHeaterActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->WaterHeater_PB, true);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->WaterHeater_PB, true);
    }

    // Change the state
    isWaterHeaterActive = !isWaterHeaterActive;
}


void MainWindow::on_CupFiller_PB_clicked()
{
    sendCommand(CUPFILLER);

    if (isCupFillerActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->CupFiller_PB, true);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->CupFiller_PB, true);
    }

    // Change the state
    isCupFillerActive = !isCupFillerActive;
}


void MainWindow::on_OperatingLight_PB_clicked()
{
    sendCommand(OPERATINGLIGHT);

    if (isOperatingLightActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->OperatingLight_PB, true);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->OperatingLight_PB, true);
    }

    // Change the state
    isOperatingLightActive = !isOperatingLightActive;
}


void MainWindow::on_BowlRinsing_PB_clicked()
{
    sendCommand(BOWLRINSING);

    if (isBowlRinsingActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->BowlRinsing_PB, true);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->BowlRinsing_PB, true);
    }

    // Change the state
    isBowlRinsingActive = !isBowlRinsingActive;
}


void MainWindow::on_FilmViewer_PB_clicked()
{
    sendCommand(FILMVIEW);

    if (isFilmViewerActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->FilmViewer_PB, false);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->FilmViewer_PB, false);
    }

    // Change the state
    isFilmViewerActive = !isFilmViewerActive;
}


void MainWindow::on_BackrestForward_PB_pressed()
{
    sendCommand(BACKRESTFORWARD);
}


void MainWindow::on_BackrestForward_PB_released()
{
    qDebug() << "-> BackrestForward_PB is RELEASED." ;
}


void MainWindow::on_BackrestBackward_PB_pressed()
{
    sendCommand(BACKRESTBACKWARD);
}


void MainWindow::on_BackrestBackward_PB_released()
{
    qDebug() << "-> BackrestBackward_PB is RELEASED." ;
}


void MainWindow::on_ChairUpward_PB_pressed()
{
    sendCommand(CHAIRUP);
}


void MainWindow::on_ChairUpward_PB_released()
{
    qDebug() << "-> ChairUpward_PB is RELEASED." ;
}


void MainWindow::on_ChairDownward_PB_pressed()
{
    sendCommand(CHAIRDOWN);
}


void MainWindow::on_ChairDownward_PB_released()
{
    qDebug() << "-> ChairDownward_PB is RELEASED." ;
}

