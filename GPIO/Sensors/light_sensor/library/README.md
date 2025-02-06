# 光传感器 Light Sensor

笔者使用的是一个普通的至少带有DC输出的一个光传感器，对GPIO进行了简单的封装。值得注意的是，这个Package是需要中断配置的，你也可以注册只输入的GPIO包。本库不负责对GPIO的底层初始化，所以请确保在GPIO已经被初始化后注册使用的GPIO。

I used a common light sensor with at least DC output, and simply packaged the GPIO. It is worth noting that this package requires interrupt configuration, and you can also register an input-only GPIO package. This library is not responsible for the underlying initialization of GPIO, so make sure to register the GPIO you use after the GPIO has been initialized.