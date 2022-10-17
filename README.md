# Xbox 360 RF module Rev. H Model: RF01

This is short description of hacking Xbox 360 RF module from dead console.
Thanks this guy who reversed some commands over the interface of XBOX 360 RF Module 
https://tkkrlab.nl/wiki/XBOX_360_RF_Module. I don't know who made it first but, whatever
This is not full protocol, only sending parts. Receiving part is not implemented so...TBD

Some useful test points in rf module:
![bottom](/revH-RF01.jpeg)


* (Vcc) - TP18
* (USB D-) - TP13
* (USB D+) - TP14
* (GND) - TP9, TP10 you can use one of this because all ground the same
* Button - no test point
* Data - TP16
* CLK - TP15

On the top:
![top](/revH-RF01-top.jpeg)

The connector wiring diagramm:
![connector](/RF-module-connector-cut.jpg)

For fast proto I used arduino board from one of these chinese seller
![connector](/proto-1.jpg)

Connect to ubuntu box
![](xbox360-rf-module.png?raw=true)
