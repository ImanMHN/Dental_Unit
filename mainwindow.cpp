#include "mainwindow.h"
#include "ui_mainwindow.h"

/********** Custom variable Definition ***********/
static QString  main_icon_address = "/opt/DentalUnit/bin/icon/";
static uint8_t  icon_global_size = 70;
bool            isResetUP = true;
bool            isButtonDirActive = false;
uint8_t         intervalTime = 100;
uint8_t         currentKeyState = WAITING_STATE;
uint16_t        enteringSettingModeTime = 0;
uint16_t        cupFillingTime = 1000;
uint16_t        tmpTimeKeeper = 0;
uint32_t        flushTime = 2000; //5*60*1000;


/********** Custom Function Declaration ***********/
void setIconOnButton(QPushButton *button, const QString &iconName, bool flat = true, bool transparent = true);
void setNormalStateStyle(QPushButton *button, uint8_t whichSpecialButton = NONE_SB);
void setActiveStateStyle(QPushButton *button, uint8_t whichSpecialButton = NONE_SB);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    setupSerialPort();

    setupTimer();

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

    setIconOnButton(ui->CallAssist_PB, "callassist.png", false, true);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PresetPositionGroupA_PB_clicked()
{
    if (!isPresetPositionGroupA_Active) {

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
    }
}

void MainWindow::on_PresetPositionGroupB_PB_clicked()
{
    if (!isPresetPositionGroupB_Active) {

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
    }
}


void MainWindow::on_PresetPositionGroupC_PB_clicked()
{
    if (!isPresetPositionGroupC_Active) {

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
    }
}


void MainWindow::on_PresetPositionGroupD_PB_clicked()
{
    if (!isPresetPositionGroupD_Active) {

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
    }
}


void MainWindow::on_PresetPosition1_PB_clicked()
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


void MainWindow::on_PresetPosition2_PB_clicked()
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


void MainWindow::on_PresetPosition3_PB_clicked()
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


void MainWindow::on_RinsingPosition_PB_clicked()
{
    if (!isRinsingPosition1Active) {

        setActiveStateStyle(ui->RinsingPosition_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition1_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition2_PB, NONE_SB);
        setNormalStateStyle(ui->PresetPosition3_PB, NONE_SB);

        isPresetPosition1Active     = false;
        isPresetPosition2Active     = false;
        isPresetPosition3Active     = false;
        isRinsingPosition1Active    = true;

        sendCommand(RINSING_POSITION);
    }
}



void MainWindow::on_WaterHeater_PB_clicked()
{
    sendCommand(WATERHEATER);

    if (isWaterHeaterActive) {
        // Normal (OFF) state
        setNormalStateStyle(ui->WaterHeater_PB, CIRCLE_SB);
    } else {
        // Active (ON) state
        setActiveStateStyle(ui->WaterHeater_PB, CIRCLE_SB);
    }

    // Change the state
    isWaterHeaterActive = !isWaterHeaterActive;
}

void MainWindow::on_CupFiller_PB_pressed()
{
    if(currentKeyState == SETTING_STATE)
    {
        currentKeyState = MOUTHWASH_SUPPLY_SETTING_STATE;
        setActiveStateStyle(ui->CupFiller_PB, CIRCLE_SB);
    }
}


void MainWindow::on_CupFiller_PB_released()
{
    qDebug() << "on_CupFiller_PB_released - cupFillingTime: " << cupFillingTime;

    if(currentKeyState == MOUTHWASH_SUPPLY_SETTING_STATE)
    {
        setNormalStateStyle(ui->CupFiller_PB, CIRCLE_SB);
        isCupFillerActive = false;
        currentKeyState = WAITING_STATE;
    } else {
        if (isCupFillerActive) {
            // Normal (OFF) state
            setNormalStateStyle(ui->CupFiller_PB, CIRCLE_SB);
            currentKeyState = WAITING_STATE;
        } else {
            // Active (ON) state
            setActiveStateStyle(ui->CupFiller_PB, CIRCLE_SB);
            currentKeyState = CUP_FILLING_START_STATE;
        }

        // Change the state
        isCupFillerActive = !isCupFillerActive;
    }
}

void MainWindow::on_OperatingLight_PB_clicked()
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
    setActiveStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
}


void MainWindow::on_BowlRinsing_PB_released()
{
    if (currentKeyState == WAITING_STATE)
    {
        currentKeyState = FLUSH_START_STATE;
    }
    else if(currentKeyState == SETTING_STATE)
    {
        flushTime = 2000; //(5*60*1000);
        currentKeyState = FLUSH_TIME_SETTING_STATE;
        setNormalStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
    }
    else if(currentKeyState == FLUSH_TIME_SETTING_STATE)
    {
        tmpTimeKeeper = 0;
        flushTime += 2000; // (5*60*1000);

        if (flushTime >= 4*2000){ //(4*5*60*1000)){ //4 times button pressed
            flushTime = 10*2000; //(10*5*60*1000);
            currentKeyState = FLUSH_START_STATE;
        }
        setNormalStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
    }
    else if(currentKeyState == FLUSH_START_STATE)
    {
        currentKeyState = WAITING_STATE;
        setNormalStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
    }
}

void MainWindow::on_FilmViewer_PB_clicked()
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
}


void MainWindow::on_BackrestForward_PB_released()
{
    currentKeyState = WAITING_STATE;
}


void MainWindow::on_BackrestBackward_PB_pressed()
{
    currentKeyState = BACKREST_BACKWARD_STATE;
}


void MainWindow::on_BackrestBackward_PB_released()
{
    currentKeyState = WAITING_STATE;
}


void MainWindow::on_ChairUpward_PB_pressed()
{
    currentKeyState = CHAIR_UP_STATE;
}


void MainWindow::on_ChairUpward_PB_released()
{
    currentKeyState = WAITING_STATE;
}


void MainWindow::on_ChairDownward_PB_pressed()
{
    currentKeyState = CHAIR_DOWN_STATE;
}


void MainWindow::on_ChairDownward_PB_released()
{
    currentKeyState = WAITING_STATE;
}

void MainWindow::on_Setting_PB_pressed()
{
    setActiveStateStyle(ui->Setting_PB, SETTING_SB);

    if(currentKeyState == SETTING_STATE){
        currentKeyState = WAITING_STATE;
    }else{
        currentKeyState = ENTERING_SETTING_STATE;
    }
}

void MainWindow::on_Setting_PB_released()
{
    setNormalStateStyle(ui->Setting_PB, SETTING_SB);

    if(enteringSettingModeTime < 3000)
        currentKeyState = WAITING_STATE;
}

void MainWindow::on_Reset_PB_pressed()
{
    setActiveStateStyle(ui->Reset_PB, RESET_SB);
}


void MainWindow::on_Reset_PB_released()
{
    setNormalStateStyle(ui->Reset_PB, RESET_SB);
    currentKeyState = RESET_STATE;
}


void MainWindow::on_CallAssist_PB_pressed()
{
    setActiveStateStyle(ui->CallAssist_PB, CALLASSIST_SB);
}


void MainWindow::on_CallAssist_PB_released()
{
    setNormalStateStyle(ui->CallAssist_PB, CALLASSIST_SB);
    sendCommand(CALLASSIST);
}

/********** Custom Function Definition ***********/
void setIconOnButton(QPushButton *button, const QString &iconName, bool flat, bool transparent) {
    QIcon icon(main_icon_address + iconName);
    button->setIcon(icon);
    button->setIconSize(QSize(icon_global_size, icon_global_size));
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

/********** Custom Function of MainWindow Object Definition ***********/
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

void MainWindow::setupTimer()
{
    timer = new QTimer(this);
    timer->setInterval(intervalTime); //ms
    connect(timer, &QTimer::timeout, this, &MainWindow::checkState);
    timer->start();
}

void MainWindow::sendCommand(uint8_t command)
{
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
        "RINSING_POSITION"
    };

    uint8_t startByte = 0x7F;
    uint8_t crc = startByte + command;
    QByteArray data;
    data.append((char)startByte);
    data.append((char)command);
    data.append((char)crc);

    serial->write(data);
//    qDebug() << "Command sent:" << commandsList[command] << " - " << data.toHex();
}

void MainWindow::checkState()
{

    switch (currentKeyState) {

        case WAITING_STATE:
            qDebug() << "WAITING_STATE";
            enteringSettingModeTime = 0;
            tmpTimeKeeper = 0;

            ui->SettingIndicator_RB->setChecked(false);
            ui->SettingIndicator_RB->setStyleSheet("");

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

        case ENTERING_SETTING_STATE:
            qDebug() << "ENTERING_SETTING_STATE";
            enteringSettingModeTime += intervalTime;

            if(enteringSettingModeTime > 3000)
            {
                currentKeyState = SETTING_STATE;

                ui->SettingIndicator_RB->setChecked(true);
                ui->SettingIndicator_RB->setStyleSheet(
                    "QRadioButton::indicator:checked {"
                    "    background-color: red;"
                    "}"
                );
            }

            break;

        case SETTING_STATE:
            qDebug() << "SETTING_STATE";
            setNormalStateStyle(ui->CupFiller_PB, CIRCLE_SB);
            setNormalStateStyle(ui->WaterHeater_PB, CIRCLE_SB);
            setNormalStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
            isCupFillerActive   = false;
            isWaterHeaterActive = false;
            isBowlRinsingActive = false;
            break;

        case MOUTHWASH_SUPPLY_SETTING_STATE:
            qDebug() << "MOUTHWASH_SUPPLY_SETTING_STATE";
            cupFillingTime += intervalTime;
            break;

        case CUP_FILLING_START_STATE:
            qDebug() << "CUP_FILLING_START_STATE";
            sendCommand(CUPFILLER);
            tmpTimeKeeper += intervalTime;

            if(tmpTimeKeeper > cupFillingTime)
            {
                setNormalStateStyle(ui->CupFiller_PB, CIRCLE_SB);
                currentKeyState = WAITING_STATE;
            }
            break;

        case FLUSH_TIME_SETTING_STATE:
            qDebug() << "FLUSH_TIME_SETTING_STATE";
            sendCommand(BOWLRINSING);
            tmpTimeKeeper += intervalTime;

            if(tmpTimeKeeper > 3000)
            {
                tmpTimeKeeper = 0;
                setActiveStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
                currentKeyState = FLUSH_START_STATE;
                qDebug() << "FLUSH_TIME_SETTING_STATE";
            }
            break;

        case FLUSH_START_STATE:
            qDebug() << "-------->>>> flushTime: "  << flushTime;
            sendCommand(BOWLRINSING);
            tmpTimeKeeper += intervalTime;

            setActiveStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
            ui->SettingIndicator_RB->setChecked(false);
            ui->SettingIndicator_RB->setStyleSheet("");

            if(tmpTimeKeeper > flushTime)
            {
                tmpTimeKeeper = 0;
                setNormalStateStyle(ui->BowlRinsing_PB, CIRCLE_SB);
                currentKeyState = WAITING_STATE;
            }
            break;

        case RESET_STATE:
            qDebug() << "RESET_STATE";

            if(isResetUP)
                sendCommand(CHAIRDOWN);
            else
                sendCommand(BACKRESTFORWARD);

            isResetUP = !isResetUP;

            tmpTimeKeeper += intervalTime;

            if(tmpTimeKeeper > 10000)
            {
                currentKeyState = WAITING_STATE;
            }
            break;

        default:
            currentKeyState = WAITING_STATE;
    }
}



































