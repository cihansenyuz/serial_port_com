#include "serialport.h"


SerialPort::SerialPort()
{
    setPortName(portPath);
    createLists();
}

const QString &SerialPort::getPortPath() const
{
    return portPath;
}

void SerialPort::setPortPath(const QString &newPortPath)
{
    portPath = newPortPath;
}

void SerialPort::createLists()
{
    baudRateList.append("1200");
    baudRateList.append("2400");
    baudRateList.append("4800");
    baudRateList.append("9600");
    baudRateList.append("19200");
    baudRateList.append("38400");
    baudRateList.append("57600");
    baudRateList.append("115200");

    dataBitList.append("5 bits");
    dataBitList.append("6 bits");
    dataBitList.append("7 bits");
    dataBitList.append("8 bits");

    stopBitList.append("1 bit");
    stopBitList.append("1.5 bits");
    stopBitList.append("2 bits");

    parityList.append("no parity");
    parityList.append("even");
    parityList.append("odd");
    parityList.append("space");
    parityList.append("mark");

    flowControlList.append("no flow control");
    flowControlList.append("hardware");
    flowControlList.append("software");
}

void SerialPort::sendMessage1602(QByteArray text)
{
    text = text.append(terminator1602);
    this->write(text);
}

void SerialPort::sendCommand1602(const char commandChar)
{
    this->command.clear();
    this->command.append(commandChar);
    this->command.append(terminator1602);
    this->write(this->command);
}

void SerialPort::sendSettings1602(const char selection1, const char selection2, const char selection3)
{
    this->sendCommand1602(options1602);
    this->command.clear();
    this->command.append(selection1);
    this->command.append(selection2);
    this->command.append(selection3);
    this->command.append(terminator1602);
    this->write(this->command);
}
