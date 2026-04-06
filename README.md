# ESP32-Project
This my project using for ESP32
1. GPS Tracking
   
   This system functions to track the location of an object. This device consists of a Neo-6m GPS module, battery, charging module, and 100k ohm resistor.

   
-How it works:


>The battery serves as the system's primary power source, after which all components activate. First, the Neo-6m GPS sensor searches for a satellite location. Once it finds a satellite, it sends the location coordinates to the GPS module. After obtaining the location coordinates, the GPS module sends these coordinates to the ESP32 for processing and sending them to the monitoring dashboard. From this dashboard, we can view and monitor the location of an object.
