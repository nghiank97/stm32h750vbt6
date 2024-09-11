# ADS1220

## DRDY pin in continuous mode with 1000SPS

```cpp
m_config_reg1 =
            (0b110<<5)|		// DR= 1000SPS
            (0b00<<3)|		// Mode= Normal
            (0b1<<2)|		// Conv mode=continuous
            (0b0<<1)|		// Temp Sensor disabled
            (0b0<<0);		// Current Source off
 ```
```cpp
 extern void drdy_callback(){
	led_toggle();
	raw = ads1220_read_continuous();
}
 ```
![image info](./image/continuous.jpg)

![image info](./image/continuous_zoom.jpg)

![image info](./image/spi_oss.jpg)

