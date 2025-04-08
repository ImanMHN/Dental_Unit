#include "mainwindow.h"
#include "ui_mainwindow.h"

/********** Custom variable Definition ***********/
static QString  main_icon_address = "/opt/DentalUnit/bin/icon/";
bool            isResetUP = true;
bool            isButtonDirActive = false;
bool            isSerialPort2Free = true;
uint8_t         intervalTime = 100;
uint8_t         currentKeyState = WAITING_STATE;
uint16_t        enteringSettingModeTime = 0;
uint16_t        cupFillingTime = 1000;
uint16_t        tmpTimeKeeper = 0;
uint32_t        flushTime = 2000; //5*60*1000;
QByteArray      voiceAssistCommand;


/********** Custom Function Declaration ***********/
void setIconOnButton(QPushButton *button, bool flat = true, bool transparent = true);
void setNormalStateStyle(QPushButton *button, uint8_t whichSpecialButton = NONE_SB);
void setActiveStateStyle(QPushButton *button, uint8_t whichSpecialButton = NONE_SB);
void setChairDirectionsStyle(QPushButton *button);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    setupSerialPort();

    setupTimer();

//    QPixmap pix(main_icon_address + "dentalunit.png");
//    ui->Unit_Label->setPixmap(pix);

    setStyleSheet("background-color: #e2f8fa;");

    setIconOnButton(ui->BackrestBackward_PB);
    setIconOnButton(ui->BackrestForward_PB);
    setIconOnButton(ui->ChairUpward_PB);
    setIconOnButton(ui->ChairDownward_PB);

    setIconOnButton(ui->BowlRinsing_PB,     false, true);
    setIconOnButton(ui->CupFiller_PB,       false, true);
    setIconOnButton(ui->OperatingLight_PB,  false, true);
    setIconOnButton(ui->WaterHeater_PB,     false, true);
    setIconOnButton(ui->FilmViewer_PB,      false, true);

    setIconOnButton(ui->PresetPosition1_PB, false, true);
    setIconOnButton(ui->PresetPosition2_PB, false, true);
    setIconOnButton(ui->PresetPosition3_PB, false, true);
    setIconOnButton(ui->RinsingPosition_PB, false, true);

    setIconOnButton(ui->CallAssist_PB, false, true);

    setNormalStateStyle(ui->CallAssist_PB   , CALLASSIST_SB);
    setNormalStateStyle(ui->Setting_PB      , SETTING_SB);
    setNormalStateStyle(ui->Reset_PB        , RESET_SB);

    setActiveStateStyle(ui->PresetPositionGroupA_PB, NONE_SB);
    std::fill(std::begin(isPresetPositionGroupActive), std::end(isPresetPositionGroupActive), false);
    isPresetPositionGroupActive[POSITION_GROUP_A] = true;
    setNormalStateStyle(ui->PresetPositionGroupB_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPositionGroupC_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPositionGroupD_PB, NONE_SB);

    setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
    setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

    setNormalStateStyle(ui->WaterHeater_PB      , CIRCLE_SB);
    setNormalStateStyle(ui->CupFiller_PB        , CIRCLE_SB);
    setNormalStateStyle(ui->OperatingLight_PB   , CIRCLE_SB);
    setNormalStateStyle(ui->BowlRinsing_PB      , CIRCLE_SB);
    setNormalStateStyle(ui->FilmViewer_PB       , NONE_SB);

    setChairDirectionsStyle(ui->ChairUpward_PB);
    setChairDirectionsStyle(ui->ChairDownward_PB);
    setChairDirectionsStyle(ui->BackrestBackward_PB);
    setChairDirectionsStyle(ui->BackrestForward_PB);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PresetPositionGroupA_PB_pressed()
{
    if (!isPresetPositionGroupA_Active) {

        sendCommand(DR_1);

        setActiveStateStyle(ui->PresetPositionGroupA_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupB_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupC_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupD_PB, NONE_SB);

        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
        setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

        std::fill(std::begin(isPresetPositionGroupActive), std::end(isPresetPositionGroupActive), false);
        isPresetPositionGroupActive[POSITION_GROUP_A] = true;

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = false;
    }
}


void MainWindow::on_PresetPositionGroupB_PB_pressed()
{
    if (!isPresetPositionGroupB_Active) {

        sendCommand(DR_2);

        setActiveStateStyle(ui->PresetPositionGroupB_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupA_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupC_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupD_PB, NONE_SB);

        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
        setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

        std::fill(std::begin(isPresetPositionGroupActive), std::end(isPresetPositionGroupActive), false);
        isPresetPositionGroupActive[POSITION_GROUP_B] = true;

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = false;
    }
}


void MainWindow::on_PresetPositionGroupC_PB_pressed()
{
    if (!isPresetPositionGroupC_Active) {

        sendCommand(DR_3);

        setActiveStateStyle(ui->PresetPositionGroupC_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupA_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupB_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupD_PB, NONE_SB);

        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
        setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

        std::fill(std::begin(isPresetPositionGroupActive), std::end(isPresetPositionGroupActive), false);
        isPresetPositionGroupActive[POSITION_GROUP_C] = true;

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = false;
    }
}


void MainWindow::on_PresetPositionGroupD_PB_pressed()
{
    if (!isPresetPositionGroupD_Active) {

        sendCommand(DR_4);

        setActiveStateStyle(ui->PresetPositionGroupD_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupA_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupB_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPositionGroupC_PB, NONE_SB);

        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
        setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

        std::fill(std::begin(isPresetPositionGroupActive), std::end(isPresetPositionGroupActive), false);
        isPresetPositionGroupActive[POSITION_GROUP_D] = true;

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = false;
    }
}


void MainWindow::on_PresetPosition1_PB_pressed()
{
    if (!isPresetPosition1Active) {

        setActiveStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
        setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

        isPresetPosition1Active     = true;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = false;

        for (int i= POSITION_GROUP_A; i<=POSITION_GROUP_D; i++)
        {
            if(isPresetPositionGroupActive[i])
            {
                sendCommand(PREPOSITION_A1+(3*i));
                break;
            }
        }
    }
}


void MainWindow::on_PresetPosition2_PB_pressed()
{
    if (!isPresetPosition2Active) {

        setActiveStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
        setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = true;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = false;

        for (int i= POSITION_GROUP_A; i<=POSITION_GROUP_D; i++)
        {
            if(isPresetPositionGroupActive[i])
            {
                sendCommand(PREPOSITION_A2+(3*i));
                break;
            }
        }
    }
}


void MainWindow::on_PresetPosition3_PB_pressed()
{
    if (!isPresetPosition3Active) {

        setActiveStateStyle(ui->PresetPosition3_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = true;
        isRinsingPosition1Active    = false;

        for (int i= POSITION_GROUP_A; i<=POSITION_GROUP_D; i++)
        {
            if(isPresetPositionGroupActive[i])
            {
                sendCommand(PREPOSITION_A3+(3*i));
                break;
            }
        }
    }
}

void MainWindow::on_RinsingPosition_PB_pressed()
{
    sendCommand(RESET2);
    if (!isRinsingPosition1Active) {

        setActiveStateStyle(ui->RinsingPosition_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = true;
    }
}

void MainWindow::on_WaterHeater_PB_pressed()
{
    sendCommand(WATERHEATER);

    setActiveStateStyle(ui->WaterHeater_PB, CIRCLE_SB);
}

void MainWindow::on_WaterHeater_PB_released()
{
    setNormalStateStyle(ui->WaterHeater_PB, CIRCLE_SB);
}

void MainWindow::on_CupFiller_PB_pressed()
{
    sendCommand(CUPFILLER);

    setActiveStateStyle(ui->CupFiller_PB, CIRCLE_SB);
}

void MainWindow::on_CupFiller_PB_released()
{
    setNormalStateStyle(ui->CupFiller_PB, CIRCLE_SB);
}

void MainWindow::on_OperatingLight_PB_pressed()
{
    sendCommand(OPERATINGLIGHT);

    if (isOperatingLightActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->OperatingLight_PB, CIRCLE_SB);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->OperatingLight_PB, CIRCLE_SB);
    }

    // Change the state
    isOperatingLightActive = !isOperatingLightActive;
}

void MainWindow::on_BowlRinsing_PB_pressed()
{
    sendCommand(BOWLRINSING);

    setActiveStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
}


void MainWindow::on_BowlRinsing_PB_released()
{
    setNormalStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
}

void MainWindow::on_FilmViewer_PB_pressed()
{
    sendCommand(FILMVIEW);

    if (isFilmViewerActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->FilmViewer_PB, NONE_SB);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->FilmViewer_PB, NONE_SB);
    }

    // Change the state
    isFilmViewerActive = !isFilmViewerActive;
}


void MainWindow::on_BackrestForward_PB_pressed()
{
    currentKeyState = BACKREST_FORWARD_STATE;

    setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
    setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

    isPresetPosition1Active     = false;
    isPresetPosition2Active     = false;
    isPresetPosition3Active     = false;
    isRinsingPosition1Active    = false;
}


void MainWindow::on_BackrestForward_PB_released()
{
    currentKeyState = WAITING_STATE;
}


void MainWindow::on_BackrestBackward_PB_pressed()
{
    setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
    setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

    isPresetPosition1Active     = false;
    isPresetPosition2Active     = false;
    isPresetPosition3Active     = false;
    isRinsingPosition1Active    = false;

    currentKeyState = BACKREST_BACKWARD_STATE;
}


void MainWindow::on_BackrestBackward_PB_released()
{
    currentKeyState = WAITING_STATE;
}


void MainWindow::on_ChairUpward_PB_pressed()
{
    setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
    setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

    isPresetPosition1Active     = false;
    isPresetPosition2Active     = false;
    isPresetPosition3Active     = false;
    isRinsingPosition1Active    = false;

    currentKeyState = CHAIR_UP_STATE;
}


void MainWindow::on_ChairUpward_PB_released()
{
    currentKeyState = WAITING_STATE;
}


void MainWindow::on_ChairDownward_PB_pressed()
{
    setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
    setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);
    setNormalStateStyle(ui->RinsingPosition_PB, NONE_SB);

    isPresetPosition1Active     = false;
    isPresetPosition2Active     = false;
    isPresetPosition3Active     = false;
    isRinsingPosition1Active    = false;

    currentKeyState = CHAIR_DOWN_STATE;
}


void MainWindow::on_ChairDownward_PB_released()
{
    currentKeyState = WAITING_STATE;
}

void MainWindow::on_Setting_PB_pressed()
{
    sendCommand(SET);

    if(isSetActive){
        // Normal (OFF) state
        setNormalStateStyle(ui->Setting_PB, SETTING_SB);
    }else{
        // Active (ON) state
        setActiveStateStyle(ui->Setting_PB, SETTING_SB);
    }

    isSetActive = !isSetActive;
}

void MainWindow::on_Setting_PB_released()
{

}

void MainWindow::on_Reset_PB_pressed()
{
    sendCommand(RESET1);
    setActiveStateStyle(ui->Reset_PB, RESET_SB);
}


void MainWindow::on_Reset_PB_released()
{
    setNormalStateStyle(ui->Reset_PB, RESET_SB);
}


void MainWindow::on_CallAssist_PB_pressed()
{
    sendCommand(CALLASSIST);

    setActiveStateStyle(ui->CallAssist_PB, CALLASSIST_SB);
}


void MainWindow::on_CallAssist_PB_released()
{
    setNormalStateStyle(ui->CallAssist_PB, CALLASSIST_SB);
}

/********** Custom Function Definition ***********/
void setIconOnButton(QPushButton *button, bool flat, bool transparent) {
//    QIcon icon(main_icon_address + iconName);
//    button->setIcon(icon);
//    button->setIconSize(QSize(icon_global_size, icon_global_size));
    if (flat) button->setFlat(true);
    if (transparent) button->setStyleSheet("background-color: transparent; border: none;");
}



void setNormalStateStyle(QPushButton *button, uint8_t whichSpecialButton){

    if (whichSpecialButton == CIRCLE_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: transparent;"
                    "border: 5px solid black;"
                    "color: black;"
                    "border-radius: 40px;"
                    "}"
                    "QPushButton:focus {"
                    "    outline: none;"
                    "}"
        );
    }
    else if (whichSpecialButton == CALLASSIST_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #f9f937;"
                    "border: 5px solid black;"
                    "color: black;"
                    "border-radius: 10px;"
                    "}"
        );
    }
    else if (whichSpecialButton == SETTING_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #49f937;"
                    "border: 5px solid black;"
                    "color: black;"
                    "border-radius: 10px;"
                    "}"
        );
    }
    else if (whichSpecialButton == RESET_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #f93737;"
                    "border: 5px solid black;"
                    "color: black;"
                    "border-radius: 10px;"
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


void setActiveStateStyle(QPushButton *button, uint8_t whichSpecialButton){

    if (whichSpecialButton == CIRCLE_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #37c7f9;"
                    "border: 5px solid black;"
                    "color: white;"
                    "border-radius: 40px;"
                    "}"
                    "QPushButton:focus {"
                    "    outline: none;"
                    "}"
        );
    }
    else if (whichSpecialButton == CALLASSIST_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #b5b529;"
                    "border: 5px solid black;"
                    "color: white;"
                    "border-radius: 10px;"
                    "}"
        );
    }
    else if (whichSpecialButton == SETTING_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #35b029;"
                    "border: 5px solid black;"
                    "color: white;"
                    "border-radius: 10px;"
                    "}"
        );
    }
    else if (whichSpecialButton == RESET_SB) {
        button->setStyleSheet(
                    "QPushButton {"
                    "background-color: #b02929;"
                    "border: 5px solid black;"
                    "color: white;"
                    "border-radius: 10px;"
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

void setChairDirectionsStyle(QPushButton *button)
{
    button->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "}"
        "QPushButton:focus {"
        "    outline: none;"
        "}"
    );
}

/********** Custom Function of MainWindow Object Definition ***********/
void MainWindow::setupSerialPort()
{

    /*** SERIAL PORT 1 SETUP - START ***/
    serialPort1 = new QSerialPort(this);

    serialPort1->setPortName("/dev/ttyS1");
    serialPort1->setBaudRate(QSerialPort::Baud115200);
    serialPort1->setDataBits(QSerialPort::Data8);
    serialPort1->setParity(QSerialPort::NoParity);
    serialPort1->setStopBits(QSerialPort::OneStop);
    serialPort1->setFlowControl(QSerialPort::NoFlowControl);

    connect(serialPort1, &QSerialPort::readyRead, this, &MainWindow::readVoiceAssistData);

    if (serialPort1->open(QIODevice::ReadOnly)) {
        qDebug() << "Serial port 1 opened successfully.";
    } else {
        qDebug() << "Failed to open serial port 1:" << serialPort1->errorString();
    }
    /*** SERIAL PORT 1 SETUP - END ***/

    /*** SERIAL PORT 2 SETUP - START***/
    serialPort2 = new QSerialPort(this);

    serialPort2->setPortName("/dev/ttyS2");
    serialPort2->setBaudRate(QSerialPort::Baud115200);
    serialPort2->setDataBits(QSerialPort::Data8);
    serialPort2->setParity(QSerialPort::NoParity);
    serialPort2->setStopBits(QSerialPort::OneStop);
    serialPort2->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort2->open(QIODevice::WriteOnly)) {
        qDebug() << "Serial port 2 opened successfully.";
    } else {
        qDebug() << "Failed to open serial port 2:" << serialPort2->errorString();
    }
    /*** SERIAL PORT 2 SETUP - END ***/
}

void MainWindow::readVoiceAssistData()
{
    QByteArray data = serialPort1->readAll();

    if(isSerialPort2Free){
        serialPort2->write(data);
    }else{
        voiceAssistCommand.clear();
        voiceAssistCommand = data;
        timerVoiceAssist->start();
    }

    qDebug() << "Received data:" << data;

    /**** DETECTING COMMAND - START ****/
    uint32_t value = 0;
    for (int i = 0; i < data.size(); ++i) {
        value |= (static_cast<uint8_t>(data[i]) << (8 * (data.size() - i - 1)));
    }

    uint8_t firstByte = (uint8_t) ((value & 0xFF000000) >> 24);
    if (firstByte != 0x7F)
    {
        qDebug() << "Wrong First byte";
        return;
    }

    uint8_t secondByte = (uint8_t) ((value & 0x00FF0000) >> 16);
    uint8_t frameCmd = (uint8_t) ((value & 0x0000FF00) >> 8);
    uint8_t frameCRC = (uint8_t) ((value & 0x000000FF));
    uint8_t calculatedCRC = firstByte+secondByte+frameCmd;

    if (frameCRC != calculatedCRC)
    {
        qDebug() << "Wrong CRC - frameCRC: " << QString::number(frameCRC, 16).toUpper() << " calculatedCRC: " << QString::number(calculatedCRC, 16).toUpper();
        return;
    }

    if(frameCmd == DR_1) on_PresetPositionGroupA_PB_pressed();
    if(frameCmd == DR_2) on_PresetPositionGroupB_PB_pressed();
    if(frameCmd == DR_3) on_PresetPositionGroupC_PB_pressed();
    if(frameCmd == DR_4) on_PresetPositionGroupD_PB_pressed();
    /**** DETECTING COMMAND - STOP ****/
}

void MainWindow::setupTimer()
{
    timer = new QTimer(this);
    timer->setInterval(intervalTime); //ms
    connect(timer, &QTimer::timeout, this, &MainWindow::checkState);
    timer->start();

    timerVoiceAssist = new QTimer(this);
    timerVoiceAssist->setInterval(intervalTime/2); //ms
    connect(timerVoiceAssist, &QTimer::timeout, this, &MainWindow::sendVoiceAssistCmd);
}

void MainWindow::sendCommand(uint8_t command)
{
    isSerialPort2Free = false;
    static QString commandsList[] = {
        "NONE",
        "CHAIRUP",
        "CHAIRDOWN",
        "BACKRESTFORWARD",
        "BACKRESTBACKWARD",
        "PREPOSITION_A1",
        "PREPOSITION_A2",
        "PREPOSITION_A3",
        "PREPOSITION_B1",
        "PREPOSITION_B2",
        "PREPOSITION_B3",
        "PREPOSITION_C1",
        "PREPOSITION_C2",
        "PREPOSITION_C3",
        "PREPOSITION_D1",
        "PREPOSITION_D2",
        "PREPOSITION_D3",
        "RESET1",
        "RESET2",
        "OPERATINGLIGHT",
        "WATERHEATER",
        "BOWLRINSING",
        "CUPFILLER",
        "CALLASSIST",
        "SET",
        "OK",
        "ERROR",
        "FILMVIEW",
        "DR_1",
        "DR_2",
        "DR_3",
        "DR_4"
    };

    uint8_t startByte = 0x7F;
    uint8_t secondByte = 0x01;
    uint8_t crc = startByte + secondByte + command;
    QByteArray data;
    data.append((char)startByte);
    data.append((char)secondByte);
    data.append((char)command);
    data.append((char)crc);

    serialPort2->write(data);
    qDebug() << "Command sent:" << commandsList[command] << " - " << data.toHex();
    isSerialPort2Free = true;
}

void MainWindow::sendVoiceAssistCmd()
{
    if(isSerialPort2Free){
        timerVoiceAssist->stop();
        serialPort2->write(voiceAssistCommand);
        voiceAssistCommand.clear();
    }
}

void MainWindow::checkState()
{

    switch (currentKeyState) {

        case WAITING_STATE:

            break;

        case CHAIR_UP_STATE:
            qDebug() << "CHAIR_UP_STATE";
            sendCommand(CHAIRUP);
            break;

        case CHAIR_DOWN_STATE:
            qDebug() << "CHAIR_DOWN_STATE";
            sendCommand(CHAIRDOWN);
            break;

        case BACKREST_FORWARD_STATE:
            qDebug() << "BACKREST_FORWARD_STATE";
            sendCommand(BACKRESTFORWARD);
            break;

        case BACKREST_BACKWARD_STATE:
            qDebug() << "BACKREST_BACKWARD_STATE";
            sendCommand(BACKRESTBACKWARD);
            break;

        default:
            currentKeyState = WAITING_STATE;
    }
}






















































