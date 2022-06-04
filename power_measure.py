import csv
import time
import serial
arduino_port = serial.Serial(port='COM3',baudrate=9600)
baud_rate=9600
currentdatadoubleArr=[]
powerdatadoubleArr=[]
#WHILE EXECUTING PRESS CTRL C OR STOP EXECUTION TO PRINT AVERAGE ON CSV FILE
print("Execution started")
while True:
    with open('PowerMeasureResults.csv', 'a')as file:
        writer =csv.writer(file)

        try:

            data = arduino_port.readline()
            string_data = data.decode("utf-8")
            powerdata = string_data.split(",")
            currentdatadouble = float(powerdata[0])
            powerdatadouble = float(powerdata[1])
            currentdatadoubleArr.append(currentdatadouble)
            powerdatadoubleArr.append(powerdatadouble)
            writer.writerow([time.strftime("%H:%M:%S"),currentdatadouble,powerdatadouble])
        except ValueError:
            writer.writerow(["TIME","CURRENT","POWER"])

            print("DECLARATION LINE PASSED")
        except KeyboardInterrupt:
            writer.writerow(["AVERAGE","CURRENT","POWER"])
            writer.writerow(["", sum(currentdatadoubleArr) / len(currentdatadoubleArr),
                             sum(powerdatadoubleArr)/len(powerdatadoubleArr)])
            break

