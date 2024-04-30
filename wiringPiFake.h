// Fake library for wiringPi to allow compilation on Windows cause the Pi is so slow

#define WIRINGPIFAKE_H
#ifdef WIRINGPIFAKE_H


#ifdef __linux__
// Include the actual wiringPi library for Linux
#include <wiringPi.h>
#else
// Declare dummy functions for Windows
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
//dummy function to comly with wiringPi not being present in windows
void digitalWrite(int pin, int value) {
    //dummy function
}
void pinMode(int pin, int mode) {
    //dummy function
}
void wiringPiSetupGpio() {

}
int digitalRead(int pinNumber) {
    //dummy function
    return 1;
}
void delay(int delayTime) {
    //dummy function
}
void delayMicroseconds(int delayTime) {
	//dummy function
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