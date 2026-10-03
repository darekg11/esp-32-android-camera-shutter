Simple Bluetooth Camera Shutter made with ESP-32.

The ESP32 is powered via 9V battery (6xAA batteries in series).  
The battery is hooked to MB102 to get stable 3.3V for ESP32.  
MB102 is placed on breadboard.  
GPIO D2 is used for green LED which indicates that ESP 32 has powered on (it is always ON when ESP32 is ON)  
GPIO D4 is used for blue LED which indicates status of Bluetooth pairing. Blinking means it is trying to pair, constant light means it has paired successfully.
GPIO D18 is used as PULL UP input for simple tacticle button. Upon pressing when bluetooth pairing is completed, it sends `VOLUME_UP` keyboard signal which should trigger taking photo / start or stop recording in default Android Camera app.

![Screenshot of working circut](https://github.com/darekg11/esp-32-android-camera-shutter/blob/master/photo.jpg)