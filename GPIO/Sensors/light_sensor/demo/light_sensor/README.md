# READ ME THE DEMO

使用本工程前，请需要注意的是——本工程耦合了OLED显示模块，如果想要直接看到现象，请默认的使用4针脚OLED（SSD1309，如果您是SSD1306请更改platformio.ini中的-DSSD1309为-DSSD1306），将SCL和SDA分别接到PA8和PA9。将光传感器的D0引脚接到PA0上。

工程使用的是中断读取，上电的时候OLED会显示Waiting the sensor's data...

当中断触发后（一般是开强光，手机手电筒即可）则会显示当前的状态。

点亮的时候显示的是Current Status: Light On

熄灭的时候显示的是Current Status: Light Off

# READ ME THE DEMO

Before using this project, please note that this project is coupled with an OLED display module. If you want to see the phenomenon directly, please use the default 4-pin OLED (SSD1309, if you use SSD1306, please change -DSSD1309 in platformio.ini to -DSSD1306), connect SCL and SDA to PA8 and PA9 respectively. Connect the D0 pin of the light sensor to PA0.

The project uses interrupt reading. When powered on, the OLED will display Waiting the sensor's data...

When the interrupt is triggered (usually by turning on strong light, such as a mobile phone flashlight), the current status will be displayed.

When it is lit, it displays Current Status: Light On

When it is off, it displays Current Status: Light Off
