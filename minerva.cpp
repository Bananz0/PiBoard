#include "minerva.h"
#include "wiringPiFake.h"
#include <thread>

//Delay times for sending and receiving bits and bytes
#define BITDELAY 1000
#define BYTEDELAY 100
#define USEGPIO true
#define USEBIGDATA true
#define SYNC_TIMEOUT 1000000 
#define MAX_SYNC_RETRIES 5 
int syncPins[8] = { 2, 3, 4, 17 ,
                    14, 15, 18, 13};
 
Minerva::Minerva() {
    //initialize GPIO
    initializeGPIO();
    //set send pins
    dataPins[0] = 22;
    dataPins[1] = 26;
    dataPins[2] = 6;
    dataPins[3] = 0;
    //set receive pins
    dataPins[4] = 23;
    dataPins[5] = 20;
    dataPins[6] = 12;
    dataPins[7] = 1;
    //set misc pins
    dataPins[8] = 8;
    dataPins[9] = 9;
    //set window size
    winSize = QSize(800, 600);
    //initialize drawDataPacket
    sendDataPacket = new drawData;
    receiveDataPacket = new drawData;
    lastSentDataPacket = new drawData;
    //initialize data packets
    posData = QByteArray();
    flagsData = QByteArray();
    penData = QByteArray();
    sizeData = QByteArray();

    //initialize the mutexes
    sendLock = new QMutex();
    recLock = new QMutex();
}

Minerva::~Minerva() {
    //delete epimetheus;
    //delete prometheus;
    //delete epimetheusThread;
    //delete prometheusThread;
    delete lastReceivedDataPacket;
    delete lastSentDataPacket;
    delete sendDataPacket;
    delete receiveDataPacket;
}

void Minerva::getServerWindowSize(QSize hermesSize) {
    winSize = hermesSize;
};

QSize Minerva::setClentWindowSize() {
    return winSize;
}

//QString Minerva::testConnection(){
//    QString connectionStatus;
//    int connectionStatusNum = 0;
//    int connectionStatusNumSent = 0;
//    for (int i = 0; i < 4; i++){
//        int outputPin = dataPins[i%4];
//        int inputPin = dataPins[ (i%4 + 4)];
//        digitalWrite(outputPin,1);// : digitalWrite(outputPin,0);
//        connectionStatusNum += 1;//: connectionStatusNum = connectionStatusNum;
//        connectionStatusNumSent += receiveBit(inputPin);
//        delay(100);
//        digitalWrite(outputPin,0);
//        qDebug() << "Send Pin: "<< outputPin << "Receive Pin: " << inputPin << "Data Received: "<< connectionStatusNumSent;
//    }
//     qDebug() << "Data Sent: " <<connectionStatusNum << " Data received: " << connectionStatusNumSent;
//    if (connectionStatusNum != connectionStatusNumSent) {
//        connectionStatus = "Connection failed";
//    }
//    else {
//        connectionStatus = "Connection successful";
//    }
//    qDebug() << connectionStatus;
//    return connectionStatus;
//}

void Minerva::selectDataPin(int pinNumber, int dataModeNum) {
    pinMode(dataPins[pinNumber], dataModeNum);
}

void Minerva::initializeGPIO() {
    wiringPiSetupGpio();
}

void Minerva::serverMode() {
    pinMode(22, OUTPUT);
    pinMode(26, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(17, INPUT);
}

void Minerva::clientMode() {
    pinMode(23, INPUT);
    pinMode(20, INPUT);
    pinMode(0, INPUT);
    pinMode(9, INPUT);
    pinMode(14, INPUT);
    pinMode(15, INPUT);
    pinMode(18, INPUT);
    pinMode(13, OUTPUT);
}

//https://doc.qt.io/qt-6/qdatastream.html
void Minerva::encodeData() {
    //sendLock->lock();
    //check if data has changed before sending
    if (lastSentDataPacket != nullptr && *sendDataPacket == *lastSentDataPacket) {
        //qDebug() << "No new data to send";
        return;
    }
    delete lastSentDataPacket;
    lastSentDataPacket = new drawData(*sendDataPacket);

    if (USEBIGDATA) {
        //Serialize Big Packet
        QDataStream bigStreamSender(&bigData, QDataStream::WriteOnly);
        //Lock data when sending 
        sendLock->lock();
        bigStreamSender << sendDataPacket->startPoint;
        bigStreamSender << sendDataPacket->movingPoint;
        bigStreamSender << sendDataPacket->endPoint;
        bigStreamSender << sendDataPacket->clearCanvasFlag;
        bigStreamSender << sendDataPacket->drawMode;
        bigStreamSender << sendDataPacket->pen;
        bigStreamSender << sendDataPacket->windowSize;
        sendLock->unlock();
        //unlock data when sending
        //Queueing big packet
        dataQueue.enqueue(bigData);

        qDebug() << "Send data queue size is :" << dataQueue.size();
    }
    else if (!USEBIGDATA) {
        //Serialize Individual Packets
        QDataStream posStreamSender(&posData, QDataStream::WriteOnly);
        QDataStream flagsStreamSender(&flagsData, QDataStream::WriteOnly);
        QDataStream penStreamSender(&penData, QDataStream::WriteOnly);
        QDataStream sizeStreamSender(&sizeData, QDataStream::WriteOnly);
        sendLock->lock();
        posStreamSender << sendDataPacket->startPoint;
        posStreamSender << sendDataPacket->movingPoint;
        posStreamSender << sendDataPacket->endPoint;
        flagsStreamSender << sendDataPacket->clearCanvasFlag;
        flagsStreamSender << sendDataPacket->drawMode;
        penStreamSender << sendDataPacket->pen;
        sizeStreamSender << sendDataPacket->windowSize;
        sendLock->unlock();
        //Queueing data to send over multiple wires
        posQueue.enqueue(posData);
        flagsQueue.enqueue(flagsData);
        penQueue.enqueue(penData);
        sizeQueue.enqueue(sizeData);
    }
    //    //Finding out the data size for transmission
    //    qDebug() << posData.size() << " Position Data";
    //    qDebug() << flagsData.size() << " Flags Data";
    //    qDebug() << penData.size() << " Pen Data";
    //    qDebug() << sizeData.size() << " Size Data";
        //sendLock->unlock();
}

void Minerva::decodeData() {
    //recLock->lock();
    if (USEBIGDATA) {
        //if (dataQueue.isEmpty()){
        //    return;
        //}
        //bigData = dataQueue.dequeue();
        bigData = bigData_raw;
        //Deserializing Big Packet
        recLock->lock();
        QDataStream bigStream(&bigData, QDataStream::ReadOnly);
        bigStream >> receiveDataPacket->startPoint;
        bigStream >> receiveDataPacket->movingPoint;
        bigStream >> receiveDataPacket->endPoint;
        bigStream >> receiveDataPacket->clearCanvasFlag;
        bigStream >> receiveDataPacket->drawMode;
        bigStream >> receiveDataPacket->pen;
        bigStream >> receiveDataPacket->windowSize;
        recLock->unlock();
    }
    else if (!USEBIGDATA) {
        if (posQueue.isEmpty() || flagsQueue.isEmpty() || penQueue.isEmpty() || sizeQueue.isEmpty()) {
            return;
        }
        posData = posQueue.dequeue();
        flagsData = flagsQueue.dequeue();
        penData = penQueue.dequeue();
        sizeData = sizeQueue.dequeue();

        //Receiving Individual Packets
        QDataStream posStream(&posData, QDataStream::ReadOnly);
        QDataStream flagsStream(&flagsData, QDataStream::ReadOnly);
        QDataStream penStream(&penData, QDataStream::ReadOnly);
        QDataStream sizeStream(&sizeData, QDataStream::ReadOnly);
        recLock->lock();
        posStream >> receiveDataPacket->startPoint;
        posStream >> receiveDataPacket->movingPoint;
        posStream >> receiveDataPacket->endPoint;
        flagsStream >> receiveDataPacket->clearCanvasFlag;
        flagsStream >> receiveDataPacket->drawMode;
        penStream >> receiveDataPacket->pen;
        sizeStream >> receiveDataPacket->windowSize;
        recLock->unlock();
    }
    //qDebug() << "Receive data queue size is :" << dataQueue.size();
    //recLock->unlock();
}

void Minerva::sendBit(uint pinNumber, bool bitData) {
    if (bitData) {
		digitalWrite(dataPins[pinNumber], HIGH);
	}
    else {
        digitalWrite(dataPins[pinNumber], LOW);
    }
    delayMicroseconds(BITDELAY);
}

int Minerva::receiveBit(uint pinNumber) {
    bool bitValue = false;
    bitValue = digitalRead(dataPins[pinNumber]);
    delayMicroseconds(BITDELAY);
    return (int)bitValue;
}

void Minerva::sendData(QByteArray data, uint pinNumber) {
    for (int i = 0; i < data.size(); i++) {
        char byte = data[i]; // Get the byte at index i
        for (int j = 0; j < 8; j++) {
            bool bit = (byte >> j) & 0x01; // Extract the j-th bit from the byte
            sendBit(pinNumber, bit); // Send the bit using the sendBit function
        }
        delayMicroseconds(BYTEDELAY);
    }
}

QByteArray Minerva::receiveData(uint pinNumber, int expectedByteSize) {
    QByteArray receivedData;
    char currentByte = 0;
    int bitCount = 0;

    for (int i = 0; i < expectedByteSize * 8; i++) {
        bool bit = digitalRead(dataPins[pinNumber]);
        //bool bit = receiveBit(pinNumber);
        currentByte = (currentByte << 1) | bit;
        bitCount++;

        if (bitCount == 8) {
            receivedData.append(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
        delayMicroseconds(BYTEDELAY);
    }

    //qDebug() << "Received data size:" << receivedData.size();
    return receivedData;
}

void Minerva::sendBigData() {
    if (dataQueue.isEmpty()) {
        return;
    }
    qDebug() << "Big Data Size: " << bigData.size();
    if (USEGPIO) {
        sendData(dataQueue.dequeue(), 0);
    }
    else if (!USEGPIO) {
        QFile bigFile("bigData.dat");
        bigFile.open(QIODevice::WriteOnly);
        bigFile.write(dataQueue.dequeue());
    }
}

void Minerva::receiveBigData() {
    if (USEGPIO) {
        //dataQueue.enqueue(receiveData(4, 171));
        bigData_raw = receiveData(4, 177);
        qDebug() << bigData_raw;
    }
    else if (!USEGPIO) {
        QFile bigFile("bigData.dat");
        bigFile.open(QIODevice::ReadOnly);
        dataQueue.enqueue(bigFile.readAll());
    }

}

void Minerva::sendMultipleData() {
    if (posQueue.isEmpty() || flagsQueue.isEmpty() || penQueue.isEmpty() || sizeQueue.isEmpty()) {
        return;
    }
    if (USEGPIO) {
        sendData(posQueue.dequeue(), 1);
        sendData(flagsQueue.dequeue(), 2);
        sendData(penQueue.dequeue(), 3);
        sendData(sizeQueue.dequeue(), 4);
    }
    else if (!USEGPIO) {
        QFile posFile("posData.dat");
        posFile.open(QIODevice::WriteOnly);
        posFile.write(posQueue.dequeue());

        QFile flagsFile("flagsData.dat");
        flagsFile.open(QIODevice::WriteOnly);
        flagsFile.write(flagsQueue.dequeue());

        QFile penFile("penData.dat");
        penFile.open(QIODevice::WriteOnly);
        penFile.write(penQueue.dequeue());

        QFile sizeFile("sizeData.dat");
        sizeFile.open(QIODevice::WriteOnly);
        sizeFile.write(sizeQueue.dequeue());
    }
}

void Minerva::receiveMultipleData() {

    if (USEGPIO) {
        posQueue.enqueue(receiveData(5, 48));
        flagsQueue.enqueue(receiveData(6, 5));
        penQueue.enqueue(receiveData(7, 116));
        sizeQueue.enqueue(receiveData(8, 8));
    }
    else if (!USEGPIO) {
        //Receiving Individual Packets
        QFile posFile("posData.dat");
        posFile.open(QIODevice::ReadOnly);

        QFile flagsFile("flagsData.dat");
        flagsFile.open(QIODevice::ReadOnly);

        QFile penFile("penData.dat");
        penFile.open(QIODevice::ReadOnly);

        QFile sizeFile("sizeData.dat");
        sizeFile.open(QIODevice::ReadOnly);

        //Deserializing Individual Packets
        posQueue.enqueue(posFile.readAll());
        flagsQueue.enqueue(flagsFile.readAll());
        penQueue.enqueue(penFile.readAll());
        sizeQueue.enqueue(sizeFile.readAll());
    }


}

void Minerva::send() {
    int numRetries = 0;
    bool receiverReady = false;

    sendReady(true, 0); //sends ready over pin 0 (GPIO 2) - and pin 4 (GPIO 14) receives it

    while (!receiverReady && numRetries < MAX_SYNC_RETRIES) {
        delayMicroseconds(SYNC_TIMEOUT);
        receiverReady = isReceiveReady(3); //reads receiver ready from pin 3(GPIO 17) - pin 7 (GPIO 13) sends it
        numRetries++;
    }

    if (receiverReady) {
    if (USEBIGDATA) {
        sendBigData();
    }
    else {
        sendMultipleData();
    }

        sendReady(false, 0); //sends not ready over pin 0 (GPIO 2) - and pin 4 (GPIO 14) receives it
    }
    else {
        qWarning() << "Minerva::send(): Receiver not ready after" << MAX_SYNC_RETRIES << "retries. Aborting send.";
    }
}

void Minerva::receive() {
    int numRetries = 0;
    bool senderReady = false;

    sendReady(true, 7); // Send the ready signal to pin 7 (GPIO 13) - pin 3 (GPIO 17) receives it

    while (!senderReady && numRetries < MAX_SYNC_RETRIES) {
        delayMicroseconds(SYNC_TIMEOUT);
        senderReady = isReceiveReady(4); // Read the ready signal from pin 4 (GPIO 14) - pin 0 (GPIO 2) sends it
        numRetries++;
    }

    if (senderReady) {

        if (USEBIGDATA) {
            receiveBigData();
        }
        else {
            receiveMultipleData();
        }
        sendReady(false, 7); // Send the not ready signal to pin 7 (GPIO 13) - pin 3 (GPIO 17) receives it
    }
    else {
        qWarning() << "Minerva::receive(): Sender not ready after" << MAX_SYNC_RETRIES << "retries. Aborting receive.";
    }
}

void Minerva::runSendThread() {
    while (true) {
        send();
        std::this_thread::sleep_for(std::chrono::nanoseconds(2500000));
    }
}

void Minerva::runReceiveThread() {
    while (true) {
        receive();
        std::this_thread::sleep_for(std::chrono::nanoseconds(2500000));
    }
}

void Minerva::startReceiveThread() {
    //std::thread receiveThread(&Minerva::runReceiveThread, this);
    //receiveThread.detach();
    /*epimetheusThread->start();*/
}

void Minerva::startSendThread() {
    //std::thread sendThread(&Minerva::runSendThread, this);
    // sendThread.detach();
    /*prometheusThread->start();*/
}

void Minerva::testDMA() {
    //pinMode(8, OUTPUT);
    //pinMode(9,INPUT);
}

QString Minerva::testPins() {
    bool sent = true;
    bool rec = false;
    int dataCount = 0;
    for (int i = 0; i < 40; i++) {
        int output = i % 4;
        int input = output + 4;
        sendBit(output, sent);
        rec = receiveBit(input);
        dataCount += rec;
        qDebug() << "Send Pin: " << output << "Receive Pin: " << input << "Data Received: " << dataCount;
        rec = false;
    }
    QString dataText = dataCount == 40 ? "Data connection test successfull " : "Data connection test failed";
    return dataText;
}

void Minerva::sendReady(bool value , int pin) {
    digitalWrite(syncPins[pin], value);
}

bool Minerva::isReceiveReady(int pin) {
    return digitalRead(syncPins[pin]);
}
