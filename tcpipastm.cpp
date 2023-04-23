//нужно сделать: очередь для нескольких файлов передачи, повторну отправку, прием данных по ASTM
//нужно проверить несколько фреймов у посылке

#include "tcpipastm.h"
//#include "globals.h"
//#include "workfile.h"

#include <QDataStream>

//#define ENQ 0x05
//#define ACK 0x06
//#define EOT 0x04
//#define STX 0x02
//#define ETX 0x03
//#define ETB 0x17
//#define CR 0x0D
//#define LF 0x0A
//#define NAK 0x15
//#define FN 0x31
//#define time_tcpip 1000
//#define transmittingmaximumsize 1024
//#define numstr_savefilesettings_ip 69
//#define numstr_savefilesettings_port 70
//#define numstr_savefilesettings_language 0
//#define numstr_savefilesettings_log_active 68


tcpipastm::tcpipastm(QObject *parent) : QObject(parent)
{
//    timer_tcpip = new QTimer;
//    stateProtocolTcpIp = NEUTRAL;
    socket = new QTcpSocket(this);
//    arr_receivedData.clear();
//    arr_dataToSend.clear();
//    frame_number = 1;
//    nak_count = 0;
//    add_frame_transmitting = false;

    QObject::connect(socket, &QTcpSocket::readyRead, this, &tcpipastm::slotReadyRead);
    //QObject::connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
//    QObject::connect(timer_tcpip, &QTimer::timeout, this, &tcpipastm::timeOutTimerTcpip);
//    QObject::connect(this, &tcpipastm::signalState, this, &tcpipastm::stateASTM);


}

//void tcpipastm::sendToServer(QString &str)
//{
// //проверяем не передается ли чтото
//    if(arr_dataToSend.size() != 0){
//        qDebug() << "занято!еще не передалось";
//        return;
//    }

// //упаковуем у низкий уровень ASTM
//    arr_dataToSend.append(str);
//    emit this->signalState();
//}

//void tcpipastm::highASTM(QString &highlevel, QString serial_number_device, QString str_date, QString number_patient,
//                         QString type_measurement, QString value_gl, int value_gl_limit, QString value_lc, int value_lc_limit)
//{
//    highlevel.clear();
//    quint8 field_cr = CR;

//    QString str_H;
//    str_H.append("H|||||||||");
//    str_H.append(serial_number_device);
//    str_H.append("||P|1394-97|");
//    str_H.append(str_date);
//    str_H.append(field_cr);
//    highlevel.append(str_H);

//    QString str_P;
//    str_P.append("P|1|");
//    str_P.append(number_patient);
//    str_P.append(field_cr);
//    highlevel.append(str_P);

//    QString str_O;
//    str_O.append("O|1||||||||||||||");
//    str_O.append(type_measurement);
//    str_O.append(field_cr);
//    highlevel.append(str_O);

//    QString str_R;
//    str_R.append("R|1||");
//    if(value_gl.isEmpty() == false){
//        str_R.append(value_gl);
//        str_R.append("|mool/l|");
//        if(value_gl_limit == -1) str_R.append("Lower limit");
//        else if(value_gl_limit == 1) str_R.append("Upper limit");
//    }
//    else if(value_lc.isEmpty() == false){
//        str_R.append(value_lc);
//        str_R.append("|mool/l|");
//        if(value_lc_limit == -1) str_R.append("Lower limit");
//        else if(value_lc_limit == 1) str_R.append("Upper limit");
//    }
//    str_R.append("|||||||");
//    str_R.append(str_date);
//    str_R.append(field_cr);
//    highlevel.append(str_R);

//    QString str_C;
//    str_C.append("C|1|I|");
//    if(value_gl.isEmpty() == false) str_C.append("Glucose result");
//    else if(value_lc.isEmpty() == false) str_C.append("Lactate result");
//    str_C.append("|I");
//    str_C.append(field_cr);
//    highlevel.append(str_C);

//    if(value_gl.isEmpty() == false && value_lc.isEmpty() == false){
//        QString str_R2;
//        str_R2.append("R|2||");
//        str_R2.append(value_lc);
//        str_R2.append("|mool/l|");
//        if(value_lc_limit == -1) str_R2.append("Lower limit");
//        else if(value_lc_limit == 1) str_R2.append("Upper limit");
//        str_R2.append("|||||||");
//        str_R2.append(str_date);
//        str_R2.append("||");
//        str_R2.append(field_cr);
//        highlevel.append(str_R2);

//        QString str_C2;
//        str_C2.append("C|2|I|");
//        str_C2.append("Lactate result");
//        str_C2.append("|I");
//        str_C2.append(field_cr);
//        highlevel.append(str_C2);
//    }

//    QString str_L;
//    str_L.append("L|1|N");
//    str_L.append(field_cr);
//    highlevel.append(str_L);
//}

//void tcpipastm::connectToServer()
//{
//    /*
//    if(socket->error() != -1){
//        qDebug() << "connectToHost error!!!!!!";
//        return;
//    }*/

//    QString ip(file_settings_strings[numstr_savefilesettings_ip]);
//    QString str_port(file_settings_strings[numstr_savefilesettings_port]);
//    int port = str_port.toInt();
//    socket->connectToHost(ip, port);
//    //qDebug() << "connectToServer()" << socket->state() << ip << port;
//}

//void tcpipastm::disconnectToServer()
//{
//    socket->disconnectFromHost();
//}

void tcpipastm::slotReadyRead()
{
    //qDebug() << "slotReadyRead()";
    QByteArray current_received;
    current_received.clear();
    current_received = socket->readAll();

//    for(int i = 0; i < current_received.length(); i++){
//        if(current_received[i] == ENQ || current_received[i] == ACK || current_received[i] == EOT || current_received[i] == NAK || current_received[i] == STX){
//            if(arr_receivedData[0] == EOT && current_received[i] == ENQ){
//                break;
//            }
//            else {
//                arr_receivedData.clear();
//                arr_receivedData.append(current_received.at(i));
//            }
//        }
//        else arr_receivedData.append(current_received.at(i));
//    }

//    //проверка на не мусор
//    if(arr_receivedData[0] != ENQ && arr_receivedData[0] != ACK && arr_receivedData[0] != EOT && arr_receivedData[0] != NAK && arr_receivedData[0] != STX){
//        arr_receivedData.clear();
//        return;
//    }
//    //qDebug() << "slotReadyRead()" << arr_receivedData;
//    emit this->signalState();
}

//void tcpipastm::stateASTM()
//{
//    //qDebug() << "при входе stateASTM stateProtocolTcpIp" << stateProtocolTcpIp;

//    int size_arr_transmitting = arr_dataToSend.length();

//    if(stateProtocolTcpIp == NEUTRAL){
//        this->writeComand(ENQ);
//        stateProtocolTcpIp = ESTABLISHMENT;
//        //qDebug() << "establishment state";
//        timer_tcpip->start(time_tcpip);
//    }
//    else if(stateProtocolTcpIp == ESTABLISHMENT && this->checkComand(ACK)){
//        //qDebug() << "read ack";
//        this->transmittingFrame();
//        stateProtocolTcpIp = TRANSMIT;
//        qDebug() << "transmit state";
//        timer_tcpip->start(time_tcpip);
//        if(size_arr_transmitting > transmittingmaximumsize){
//            add_frame_transmitting = true;
//        }
//        else add_frame_transmitting = false;
//    }
//    else if(stateProtocolTcpIp == TRANSMIT && this->checkComand(ACK)){
//        //qDebug() << "read ack";
//        if(size_arr_transmitting > (frame_number * transmittingmaximumsize)){
//            this->transmittingFrame();
//            timer_tcpip->start(time_tcpip);
//            add_frame_transmitting = true;
//        }
//        else if(add_frame_transmitting == true){
//            this->transmittingFrame();
//            timer_tcpip->start(time_tcpip);
//            add_frame_transmitting = false;
//        }
//        else if(add_frame_transmitting == false){
//            this->writeComand(EOT);
//            qDebug() << "передано: " << arr_dataToSend;
// //переменная для записи у лог файл
//            QString string_log = arr_dataToSend;
//            this->writeToLog(string_log);
//            this->changeToNeutralTransmit();
//        }
//    }
//    else if((stateProtocolTcpIp == TRANSMIT || stateProtocolTcpIp == ESTABLISHMENT) && this->checkComand(NAK)){
//        nak_count++;
//        qDebug() << "nak_count" << nak_count;
//        if(nak_count > 6){
//            this->writeComand(EOT);
//            this->changeToNeutralTransmit();
//        }
//        else {
//            if(frame_number > 1) frame_number--;
//            this->transmittingFrame();
//            timer_tcpip->start(time_tcpip);
//        }
//    }

//    //qDebug() << "при выходе stateASTM stateProtocolTcpIp" << stateProtocolTcpIp;
//}

//bool tcpipastm::checkComand(quint8 comand)
//{
//    quint8 comand_received = arr_receivedData[0];
//    //qDebug() << "очищаем массив arr_receivedData!";
//    arr_receivedData.clear();

//    if(comand == comand_received) return true;
//    else return false;
//}

//void tcpipastm::transmittingFrame()
//{
//    QByteArray arr_writeFrame;
//    int start_byte_frame, stop_byte_frame;
//    quint8 etb_OR_etx;

//    stop_byte_frame = frame_number * transmittingmaximumsize;
//    start_byte_frame = stop_byte_frame - transmittingmaximumsize;
//    arr_writeFrame.clear();
//    arr_writeFrame.append(STX);
//    arr_writeFrame.append(FN + frame_number - 1);
//    for(int i = start_byte_frame; i < arr_dataToSend.length() && i < stop_byte_frame; i++){
//        arr_writeFrame.append(arr_dataToSend.at(i));

//    }

//    if(arr_dataToSend.length() > (frame_number * transmittingmaximumsize)){
//        etb_OR_etx = ETB;
//        frame_number++;
//    }
//    else {
//        etb_OR_etx = ETX;
//    }
//    arr_writeFrame.append(etb_OR_etx);
//    int nul = 0;
//    arr_writeFrame.append(nul);
//    arr_writeFrame.append(nul);
//    arr_writeFrame.append(CR);
//    arr_writeFrame.append(LF);
//    quint8 c1, c2;
//    quint8 c = this->createCheckSum(arr_writeFrame);
//    c1 = c >> 4;
//    c2 = c & 0x0F;
//    int numb_arr1 = arr_writeFrame.length() - 4;
//    int numb_arr2 = arr_writeFrame.length() - 3;
//    //делаем с quint8 символ hex
//    QString hex1 = QString::number(c1, 16);
//    QString hex2 = QString::number(c2, 16);
//    hex1 = hex1.toUpper();
//    hex2 = hex2.toUpper();
//    QByteArray temp_ar;
//    temp_ar.append(hex1);
//    temp_ar.append(hex2);
//    arr_writeFrame[numb_arr1] = temp_ar[0];
//    arr_writeFrame[numb_arr2] = temp_ar[1];

//    //qDebug() << "transmittingFrame arr_writeFrame" << arr_writeFrame;
//    this->writeFrame(arr_writeFrame);
//}

void tcpipastm::writeFrame(const QByteArray &arr_writeFrame)
{
    QByteArray send_data;
    send_data.clear();
    QDataStream out_tcp(&send_data, QIODevice::WriteOnly);
    out_tcp.setVersion(QDataStream::Qt_5_7);
    foreach (quint8 byte, arr_writeFrame) {
        out_tcp << byte;
    }
    socket->write(send_data);
}

//void tcpipastm::timeOutTimerTcpip()
//{
//    if(stateProtocolTcpIp == TRANSMIT || stateProtocolTcpIp == ESTABLISHMENT){
//        qDebug() << "timeout transmit";
//        this->writeComand(EOT);
//        this->changeToNeutralTransmit();
//    }
//}

//quint8 tcpipastm::createCheckSum(const QByteArray &arr)
//{
//    int temp = 0;
//    for(int i = 1; i <= arr.length() - 5; i++){
//        temp += arr.at(i);
//    }
//    quint8 c = temp;

//    return c;
//}

void tcpipastm::writeComand(quint8 comand)
{   
    QByteArray send_data;
    send_data.clear();
    QDataStream out_tcp(&send_data, QIODevice::WriteOnly);
    out_tcp.setVersion(QDataStream::Qt_5_7);
    out_tcp << comand;
    socket->write(send_data);
    //qDebug() << "writeComand()" << comand;
}

//void tcpipastm::changeToNeutralTransmit()
//{
//    stateProtocolTcpIp = NEUTRAL;
//    timer_tcpip->stop();
//    frame_number = 1;
//    nak_count = 0;
//    arr_dataToSend.clear();
//    //qDebug() << "changeToNeutralTransmit()!!";
//}

