#include "serialport.h"

SerialPort::SerialPort()
{
    setPortName(portPath);
    createLists();
}

/* 
* @brief Method to get port path for serial
*
*
* @param none
* @return none
*/
const QString &SerialPort::getPortPath() const
{
    return portPath;
}

/* 
* @brief Method to set port path for serial
*
*
* @param none
* @return none
*/
void SerialPort::setPortPath(const QString &newPortPath)
{
    portPath = newPortPath;
}

/* 
* @brief Method to create serial port parameters lists
*
*
* @param none
* @return none
*/
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
