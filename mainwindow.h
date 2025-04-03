#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QTimer>
#include <QByteArray>
#include <QIcon>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


typedef enum
{
    CHAIRUP             = 0x01,
    CHAIRDOWN           = 0x02,
    BACKRESTFORWARD     = 0x03,
    BACKRESTBACKWARD    = 0x04,
    PREPOSITION_A1      = 0x05,
    PREPOSITION_A2      = 0x06,
    PREPOSITION_A3      = 0x07,
    PREPOSITION_B1      = 0x08,
    PREPOSITION_B2      = 0x09,
    PREPOSITION_B3      = 0x0A,
    PREPOSITION_C1      = 0x0B,
    PREPOSITION_C2      = 0x0C,
    PREPOSITION_C3      = 0x0D,
    PREPOSITION_D1      = 0x0E,
    PREPOSITION_D2      = 0x0F,
    PREPOSITION_D3      = 0x10,
    RESET1              = 0x11,
    RESET2              = 0x12,
    OPERATINGLIGHT      = 0x13,
    WATERHEATER         = 0x14,
    BOWLRINSING         = 0x15,
    CUPFILLER           = 0x16,
    CALLASSIST          = 0x17,
    SET                 = 0x18,
    OK                  = 0x19,
    ERROR               = 0x1A,
    FILMVIEW            = 0x1B,
    RINSING_POSITION    = 0x1C
} SerialCommands;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_PresetPositionGroupA_PB_clicked();

    void on_PresetPositionGroupB_PB_clicked();

    void on_PresetPositionGroupC_PB_clicked();

    void on_PresetPositionGroupD_PB_clicked();

    void on_PresetPosition1_PB_clicked();

    void on_PresetPosition2_PB_clicked();

    void on_PresetPosition3_PB_clicked();

    void on_RinsingPosition_PB_clicked();

    void on_WaterHeater_PB_clicked();

    void on_CupFiller_PB_clicked();

    void on_OperatingLight_PB_clicked();

    void on_BowlRinsing_PB_clicked();

    void on_FilmViewer_PB_clicked();

    void on_BackrestForward_PB_pressed();

    void on_BackrestForward_PB_released();

    void on_BackrestBackward_PB_pressed();

    void on_BackrestBackward_PB_released();

    void on_ChairUpward_PB_pressed();

    void on_ChairUpward_PB_released();

    void on_ChairDownward_PB_pressed();

    void on_ChairDownward_PB_released();

    void sendCommand(uint8_t command);

private:
    Ui::MainWindow *ui;

    bool isPresetPositionGroupA_Active = false;
    bool isPresetPositionGroupB_Active = false;
    bool isPresetPositionGroupC_Active = false;
    bool isPresetPositionGroupD_Active = false;

    bool isPresetPosition1Active    = false;
    bool isPresetPosition2Active    = false;
    bool isPresetPosition3Active    = false;
    bool isRinsingPosition1Active   = false;

    bool isWaterHeaterActive    = false;
    bool isCupFillerActive      = false;
    bool isOperatingLightActive = false;
    bool isBowlRinsingActive    = false;
    bool isFilmViewerActive     = false;

    QSerialPort *serial;
    void setupSerialPort();

};
#endif // MAINWINDOW_H
