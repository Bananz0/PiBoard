#include "minerva.h"
#include "wiringPiFake.h"\

#include <thread>



//Delay times for sending and receiving bits and bytes
#define BITSENDDELAY 3
#define BITRECEIVEDELAY 3
#define BYTESENDDELAY 20
#define BYTERECEIVEDELAY 20
#define USEGPIO false
#define USEBIGDATA true
 


Minerva::Minerva() {
    //initialize GPIO
	initializeGPIO();
	//set send pins
	dataPins[0] = 0;
	dataPins[1] = 1;
	dataPins[2] = 2;
	dataPins[3] = 3;
    //set receive pins
	dataPins[4] = 4;
	dataPins[5] = 5;
	dataPins[6] = 6;
	dataPins[7] = 7;

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


}

Minerva::~Minerva() {
    delete lastReceivedDataPacket;
    delete lastSentDataPacket;
	delete sendDataPacket;
	delete receiveDataPacket;
}

void Minerva::getServerWindowSize(QSize hermesSize){
    winSize = hermesSize;
};

QSize Minerva::setClentWindowSize(){
    return winSize;
}

QString Minerva::testConnection(){
    pinMode(dataPins[0], OUTPUT);
    pinMode(dataPins[4], INPUT);

    QString connectionStatus;
    int connectionStatusNum = 0;
    int connectionStatusNumSent = 0;

    for (int i = 0; i < 4; i++){
        digitalWrite(dataPins[i],1);
        delay(BITSENDDELAY);
        connectionStatusNum += digitalRead(dataPins[i+4]);
        connectionStatusNumSent += receiveBit(dataPins[i+4]);
        qDebug() << connectionStatusNum << "Send Pin: "<< i << "Receive Pin: " << i+4;
    }

    if (connectionStatusNum != 4) {
        connectionStatus = "Connection failed";
    }
    else {
        connectionStatus = "Connection successful";
    }
    qDebug() << connectionStatus;
    return connectionStatus;
}

void Minerva::selectDataPin(int pinNumber,int dataModeNum){
    pinMode(dataPins[pinNumber], dataModeNum);
};

void Minerva::initializeGPIO() {
    wiringPiSetupGpio();
}

void Minerva::serverMode() {
    selectDataPin(0, 1);
    selectDataPin(1, 1);
    selectDataPin(2, 1);
    selectDataPin(3, 1);
}

void Minerva::clientMode() {
    selectDataPin(4, 0);
    selectDataPin(5, 0);
    selectDataPin(6, 0);
    selectDataPin(7, 0);
}

//https://doc.qt.io/qt-6/qdatastream.html
void Minerva::encodeData() {
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

        bigStreamSender << sendDataPacket->startPoint;
        bigStreamSender << sendDataPacket->movingPoint;
        bigStreamSender << sendDataPacket->endPoint;
        bigStreamSender << sendDataPacket->clearCanvasFlag;
        bigStreamSender << sendDataPacket->drawMode;
        bigStreamSender << sendDataPacket->pen;
        bigStreamSender << sendDataPacket->windowSize;

		//Queueing big packet
		dataQueue.enqueue(bigData);
	}
    else if (!USEBIGDATA) {
        //Serialize Individual Packets
        QDataStream posStreamSender(&posData, QDataStream::WriteOnly);
        QDataStream flagsStreamSender(&flagsData, QDataStream::WriteOnly);
        QDataStream penStreamSender(&penData, QDataStream::WriteOnly);
        QDataStream sizeStreamSender(&sizeData, QDataStream::WriteOnly);

        posStreamSender << sendDataPacket->startPoint;
        posStreamSender << sendDataPacket->movingPoint;
        posStreamSender << sendDataPacket->endPoint;
        flagsStreamSender << sendDataPacket->clearCanvasFlag;
        flagsStreamSender << sendDataPacket->drawMode;
        penStreamSender << sendDataPacket->pen;
        sizeStreamSender << sendDataPacket->windowSize;

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
}

void Minerva::decodeData() {
    if (USEBIGDATA) {
        if (dataQueue.isEmpty()){
            return;
        }
        bigData = dataQueue.dequeue();
        //Deserializing Big Packet
        QDataStream bigStream(&bigData, QDataStream::ReadOnly);
        bigStream >> receiveDataPacket->startPoint;
        bigStream >> receiveDataPacket->movingPoint;
        bigStream >> receiveDataPacket->endPoint;
        bigStream >> receiveDataPacket->clearCanvasFlag;
        bigStream >> receiveDataPacket->drawMode;
        bigStream >> receiveDataPacket->pen;
        bigStream >> receiveDataPacket->windowSize;
    }
    else if (!USEBIGDATA){
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

        posStream >> receiveDataPacket->startPoint;
        posStream >> receiveDataPacket->movingPoint;
        posStream >> receiveDataPacket->endPoint;
        flagsStream >> receiveDataPacket->clearCanvasFlag;
        flagsStream >> receiveDataPacket->drawMode;
        penStream >> receiveDataPacket->pen;
        sizeStream >> receiveDataPacket->windowSize;
    }
}

void Minerva::sendBit(uint pinNumber,bool bitData) {
    if (bitData) {
		digitalWrite(dataPins[pinNumber], HIGH);
	}
    else {
		digitalWrite(dataPins[pinNumber], LOW);
	}
    delayMicroseconds( BITSENDDELAY );
}

int Minerva::receiveBit(uint pinNumber) {
    int bitValue = digitalRead(dataPins[pinNumber]);
    delayMicroseconds( BITRECEIVEDELAY );
    return bitValue;
}

void Minerva::sendData(QByteArray data, uint pinNumber) {
    for (int i = 0; i < data.size(); i++) {
        char byte = data[i]; // Get the byte at index i
        for (int j = 0; j < 8; j++) {
            bool bit = (byte >> j) & 0x01; // Extract the j-th bit from the byte
            sendBit(pinNumber, bit); // Send the bit using the sendBit function
        }
    }
}

QByteArray Minerva::receiveData(uint pinNumber, int expectedByteSize) {
    QByteArray receivedData;
    char currentByte = 0;
    int bitCount = 0;

    for (int i = 0; i < expectedByteSize * 8; i++) {
        bool bit = receiveBit(pinNumber);
        currentByte = (currentByte << 1) | bit;
        bitCount++;

        if (bitCount == 8) {
            receivedData.append(currentByte);
            currentByte = 0;
            bitCount = 0;
        }
    }

    qDebug() << "Received data:" << receivedData;
    return receivedData;
}

void Minerva::sendBigData() {
    if (dataQueue.isEmpty()) {
		return;
	}
    //qDebug() << "Big Data Size: " << dataQueue.size();
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
        dataQueue.enqueue(receiveData(4, 100));
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

void Minerva::send(){
    if (USEBIGDATA) {
		sendBigData();
	}
    else if (!USEBIGDATA) {
		sendMultipleData();
	}
}

void Minerva::receive() {
    if (USEBIGDATA) {
		receiveBigData();
	}
    else if (!USEBIGDATA) {
		receiveMultipleData();
	}
}
//dummy function to comly with wiringPi not being present in windows
//void Minerva::digitalWrite(int pin, int value) {
//	//dummy function
//}
//void Minerva::pinMode(int pin, int mode) {
//	//dummy function
//}
//void Minerva::wiringPiSetupGpio() {
//}
//int Minerva::digitalRead(int pinNumber) {
//	//dummy function
//    return 0;
//}

void Minerva::runSendThread() {
    while (true) {
        send();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
}
void Minerva::runReceiveThread() {
    while (true) {
        receive();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Minerva::startReceiveThread() {
    std::thread receiveThread(&Minerva::runReceiveThread, this);
	receiveThread.detach();
}

void Minerva::startSendThread() {
    std::thread sendThread(&Minerva::runSendThread, this);
     sendThread.detach();

}
