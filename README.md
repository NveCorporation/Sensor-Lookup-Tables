# Sensor-Lookup-Tables
Look-up tables can be used to calibrate sensors or correct for system imperfections. 
This Arduino sketch is an example that corrects for 
the inherent nonlinearity of magnetic field versus distance.

A video demonstration is avaiable at:
https://www.nve.com/Videos/video-page.php?video=Lookup-table&title=Look-up%20Tables%20for%20Sensors

In the demonstration, we use simple tools to experimentally determine a sensor response, 
we create curve fit of the response, 
and we generate a look-up table for an Arduino board driving a linear actuator.
