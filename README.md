# Spectrum-analyzer

In this project, i will walk you through how to implement a spectrum analyzer using esp32 with its dual core.
I will do this project using arduino framework using arduino IDE. in order to use esp32, we will need to install esp32 arduino core in arduino IDE.
Please watch this 4-minute video for getting things ready for esp32 to program: https://www.youtube.com/watch?v=CD8VJl27n94



We will be using esp32 and/or esp32c3 super mini, 0.91 in oled screen, and a microphone to sample audio and display the frequency components.

links for the parts:  
  
https://shorturl.at/kFcOt - microphone  
https://shorturl.at/OVUjJ - 0.91 oled display  
https://shorturl.at/sInEY - esp32c3 super mini  



If you have all the parts above then this is the step we do wiring/connection. we will be using i2c communication protocol.
i2c uses SCL and SDA pins which are pin22 and pin21 for esp32, respectively. if you are using esp32c3 supermini, the pins should be 8 and 9. 
esp32 has many adc pins. i chose pin33 for esp32, and pinx for esp32c3 supermini. you can choose any other pin that has adc functionality.
once the wiring is done, please copy and paste the code provided. choose the board and port in arduino IDE. 
after programming the code, the output should be similar to the videos i provided in the link below.






videos showing the project in action:
-
https://youtube.com/shorts/M6RI966OLcw
-
https://youtu.be/9-7Ewj4thew
-


<img src="https://github.com/user-attachments/assets/60a64f61-c97a-4e37-a35f-7df1a7e6db5f" alt="image" width="300" height="300" />
<img src="https://github.com/user-attachments/assets/9435ffab-225a-45ca-853c-315885ee7832" alt="image" width="300" height="300" />

<img src="https://github.com/user-attachments/assets/ae4b92be-d067-44db-b6e4-c3c06660afef" alt="image" width="604" height="800" />

