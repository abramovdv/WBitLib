# WBitLib
Small lib for arduino projects

````cpp

//create ow object with your token
Wbit ow("*TOKEN*", "Cork", "Ireland", "en");

//init it in setup()
ow.init();

//send request in loop()
ow.syncGetRequest(true);
//...and get data
SunData sun = ow.getSunData(0);
WindData wind = ow.wind;
//etc.
````
see [main.cpp](https://github.com/abramovdv/WBitLib/blob/master/src/main.cpp) for more information
