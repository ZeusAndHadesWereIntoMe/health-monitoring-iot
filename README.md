# health-monitoring-iot
using MAX30100, MPU6050 and esp32 for a smart health monitoring iot project
the idea for this project came from a UN post i was reading. among 7500 workers which die every year 1000 die from occupational accidents and 6500 of them die from
work related diseases. 
with focusing on heart and stress realted diseases we wanted to make a device which 
monitors health with heart rate, spo2 level and body movement. 
importance of using ML in this system is avoiding the false alarms, like when the 
worker is running and the HR goes high we don't want it to be considered as an issue. also we figured different people have totally different HRs. for example
my friend coping with anxiety always had a heart rate above 100 which should 
be considered dangerous for me but it was fine for them. 
If you experience issues reading from newer MAX30100 modules, try adding resistors to the SDL and SCL pins or run the code separately. These solutions worked for us.
