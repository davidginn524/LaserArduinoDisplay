# LaserArduinoDisplay
 
This is coded for an arduino nano to be used with a i2c display st7920 128x64. 
Multiple sensors are hooked up to this to help monitor status for my K40 laser. Current sensors are
10k thermister - water temp monitoring. If it goes above 24 but below 25 it warns on the screen with short beeps with buzzer. if it's above 25 longer beeps displaying crit. After 5 minutes of no attention in crit stage with no cooldown to below 23 it will shut off the laser by opening the laser interlock system to force the laser to stop firing even if the steppers are still moving. This will most likely ruin your laser project and will have to start again but better than perm damaging your tube

Pump L/H - This measures liters per hour based on a hall effects sensor. If it measures no flow for a certain period of time it alerts via buzzer and screen and opens interlock on screen

Air Assist - this makes sure air assist it on. If it is not on it sounds alarm and opens interlock 
Air extraction - this measures the pressure difference to tell if the extraction is running or not. If no pressure difference after set amount of time it will alarm but not open any interlocks 
Safety - This checks to make sure all interlocks are functional and closed before it allows the laser to fire, if not buzzer and display via screens 

This uses a set of 4 relays (not technically needed could use one) but wold require someone to change the code
Each relay is setup for a specific measure/monitor system. This aids in troubleshooting if one is open and something is wrong 


