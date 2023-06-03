#ifndef TCPIPASTM_H
#define TCPIPASTM_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
//#include <QTimer>
//#include <QByteArray>


class tcpipastm : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpipastm();
//    void sendToServer(QString &);
//    void highASTM(QString &, QString, QString, QString, QString, QString, int, QString, int);
//    void connectToServer();
//    void disconnectToServer();
    QString getDataReceived();
    void writeFrame(const QByteArray &);


signals:
//    void signalState();
    void requestGetRepositories();
    void requestGetRepositoriesUP();
    void requestGetRepositoriesDOWN();

public slots:
    void incomingConnection(qintptr socketDescriptor);

private slots:
//   void stateASTM();
   void slotReadyRead();
//   void timeOutTimerTcpip();

private:
//    bool checkComand(quint8);
//    void transmittingFrame();
//    void writeFrame(const QByteArray &);
//    quint8 createCheckSum(const QByteArray &);
    void writeComand(quint8);
//    void changeToNeutralTransmit();


private:
    QTcpSocket *socket;
    QVector <QTcpSocket*> Sockets;
    QString data_received;
//    enum statesProtocolTcpIp{
//        NEUTRAL,
//        ESTABLISHMENT,
//        TRANSFER,
//        TRANSMIT,
//        RECEIVE,
//        TERMINATION
//    };
//    statesProtocolTcpIp stateProtocolTcpIp;
//    QTimer *timer_tcpip;
//    QByteArray arr_receivedData;
//    QByteArray arr_dataToSend;
//    int frame_number;
//    int nak_count;
//    bool add_frame_transmitting;
};
#endif // TCPIPASTM_H
