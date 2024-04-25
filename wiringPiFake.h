//enable when wiringPi is installed
#define WIRINGPI
#ifdef WIRINGPI

////dummy defines for wiringPi
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
    return 0;
}
void delay(int delayTime) {
	//dummy function
}


#endif // WIRINGPIFAKE_H