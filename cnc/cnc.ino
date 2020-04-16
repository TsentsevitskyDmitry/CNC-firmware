#include "filegetter.h"

#define ACC 40000
#define MAX_SPEED 5000

struct StepInfo
{
    long int x;
    long int y;
    long int z;
    int xSpeed;
    int ySpeed;
    int zSpeed;
};

// global vars
SdFile binFile;
Display *disp;
AccelStepper xStepper(1, 2, 5);
AccelStepper yStepper(1, 3, 6);
AccelStepper zStepper(1, 4, 7);
bool req = true;

// #define SERIAL

#ifdef SERIAL
    #define DEVICE Serial
#else
    #define DEVICE binFile
#endif

StepInfo ReadPacket();

void setup()
{
    Serial.begin(9600);

    xStepper.setMaxSpeed(MAX_SPEED);
    yStepper.setMaxSpeed(MAX_SPEED);
    zStepper.setMaxSpeed(MAX_SPEED);
    xStepper.setAcceleration(ACC);
    yStepper.setAcceleration(ACC);
    zStepper.setAcceleration(ACC);

    // setup
    disp = new Display();
    disp->showLogo();
    FileGetter getter(disp);

    // getting file with display and encoder
    getter.get(binFile);
    getter.show(binFile);

    // work with file
    Serial.println("file");
    char buff[32];
    binFile.getName(buff, 32);
    Serial.println(buff);
    Serial.println("file size");
    Serial.println(binFile.fileSize());
    Serial.println("file available");
    Serial.println(binFile.available());
    Serial.println("firts byte");
    Serial.println((int)(binFile.read()));

    // any stuff
    delete disp;
    pinMode(LED_BUILTIN, OUTPUT);
    // while (!Serial)
    // {
    //   ; // wait for serial port to connect. Needed for native USB
    // }
}

void loop()
{
    if (!req && DEVICE.available() > 0)
    {      
        byte mode = DEVICE.read();

        StepInfo step;
        step = ReadPacket();

        if(step.xSpeed != 0 && step.x != 0)
        {
            xStepper.setMaxSpeed(step.xSpeed);
            xStepper.moveTo(step.x);
        }
        if(step.ySpeed != 0 && step.y != 0)
        {
            yStepper.setMaxSpeed(step.ySpeed);
            yStepper.moveTo(step.y);
        }
        if(step.zSpeed != 0  && step.z != 0)
        {
            zStepper.setMaxSpeed(step.zSpeed);
            zStepper.moveTo(-1 * step.z);
        }

        req = true;
    }

    if (!zStepper.isRunning())
    {
        yStepper.run();
        xStepper.run();
    }
    zStepper.run();
    
    if (req && !xStepper.isRunning() && !yStepper.isRunning())
    {
        req = false;
        Serial.print('#');
    }
}

StepInfo ReadPacket()
{
    byte raw[18];
    int i = 0;

    while (i != 18)
    {
        if (DEVICE.available() > 0)
        {
            raw[i] = DEVICE.read();
            ++i;
        }
    }

    StepInfo &buffer = (StepInfo &)raw;
    return buffer;
}