
So we get response time in microseconds

$$
v_s = \frac{2d}{t}
$$

where $v_s$ is the speed of sound. $d$ is the actual distance to the obstacle (sound needs to travel from the sensor to the wall, bounce back towards the sensor, so $2d$). We're given $t$

$$
d = \frac{1}{2} v_s t
$$

So in actuality, if we set $v_s = 343 m/s$, $t$ in milliseconds, and we want $d$ in $cm$:

$$
d = \frac{1}{2} v_s \times 10^{-6} \times 10^{2} t = \frac{v_s t}{2 \times 10^{4}}
$$

