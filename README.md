RC_Navlights
============

Navigation lights for RC Planes based on Airbus' light sequence. 

 This sketch simulates the light sequence for navigation lights 
 as mounted on Airbus aircraft at the time of this writing, and a 
 replaced beacon "breathing" operation light
 
 By:
 Rigo & Rigo / February 2014
 
 Requirement:
 8 LEDs
 1x Green (Right Nav)
 1x Yellow (Rear Nav)
 3x Red (Left Nav and 2x Operating Beacon)
 3X White (Srobe wingtip and rear)
 
 Sequence 
 L&R Wing Nav: ON always
 Wingtip Strobe: delay FLASH delay longer ms FLASH (WTSS)Wingtip-Strobe-Strobe
 Back Strobe synced to WT(Wingtip) Strobe sequence as follows: (WTSS) delay ms FLASH
 Beacon "breathing fade" with synced bright pulse to back strobe. 
 */

The lights as they are should be ready to go but with no switch. I plan to add a few lines of code to be able to switch them on with a spare channel on the receiver and be able to control them from the controller. The lights need to run off the balance port from the battery as they sum up to around 10.6 V. Assuming you run on a 3S setup, you can connect the lights to the 4th pin of the balance port and the Arduino to the 3rd as it gives it a nice 7.2V and the onboard voltage regulator should keep it from overload. Alternatively, if the demand on the battery is too high and it makes the Arduino reset then in that case you can run the Arduino off of a 9V battery. 
