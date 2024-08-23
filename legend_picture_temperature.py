"""
Creates color legend for temperature as picture.
"""
import numpy as np
import matplotlib.pyplot as plt

# color codes for temperature
colors = [
    (255/255, 255/255, 255/255),   # white
    (128/255, 225/255, 255/255),   # blue
    (0/255, 255/255, 0/255),       # green
    (255/255, 160/255, 0/255),     # orange
    (255/255, 0/255, 0/255)        # red
]

n_cols = 10
n_rows = 4

picture = np.zeros((n_rows, n_cols, 3))

# fill colors in picture
for i in range(n_rows):
    start_color = np.array(colors[i])
    if i < len(colors) - 1:
        end_color = np.array(colors[i + 1])
    else:
        end_color = start_color
    
    for j in range(n_cols):
        t = j / (n_cols - 1)  # interpolation factor
        picture[i, j] = (1 - t) * start_color + t * end_color

plt.imshow(picture)
plt.axis('off')

# add labels
for i in range(n_rows):
    plt.text(0, i, str(i * 10 + 1), va='center', ha='center', fontsize=12, color='black', weight='bold')
    plt.text(n_cols - 1, i, str(i * 10 + 10), va='center', ha='center', fontsize=12, color='black', weight='bold')

plt.show()
