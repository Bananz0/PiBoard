// Fake library for wiringPi to allow compilation on Windows cause the Pi is so slow

#define WIRINGPIFAKE_H
#ifdef WIRINGPIFAKE_H


#ifdef __linux__
// Include the actual wiringPi library for Linux
#include <wiringPi.h>
#define USEGPIO true
#else
#include <fstream>
#include <iostream>
#include <thread> 
std::mutex gpioFileMutex;
#include <chrono>
// Declare dummy functions for Windows
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
#define USEGPIO false

void digitalWriteByte(int value) {
	//dummy function
};
void digitalWriteByte2(int value) {
	//dummy function
};
int digitalReadByte() {
	//dummy function
	return 0;
};


//dummy function to comly with wiringPi not being present in windows
void digitalWrite(int pin, int value) {
	static std::ofstream outputFile("gpio_output.txt", std::ios::app);
	if (outputFile.is_open()) {
		outputFile << pin << "," << value << std::endl;
		outputFile.flush();
	}
	else {
		std::cerr << "Error opening output file!" << std::endl;
	}
}
void pinMode(int pin, int mode) {
    //dummy function
}
void wiringPiSetupGpio() {

}
int digitalRead(int pin) {
	int pinValue = -1; // Default value if pin not found

	std::lock_guard<std::mutex> lock(gpioFileMutex);

	std::ifstream inputFile("gpio_output.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Error opening gpio_output.txt!" << std::endl;
		return pinValue;
	}
	std::string line;
	while (std::getline(inputFile, line)) {
		int numRead; 
		int filePin, value;
		char comma;

		numRead = std::sscanf(line.c_str(), "%d,%c%d", &filePin, &comma, &value);
		if (numRead != 3) {
			std::cerr << "Warning: Invalid line format in gpio_output.txt" << std::endl;
			continue;
		}

		if (filePin == pin) {
			pinValue = value;
			break;
		}
	}
	inputFile.close();
	return pinValue;
}

void delay(int delayTime) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delayTime));
}
void delayMicroseconds(int delayTime) {
	std::this_thread::sleep_for(std::chrono::microseconds(delayTime));
}
int wiringPiSetup() {
	//dummy function
	return 0;
}
void pullUpDnControl(int pin, int pud) {
	//dummy function
}
void wiringPiISR(int pin, int mode, void (*function)(void)) {
	//dummy function
}
void pwmWrite(int pin, int value) {
	//dummy function
}
void softPwmCreate(int pin, int value, int range) {
	//dummy function
}
void softPwmWrite(int pin, int value) {
	//dummy function
}
void micros() {
	//dummy function
}
#endif
#endif // WIRINGPIFAKE_H
