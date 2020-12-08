
# SEZO LoRaWAN Resources

## Network server decoders
Currently we provide decoders for TheThingsNetwork and Chirpstack network servers. Please check javascript decoders in [Network Server decoders](https://github.com/SEZOPL/SEZO-LoRaWAN-Resources/tree/main/Network%20server%20decoders)
## Firmware update via USB
###	Prerequisites
•	Download latest Firmware update package from: [here](https://github.com/SEZOPL/SEZO-LoRaWAN-Resources/archive/main.zip)
•	Unzip package and go to FW_UPDATE folder.

###	Preparation to firmware update
•	Switch off SEZO if its turned on, open enclosure and set “RUN/PROG” switch into “PROG” position, connect SEZO to PC using USB cable, proper setting is showed on picture below.

![Connection](https://github.com/SEZOPL/SEZO-LoRaWAN-Resources/blob/main/FW_UPDATE/Data_Base/connection.jpg)
 
•	Turn ON SEZO using ON/OFF button,
•	Run SEZO_FW_Updater.exe software from SEZO_FW_UPDATE folder,

### Firmware update procedure
 
•	Choose desired firmware typing version number.

![Versions](https://github.com/SEZOPL/SEZO-LoRaWAN-Resources/blob/main/FW_UPDATE/Data_Base/ver.png) 

•	Confirm chosen firmware by typing “YES”. If you want to make change type “NO” and make another firmware version choice. 

![Confirmation](https://github.com/SEZOPL/SEZO-LoRaWAN-Resources/blob/main/FW_UPDATE/Data_Base/yes.png) 

•	If connection is successful there should be relevant information. Wait for about 30 seconds for update to succeed.

![Connected](https://github.com/SEZOPL/SEZO-LoRaWAN-Resources/blob/main/FW_UPDATE/Data_Base/connect.png)

 • Successful procedure is confirmed with "UpdateOk" line.
 
 ![Firmware Done](https://github.com/SEZOPL/SEZO-LoRaWAN-Resources/blob/main/FW_UPDATE/Data_Base/done.png)

### Preparation to usage
•	Disconnect USB cable
•	Turn switch into “RUN” position
•	Reset device with “RST” button or turn it off and on.
