#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-10, 10, 1000)

fig = plt.figure()
ax = fig.add_subplot(111)


# f1 = np.power(x + 1, 2)
ax.plot(x, x, label='linear')
ax.plot(x, x**2, label=r'f(x) = x^2')
ax.plot(x, (x+1)**2, label='cubic')

ax.set_ylim(-10, 10)

ax.spines['top'].set_color('none')
ax.spines['right'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data', 0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data', 0))

ax.arrow(0, 0, 10, 10)
# ax.grid(True)

# ax.set_xlabel('x label')
# ax.set_ylabel('y label')

ax.set_title("Simple Plot")

ax.legend(loc='upper left')

plt.show()
