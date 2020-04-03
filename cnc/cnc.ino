#include "filegetter.h"

void setup()
{
  Display disp;
  FileGetter getter(&disp);


  getter.get(file);
  getter.show(file);
  
#include <AccelStepper.h>
SdFile file;
  
struct StepInfo
{
    long int x;
    long int y;
    long int z;
    int xSpeed;
    int ySpeed;
    int zSpeed;
};

// long int readBinLong()
// {
//     byte raw[4];
//     Serial.readBytes(raw, 4);
//     long int& buffer = (long int&)raw;
//     return buffer;
// }

// int readBinShort()
// {
//     byte raw[2];
//     Serial.readBytes(raw, 2);
//     int& buffer = (int&)raw;
//     return buffer;
// }

StepInfo ReadPacket()
{
    byte raw[18];
    Serial.readBytes(raw, 18);
    StepInfo& buffer = (StepInfo&)raw;
    return buffer;
}

const int coef = 2;
bool start = true;
AccelStepper xStepper(1, 2, 5);
AccelStepper yStepper(1, 3, 6);
AccelStepper zStepper(1, 4, 7);
#define ACC 40000
const int buffSize = 15;
bool isRead = false;

struct Deque
{

    bool push(StepInfo &elem)
    {
        if (current < buffSize)
        {
            deq[current].x = elem.x;
            deq[current].y = elem.y;
            deq[current].z = elem.z;
            deq[current].xSpeed = elem.xSpeed;
            deq[current].ySpeed = elem.ySpeed;
            deq[current].zSpeed = elem.zSpeed;
            current++;
            return true;
        }
        return false;
    };
    int size()
    {
        return current;
    };
    StepInfo pop()
    {   
        StepInfo result = deq[0];
        if(current != 0)
        {
            current -= 1;
            for (int i = 0; i < current; i++)
            {
                deq[i] = deq[i + 1];
            }
            //return deq[--current];
        }
        return result;
    };

    StepInfo deq[buffSize];
    int current;
    int front;
};

Deque deq;
int requestCount = 1;
void setup()
{
    // lcd.begin(16, 2);
    Serial.begin(9600);
    Serial.setTimeout(40);
    xStepper.setMaxSpeed(5000);
    yStepper.setMaxSpeed(5000);
    zStepper.setMaxSpeed(5000);
    xStepper.setAcceleration(ACC);
    yStepper.setAcceleration(ACC);
    zStepper.setAcceleration(ACC);
    deq.current = 0;
    while (!Serial) {  
        ; // wait for serial port to connect. Needed for native USB  
    } 
}
int mode = -1;
bool getAnswer = false;
void loop()
{   
    if(isRead && requestCount < buffSize)
    {
        isRead = false;
        requestCount++;
        Serial.println('n');
    }
    if (Serial.available())
    {
        mode = Serial.read();
        // Serial.flush();
        if(mode != 0)
        switch (mode)
        {
        case 1:
            StepInfo tmp;
            isRead = true;
            tmp = ReadPacket();
            deq.push(tmp);
            break;
        case 2:
            //Abort plotting
            break;
        default:
            break;
        }

        while (Serial.available() > 0)
            char b = Serial.read();
    }
    if (deq.size() > 0 && !yStepper.isRunning() && !xStepper.isRunning())
    {
        requestCount--;
        StepInfo step = deq.pop();
        Serial.println('p');
        Serial.print(step.x);
        Serial.print(" ");
        Serial.print(step.y);
        Serial.print(" ");
        Serial.print(step.z);
        Serial.print(" ");
        Serial.print(step.xSpeed);
        Serial.print(" ");
        Serial.print(step. ySpeed);
        Serial.print(" ");
        Serial.println(step.zSpeed);
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
            zStepper.moveTo(-1 * step.z); //ATTENTIONS MOVE NOT MOVETO
        }
    }
    if (!zStepper.isRunning())
    {
        yStepper.run();
        xStepper.run();
    }
    zStepper.run();
}
