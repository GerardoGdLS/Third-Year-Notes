README Group 10 ENSF460

This README file contains the step by step on how to run the python script for Application 2 project.

The python script should almost be ready to run as is. One small change which might be required is found on line 112 of the python file.
Line 112 contains the following line of code:

ser = initialize_serial_connection("COM5", 9600)

This initializes the connection to the USB connection port that the UART is connected to and might need to be changed depending on the computer used.
Currently this is set as COM5, but might need to be changed to a different COM port depending on your computer.

You must ensure the port is not currently being used by another application as the OS will block access if it is currently in use.
For example, if you are running real term or another python script, you must close them to ensure that the port can be properly used.

Once you have ensured the correct COM port is being used and there is no other application running, we can run our python script.
We use VSCode for this example, so I will explain the process using that.

1. When in VSCode, we must open the folder in which our python file is located. We do this as this is the folder in which the csv and plot will be saved to once we have correctly generated them.
2. We will then ensure our circuit is ready to output the values. We will begin by pressing PB1 to switch to the ON(Non-Blink) mode
2.1 Optionally, you can also turn on the ON(Blink) mode by pressing PB2.
3. Now we will press PB3 to turn on the transmission to the UART.
4. Then we select our python file and press "run" in the top right corner of the file (should be an arrow).
5. The following message should then be printed to the terminal:

Initializing serial connection...
Reading serial data...
Starting data collection...

6. The program will now begin printing the precentage of intensity read from the potentiometer and an accompanying hex value between the range of 0x0000 for 0% and 0x03FF for 100%.
7. Turning the potentiometer should now change these values and you can also change between the ON(Blink) and ON(Non-Blink) modes pressing PB2 accordingly.
8. The program will run for 1 minute and in the end will save a CSV file and a PNG file containing the data point and the graph according to the values transmitted.
9. Pressing PB3 during the transmission will stop the transmissions as well as pressing PB1 and leaving the ON mode.