"""
Creates color legend for air pressure as picture.
"""
import numpy as np
import matplotlib.pyplot as plt

# declare variables for min and max pressure and colors
lower = 950
upper = 1040

colors = [
    (255/255,0,255/255), # pink
    (255/255,0,160/255)  # purple
    ]

n_cols = 10
n_rows = 1

picture = np.zeros((n_rows, n_cols, 3))

# fill colors in picture
for i in range(n_rows):
    start_color = np.array(colors[i])
    end_color = np.array(colors[i + 1])
    
    for j in range(n_cols):
        t = j / (n_cols - 1)  # Interpolationsfaktor
        picture[i, j] = (1 - t) * start_color + t * end_color

plt.imshow(picture)
plt.axis('off')

# add labels
plt.text(0, 0, str(lower), va='center', ha='center', fontsize=12, color='black', weight='bold')
plt.text(n_cols - 1, 0, str(upper), va='center', ha='center', fontsize=12, color='black', weight='bold')

plt.show()
