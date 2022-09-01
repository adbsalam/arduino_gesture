# Gesture Recognition Samsung TV Remote SAMSUNG

Components needed 


1 - Arduino Uno Board
1 - PAJ7620 Gesture Recognition Sensor
1 - IR Reciever
1 - 9v Battery

Samsung IR Hex Codes:
https://zeroalpha.com/index.php?option=com_content&view=article&id=10139:samsung-tv-remote-ir-hex-codes&catid=119&Itemid=1167



Connect components using as shown in Following POB diagram. 
![pob](https://user-images.githubusercontent.com/39949965/187962208-b0615acc-3af7-4829-a6ea-9730c58bcfbb.jpg)


Upload arduino_gesture.ino script onto arduino board and you are good to go.

NOTE: DO NOT CONNECT BATTERY WHEN UPLOADING CODE. MAKE SURE YOU ONLY CONNECT TO ONE POWER SUPPLY. CONNECT BATTERY ONCE CODE UPLOADED AND USB REMOVED


# Other Brands

In order to use different TV Brands such as LG, SONY etc. you would need IR Hex Codes. You can find these codes online search for "<BRAND> IR Hex Coded"

Following are some of the useful Links
LG -> https://gist.github.com/francis2110/8f69843dd57ae07dce80 
SONY, PANASONIC -> https://tasmota.github.io/docs/Codes-for-IR-Remotes/#ir-remote-codes-sony-kdl-ex540


Using these Hex codes in arduino_gesture.ino change Hex codes for commands From Line 6-15

Once HEX Codes added then go to method void sendCommand(uint32_t command, String gesture){} Line 190
And change send command to Brand related command from IRemote.h

Look at IRemote.h for usage
Example for Panasonic
change Line 191 irsend.sendSAMSUNG(command, BIT_SIZE);  to irsend.sendPanasonic(command, BIT_SIZE);



Hope This Helps



