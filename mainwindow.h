/**
  ******************************************************************************
  * @file    mainwindow.h
  * @author  Cihan Senyuz
  * @brief   Header for mainwindow.cpp file.
  *                 This file contains the common defines of the application.
  * 
  *     Features;
  *     - Finding available serial ports and opening, closing ports.
  *     - UART communication parameters settings (Baud rate, data bit, stop bit, parity, flow control)
  *     - A message line to send the text to the serial port
  *     - A text panel to show recieved messages from the serial port
  *     - A text panel to show information or error messages
  * 
  ******************************************************************************
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getComPorts();

private slots:
    void on_sendButton_clicked();
    void readData();
    void on_connectButton_clicked();
    void on_refreshComsButton_clicked();
    void on_disconnectButton_clicked();
    void on_clearMessagePanelButton_clicked();
    void on_clearInfoPanelButton_clicked();
    void setDefaultSerialParameters(void);
    void on_baudRateBox_currentIndexChanged(int index);
    void on_dataBitBox_currentIndexChanged(int index);
    void on_stopBitBox_currentIndexChanged(int index);
    void on_parityBox_currentIndexChanged(int index);
    void on_flowControlBox_currentIndexChanged(int index);
    void on_errorOccurred(QSerialPort::SerialPortError error);

private:
    QList<QSerialPortInfo> list;
    SerialPort* serial;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
