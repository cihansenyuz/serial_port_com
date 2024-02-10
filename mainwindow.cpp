#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Serial Port Com");
    on_refreshComsButton_clicked(); // find available ports
    serial = new SerialPort;
    connect(serial,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(serial,SIGNAL(errorOccurred(QSerialPort::SerialPortError)),this,SLOT(on_errorOccurred(QSerialPort::SerialPortError)));
    setDefaultSerialParameters();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    ui->serialMessages->appendPlainText(ui->messageLine->text());
    ui->messageLine->clear();
}

void MainWindow::readData()
{
    ui->serialMessages->appendPlainText(serial->readAll());
}

void MainWindow::on_refreshComsButton_clicked()
{
    getComPorts();
    if (serial->isOpen() == 0) // set it empty if port is not open
        ui->comPortBox->setCurrentIndex(-1);     
}

void MainWindow::getComPorts()
{
    ui->comPortBox->clear();
    list = QSerialPortInfo::availablePorts();

    if(list.isEmpty())
    {
        ui->comPortBox->setCurrentIndex(-1);
        ui->infoMessages->appendPlainText("Error: No available com port found!");
    }
    QList<QString> portList;

    for(int i=0; i<list.length(); i++)
    {
        portList.push_back(list[i].portName());
    }
    ui->comPortBox->addItems(portList);
    ui->infoMessages->appendPlainText("Info: Available com port list updated.");
}

void MainWindow::on_connectButton_clicked()
{ 
    int index = -1;
    for(int i=0; i<list.length(); i++)
    {
        if(list[i].portName() == ui->comPortBox->currentText())
        {
            index = i;
            break;
        }
    }
    if(index != -1)
        serial->setPort(list[index]);
    
    serial->open(QIODeviceBase::ReadWrite);
}

void MainWindow::on_baudRateBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            serial->setBaudRate(SerialPort::BaudRate::Baud1200);
            break;
        case 1:
            serial->setBaudRate(SerialPort::BaudRate::Baud2400);
            break;
        case 2:
            serial->setBaudRate(SerialPort::BaudRate::Baud4800);
            break;
        case 3:
            serial->setBaudRate(SerialPort::BaudRate::Baud9600);
            break;
        case 4:
            serial->setBaudRate(SerialPort::BaudRate::Baud19200);
            break;
        case 5:
            serial->setBaudRate(SerialPort::BaudRate::Baud38400);
            break;
        case 6:
            serial->setBaudRate(SerialPort::BaudRate::Baud57600);
            break;
        case 7:
            serial->setBaudRate(SerialPort::BaudRate::Baud115200);
            break;
    }
}

void MainWindow::on_dataBitBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            serial->setDataBits(SerialPort::DataBits::Data5);
            break;
        case 1:
            serial->setDataBits(SerialPort::DataBits::Data6);
            break;
        case 2:
            serial->setDataBits(SerialPort::DataBits::Data7);
            break;
        case 3:
            serial->setDataBits(SerialPort::DataBits::Data8);
            break;
    }
}

void MainWindow::on_stopBitBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            serial->setStopBits(SerialPort::StopBits::OneStop);
            break;
        case 1:
            serial->setStopBits(SerialPort::StopBits::OneAndHalfStop);
            break;
        case 2:
            serial->setStopBits(SerialPort::StopBits::TwoStop);
            break;
    }
}

void MainWindow::on_parityBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            serial->setParity(SerialPort::Parity::NoParity);
            break;
        case 1:
            serial->setParity(SerialPort::Parity::EvenParity);
            break;
        case 2:
            serial->setParity(SerialPort::Parity::OddParity);
            break;
        case 3:
            serial->setParity(SerialPort::Parity::SpaceParity);
            break;
        case 4:
            serial->setParity(SerialPort::Parity::MarkParity);
            break;
    }
}

void MainWindow::on_flowControlBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            serial->setFlowControl(SerialPort::FlowControl::NoFlowControl);
            break;
        case 1:
            serial->setFlowControl(SerialPort::FlowControl::HardwareControl);
            break;
        case 2:
            serial->setFlowControl(SerialPort::FlowControl::SoftwareControl);
            break;
    }
}

void MainWindow::setDefaultSerialParameters()
{
    ui->baudRateBox->addItems(serial->baudRateList);
    ui->dataBitBox->addItems(serial->dataBitList);
    ui->stopBitBox->addItems(serial->stopBitList);
    ui->parityBox->addItems(serial->parityList);
    ui->flowControlBox->addItems(serial->flowControlList);

    ui->baudRateBox->setCurrentIndex(3);
    ui->dataBitBox->setCurrentIndex(3);
    ui->stopBitBox->setCurrentIndex(0);
    ui->parityBox->setCurrentIndex(0);
    ui->flowControlBox->setCurrentIndex(0);
}

void MainWindow::on_disconnectButton_clicked()
{
    if (serial->isOpen())
    {
        serial->close();
        ui->infoMessages->appendPlainText("Info: Port is closed");
    }
    else
        ui->infoMessages->appendPlainText("Info: No serial port is open or already closed");
}

void MainWindow::on_clearMessagePanelButton_clicked()
{
    ui->serialMessages->clear();
}

void MainWindow::on_clearInfoPanelButton_clicked()
{
    ui->infoMessages->clear();
}

void MainWindow::on_errorOccurred(QSerialPort::SerialPortError error)
{
    if (ui->comPortBox->currentIndex() == -1)
        ui->infoMessages->appendPlainText("Info: Please, select an available port first");
    else
    {
        if (error == QSerialPort::NoError)
            ui->infoMessages->appendPlainText("Info: Selected port is now open");
        else if (error == QSerialPort::OpenError)
            ui->infoMessages->appendPlainText("Error: cannot open selected port or already opened");
        else if (error == QSerialPort::DeviceNotFoundError)
            ui->infoMessages->appendPlainText("Error: Attempting to open an non-existing device. Refresh the port list");
        else if (error == QSerialPort::PermissionError)
            ui->infoMessages->appendPlainText("Error: Attempting to open an already opened device by another process or you don't have permissions");
        else if (error == QSerialPort::TimeoutError)
            ui->infoMessages->appendPlainText("Error: A timeout error occurred, try again");
        else if (error == QSerialPort::UnknownError)
            ui->infoMessages->appendPlainText("Error: An unidentified error occurred, try again");
    }
}