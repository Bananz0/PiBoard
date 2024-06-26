#include "minerva.h"
#include "wiringPiFake.h"
#include <thread>

//Delay times for sending and receiving bits and bytes
#define BITDELAY 1000
#define BYTEDELAY 1500
#define USEBIGDATA true
#define SYNC_TIMEOUT 1000000
#define MAX_SYNC_RETRIES 5
#define THREADSLEEP 15000
#define USEQUEUE false //queue for receiving data locally

//int syncPins[8] = { 2, 3, 4, 17 ,
//                    14, 15, 18, 13 };

Minerva::Minerva() {
    //initialize GPIO
    initializeGPIO();
    //set send pins
    dataPins[0] = 17;
    dataPins[1] = 18;
    dataPins[2] = 27;
    dataPins[3] = 22;
    dataPins[4] = 23;
    dataPins[5] = 3;
    dataPins[6] = 25;
    dataPins[7] = 4;
    pinMode(3, INPUT);
    //set misc pins
    //dataPins[8] = 8;
    //dataPins[9] = 9;
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

void Minerva::selectDataPin(int pinNumber, int dataModeNum) {
    pinMode(dataPins[pinNumber], dataModeNum);
}

void Minerva::initializeGPIO() {
    wiringPiSetupGpio();
}

void Minerva::serverMode() {
    //pinMode(22, OUTPUT); //Connected to GPIO 23
    //pinMode(26, OUTPUT); //Connected to GPIO 20
    //pinMode(6, OUTPUT);  //Connected to GPIO 0
    //pinMode(8, OUTPUT);  //connected to GPIO 9
    //pinMode(2, OUTPUT); //sync - send senderready to GPIO 14
    //pinMode(3, OUTPUT); //sync - send sendbit() to GPIO 15 - clock to receiver
    //pinMode(25, INPUT); //sync - receive sendBit from GPIO 24 - clock from receiver
    //pinMode(4, INPUT); //sync - receive sendBit from GPIO 18
    //pinMode(17, INPUT);// sync - read receiverready from GPIO 13

    for (int i = 0; i < 8; i++) {
        pinMode(dataPins[i], OUTPUT);
    }
    pinMode(21, OUTPUT);
    digitalWrite(21, LOW);
}

void Minerva::clientMode() {
    pinMode(dataPins[2], OUTPUT); //read flag

    //https://raspberrypi.stackexchange.com/questions/79111/is-pinmode-necessary-in-wiringpi-programming
    //Therefore not using pinmode for input pins
    //pinMode(23, INPUT); //main receiver
    //pinMode(20, INPUT); //receive small packets
    //pinMode(0, INPUT);  //receive small packets
    //pinMode(9, INPUT); // receive small packets
    //pinMode(14, INPUT);  //sync receive sendready  from GPIO 2
    //pinMode(15, INPUT);  //sync receive sendbit() from GPIO 3 - clock from sender
    //pinMode(24, OUTPUT); //sync send sendBit to GPIO 25 - clock to sender
    //pinMode(18, OUTPUT); //sync send sendBit() to GPIO 4
    //pinMode(13, OUTPUT); //sync send receiverready to GPIO 17

    //digitalWrite(24, LOW);
    //digitalWrite(18, LOW);
    //digitalWrite(13, LOW);
//    bool DMAreceived = false;
//    while (!DMAreceived) {
//        DMAreceived = digitalRead(23);
//        delayMicroseconds(1000);
//        if (DMAreceived) {
//            qDebug() << "DMA Received";
//            qDebug() << "Sending back SOL";
//            pinMode(23, OUTPUT);
//            testDMA();
//            delayMicroseconds(1000);
//            qDebug() << "SOL Sent";
//            pinMode(23, INPUT);
//        }
//    }
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
        if (USEQUEUE) {
            bool emptyAlert = true;
            if (dataQueue.isEmpty()) {
                //alert empty once and return
                if (emptyAlert) {
                    qDebug() << "Receive Data Queue is empty";
                    emptyAlert = false;
                }
                return;

            }
            bigData = dataQueue.dequeue();
        }
        else if (!USEQUEUE) {
            bigData = bigData_raw;
        }
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
        //     penStream >> receiveDataPacket->pen;
        //     sizeStream >> receiveDataPacket->windowSize;
        recLock->unlock();
    }
    //qDebug() << "Receive data queue size is :" << dataQueue.size();
    //recLock->unlock();
}

//void Minerva::sendBit(uint pinNumber, bool bitData) {
//    digitalWrite(syncPins[1], LOW); // Set the clock pin low - sender
//    if (bitData) {
//        digitalWrite(dataPins[pinNumber], HIGH);
//    }
//    else {
//        digitalWrite(dataPins[pinNumber], LOW);
//    }
//    digitalWrite(syncPins[1], HIGH); // Set the clock pin high
//    delayMicroseconds(BITDELAY);
//    digitalWrite(dataPins[pinNumber], LOW);
//}

//bool Minerva::receiveBit(uint pinNumber) {
//    bool bitValue = false;
//
//    bitValue = digitalRead(dataPins[pinNumber]);
//    qDebug() << "Receitdfhethhethetrhom: " << bitValue;
//    return bitValue;
//}

void Minerva::sendData(QByteArray data, uint pinNumber) {
    bool clock = false;
    bool clock_b = false;
    bool readByte = false;
    bool recReady = false;

    //    QByteArray dataStart = QByteArray(1, 0x9D);
    //    QByteArray dataEnd = QByteArray(1, 0x9E);
    QByteArray startPattern = QByteArray::fromHex("9D");
    QByteArray endPattern = QByteArray::fromHex("9E");
    data.prepend(startPattern);
    data.append(endPattern);


    digitalWrite(21, HIGH); // Set the write data enable pin high
    for (int i = 0; i < data.size(); i++) {
        digitalWrite(dataPins[3], HIGH); //set the byte write enable pin high
        delayMicroseconds(BITDELAY);
        pinMode(dataPins[6], INPUT);
        while (clock_b) {
            clock = digitalRead(dataPins[6]); //read the clock signal
            delayMicroseconds(1);
        }
        char byte = data[i];
        for (int j = 0; j < 8; j++) {
            bool bit = (byte >> (7 - j)) & 0x01;
            bool read = false;
            pinMode(dataPins[5], INPUT);
            while (clock) {
                clock = digitalRead(dataPins[5]); //read the clock signal
                delayMicroseconds(1);
            }

            digitalWrite(dataPins[0], bit);
            qDebug() << "sent bit: " << bit;
            delayMicroseconds(BITDELAY);
            digitalWrite(dataPins[1], HIGH); // send the sent flag
            delayMicroseconds(BITDELAY);
            pinMode(dataPins[5], OUTPUT);
            digitalWrite(dataPins[5], HIGH); //send the clock signal
            delayMicroseconds(BITDELAY);
            pinMode(dataPins[6], OUTPUT);
            digitalWrite(dataPins[6], HIGH); //send the clock_b signal
            delayMicroseconds(BITDELAY);

            while (!read) {
                read = digitalRead(dataPins[2]); //read flag
                delayMicroseconds(1);
                if (read) {
                    digitalWrite(dataPins[1], LOW); //clear the sent flag
                    digitalWrite(dataPins[3], LOW); //clear the byte write enable pin
                    delayMicroseconds(BITDELAY);
                }
            }
        }

        delayMicroseconds(BYTEDELAY);

        if (!readByte) {
            readByte = digitalRead(dataPins[4]); //read byte flag
            delayMicroseconds(BITDELAY);
        }
    }
    digitalWrite(21, LOW); // Set the write enable pin low
    delayMicroseconds(BITDELAY);

}

QByteArray Minerva::receiveData(uint pinNumber) {
    QByteArray receivedData;
    bool clock = false;
    char currentByte = 0;
    bool sent = false;
    bool writeByte = false;
    bool clock_b = false;
    bool firstByte = true;

    pinMode(dataPins[5], OUTPUT);
    pinMode(dataPins[6], OUTPUT);

    digitalWrite(dataPins[4], LOW); //clear the byte read flag
    digitalWrite(dataPins[2], LOW); //clear the read flag
    digitalWrite(dataPins[5], LOW); //clear the clock signal
    digitalWrite(dataPins[6], LOW); //clear the clock_b signal

    while (digitalRead(21) == LOW) {
        delayMicroseconds(1); //wait for the write data enable pin to go high
    }


    while (digitalRead(21) == HIGH) {

        //byte read enable
        digitalWrite(dataPins[4], HIGH); //set the byte read enable pin high (reading the byte)

        while (!writeByte) {
            writeByte = digitalRead(dataPins[3]); //byte write enable pin
            delayMicroseconds(1);
        }

        while (!clock_b) {
            pinMode(dataPins[6], INPUT);
            clock_b = digitalRead(dataPins[6]); //read the clock signal
            delayMicroseconds(1);
        }

        digitalWrite(dataPins[6], LOW); //clear the clock_b signal

        for (int j = 0; j < 8; j++) {
            pinMode(dataPins[5], OUTPUT);
            digitalWrite(dataPins[4], LOW); //clear the byte read flag
            digitalWrite(dataPins[2], LOW); //clear the read flag
            digitalWrite(dataPins[5], LOW); //clear the clock signal


            while (!clock && !sent) {
                pinMode(dataPins[5], INPUT);
                sent = digitalRead(dataPins[1]); //sent flag
                clock = digitalRead(dataPins[5]); //read the clock signal
                delayMicroseconds(1);
            }

            bool bit = digitalRead(dataPins[0]);
            currentByte = (currentByte << 1) | bit;
            qDebug() << "rec bit: " << bit;
            delayMicroseconds(100000);
            pinMode(dataPins[5], OUTPUT);
            pinMode(dataPins[6], OUTPUT);
            digitalWrite(dataPins[5], LOW); //clear the clock signal
            delayMicroseconds(BITDELAY);
            digitalWrite(dataPins[6], LOW); //clear the clock_b signal
            delayMicroseconds(BITDELAY);
            digitalWrite(dataPins[2], HIGH); //receive flag
            delayMicroseconds(BITDELAY);
            digitalWrite(dataPins[4], HIGH); //set the byte read pin high
            delayMicroseconds(BITDELAY);
        }
        if (currentByte == 0x9E) {
            break;
        }
        if (firstByte) {
            firstByte = false;
        }
        else {
            receivedData.append(currentByte);
        }
        pinMode(dataPins[6], OUTPUT);
        digitalWrite(dataPins[6], LOW); //clear the clock signal
        delayMicroseconds(BITDELAY);
    }
    qDebug() << "Received Data Size: " << receivedData.size();
    qDebug() << receivedData;
    return receivedData;
}

void Minerva::sendBigData() {
    if (dataQueue.isEmpty()) {
        return;
        qDebug() << "Send Data Queue is empty";
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
        bigData_raw = receiveData(4);
        dataQueue.enqueue(bigData_raw);
        qDebug() << bigData_raw;
    }
    else if (!USEGPIO) {
        QFile bigFile("bigData.dat");
        bigFile.open(QIODevice::ReadOnly);
        bigData_raw = bigFile.readAll();
        bigData = bigFile.readAll();
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
        posQueue.enqueue(receiveData(5));
        flagsQueue.enqueue(receiveData(6));
        penQueue.enqueue(receiveData(7));
        sizeQueue.enqueue(receiveData(8));
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
    if (USEGPIO) {
        sendGPIO();
    }
    else if (!USEGPIO) {
        sendFile();
    }
}

void Minerva::receive() {
    if (USEGPIO) {
        receiveGPIO();
    }
    else if (!USEGPIO) {
        receiveFile();
    }
}

void Minerva::sendFile() {
    qDebug() << "Data sent";
    if (USEBIGDATA) {
        sendBigData();
    }
    else if (!USEBIGDATA) {
        sendMultipleData();
    }
}

void Minerva::sendGPIO() {
    //int numRetries = 0;
    //bool receiverReady = false;

    //sendReady(true, 0); //sends ready over pin 0 (GPIO 2) - and pin 4 (GPIO 14) receives it

    //while (!receiverReady && numRetries < MAX_SYNC_RETRIES) {
    //    delayMicroseconds(SYNC_TIMEOUT);
    //    receiverReady = isReceiveReady(3); //reads receiver ready from pin 3(GPIO 17) - pin 7 (GPIO 13) sends it
    //    numRetries++;
    //}

    //if (receiverReady) {
    if (USEBIGDATA) {
        sendBigData();
    }
    else {
        sendMultipleData();
    }

    //    sendReady(false, 0); //sends not ready over pin 0 (GPIO 2) - and pin 4 (GPIO 14) receives it
    //}
    //else {
    //    qWarning() << "Minerva::send(): Receiver not ready after" << MAX_SYNC_RETRIES << "retries. Aborting send.";
    //}
}

void Minerva::receiveFile() {
    if (USEBIGDATA) {
        receiveBigData();
    }
    else if (!USEBIGDATA) {
        receiveMultipleData();
    }
}

void Minerva::receiveGPIO() {
    //int numRetries = 0;
    //bool senderReady = false;

    //sendReady(true, 7); // Send the ready signal to pin 7 (GPIO 13) - pin 3 (GPIO 17) receives it

    //while (!senderReady && numRetries < MAX_SYNC_RETRIES) {
    //    delayMicroseconds(SYNC_TIMEOUT);
    //    senderReady = isReceiveReady(4); // Read the ready signal from pin 4 (GPIO 14) - pin 0 (GPIO 2) sends it
    //    numRetries++;
    //}

    //if (senderReady) {

    if (USEBIGDATA) {
        receiveBigData();
    }
    else {
        receiveMultipleData();
    }
    //    sendReady(false, 7); // Send the not ready signal to pin 7 (GPIO 13) - pin 3 (GPIO 17) receives it
    //}
    //else {
    //    qWarning() << "Minerva::receive(): Sender not ready after" << MAX_SYNC_RETRIES << "retries. Aborting receive.";
    //}
}

void Minerva::runSendThread() {
    while (true) {
        send();
        //std::this_thread::sleep_for(std::chrono::nanoseconds(THREADSLEEP));
    }
}

void Minerva::runReceiveThread() {
    while (true) {
        receive();
       // std::this_thread::sleep_for(std::chrono::nanoseconds(THREADSLEEP));
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

QString Minerva::testDMA() {
    //    bool DMAreceived = false;
    //    digitalWrite(21, HIGH);
    //    qDebug() << "DMA Test Sent";
    //    delayMicroseconds(BITDELAY);
    //    digitalWrite(21, LOW);
    //    delayMicroseconds(BITDELAY);
    //    delayMicroseconds(4000);
    //    //timeout
    //    for (int i = 0; i < 10; i++) {
    //		DMAreceived = digitalRead(23);
    //        if (DMAreceived) {
    //			break;
    //		}
    //		delayMicroseconds(1000);
    //        qDebug() << "Timeout after " << i << " seconds";
    //	}
    //    QString dataText = DMAreceived ? "DMA Test successfull" : "DMA Test failed";
    //    qDebug() << "DMA Test Received: " << DMAreceived;
    //    return dataText;
    return "Feature has been deimplemented and reabsorbed into another function. ";
}

QString Minerva::testPins() {
    bool sent = true;
    bool rec = false;
    int dataCount = 0;
    for (int i = 0; i < 40; i++) {
        int output = dataPins[7];
        int input = 2;
        digitalWrite(output, sent);
        rec = digitalRead(input);
        dataCount += rec;
        qDebug() << "Send Pin: " << output << "Receive Pin: " << input << "Data Received: " << dataCount;
        rec = false;
        digitalWrite(output, false);
    }
    QString dataText = dataCount == 40 ? "Data connection test successfull " : "Data connection test failed";
    return dataText;
}

void Minerva::sendReady(bool value, int pin) {
    //pinMode(syncPins[pin], OUTPUT);
}

bool Minerva::isReceiveReady(int pin) {
    return 0; // digitalRead(syncPins[pin]);
}

void Minerva::sendBitUnclocked(uint s_pin, bool send) {
    //digitalWrite(s_pin, send);
}

bool Minerva::receiveBitUnclocked(uint r_pin) {
    return 0;// digitalRead(r_pin);
}
