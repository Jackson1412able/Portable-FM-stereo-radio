# Portable-FM-stereo-radio

This repository is created to house a project of mine, which is a portable FM stereo radio.
This project was created as a gift to my mom for Mother's day.

This project incorporates an Arduino Uno microcontroller, a TEA5767 FM stereo radio module, a pair of 3W speakers,
an amplifier circuit, and a 5" Nextion HMI TFT touchscreen LCD display.

The Nextion touchscreen LCD display can be programmed separately from the microcontroller. The code for the LCD display
is named as radio.HMI and the code for the Arduino Uno is named as radio.ino. The Arduino Uno uses I2C communication to communicate
with the TEA5767 module and serial communication to communicate with the lcd display. In general, the Arduino Uno
sends instructions to the TEA5767 module to broadcast at a specific FM radio frequency, this module then output the broadcasted
signals to an amplifying circuit to amplify the signal and remove unwanted noise. The resulting signals are then transmitted
to the pair of speakers to play the broadcasted signals. The touchscreen LCD allows users to alter the desired FM radio frequency.

Several pictures below show the developed portable FM stereo radio.<br/><br/>
<p align="center">
<img src="https://user-images.githubusercontent.com/46261099/51828442-92cabb80-2326-11e9-8568-4df747c2b78f.JPEG" width="334" height="250" />
<img src="https://user-images.githubusercontent.com/46261099/51828443-93fbe880-2326-11e9-8ffe-22457faa0c14.JPG" width="334" height="250" />
</p>
<p align="center">
<img src="https://user-images.githubusercontent.com/46261099/51828445-94947f00-2326-11e9-9cf9-991d9e10a2b6.JPG" width="240" height="300" />
</p>


[Video of developed project](https://youtu.be/yOZuRM8ol6s)
