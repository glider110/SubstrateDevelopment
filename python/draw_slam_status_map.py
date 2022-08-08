import sys
import numpy as np
import matplotlib.pyplot as plt
import math
from datetime import datetime

path_file = sys.argv[1];

plt.rcParams['figure.figsize'] = (6.0, 3.0)
plt.rcParams['savefig.dpi'] = 200
plt.rcParams['figure.dpi'] = 200

total_color_cnt = 8

all_status = [1, 2, 3, 4, 5, 6, 261]
status_table = dict()
status_table[0] = "1"
status_table[1] = "2"
status_table[2] = "3"
status_table[3] = "4"
status_table[4] = "5"
status_table[5] = "6"
status_table[6] = "261"
status_table[7] = "UNKNOWN"


cmap = plt.cm.get_cmap('rainbow', total_color_cnt)
colors = []
for i in range(total_color_cnt):
    print(cmap(i))
    colors.append(cmap(i))

path_data = np.genfromtxt(path_file, delimiter="\t", usecols=(0, 1, 2, 5), dtype=int)

# print(path_data)

ts = path_data[:, 0]
coors = path_data[:, 1:3]
status = path_data[:, 3]
print(coors)
print(status)

x_lim = [ np.min(coors[:, 0]) - 100, np.max(coors[:, 0]) + 100 ]
y_lim = [ np.min(coors[:, 1]) - 100, np.max(coors[:, 1]) + 100 ]
print(x_lim, y_lim)

plt.figure(constrained_layout=True)
plt.axis(x_lim + y_lim)

total_cnt = len(coors)
cur_cnt = 0
draw_path = False
start_idx = 0
end_idx = 0

lines = []
jump_ts = []
jump_x = []
jump_y = []

last_coor = coors[0]
last_st = status[0]
while cur_cnt < total_cnt:
    coor = coors[cur_cnt]
    st = status[cur_cnt]
    end_idx = cur_cnt

    if math.hypot(coor[0] - last_coor[0], coor[1] - last_coor[1]) > 100:
        jump_x.append([last_coor[0], coor[0]])
        jump_y.append([last_coor[1], coor[1]])
        jump_ts.append(ts[cur_cnt - 1])
    last_coor = coor

    if st == last_st:
        cur_cnt += 1
        continue
    
    if last_st in all_status:
        color_idx = all_status.index(last_st)
    else:
        color_idx = len(colors) - 1

    last_st = st

    print(start_idx, end_idx, color_idx)
    line, = plt.plot(coors[start_idx: end_idx + 1, 0], coors[start_idx: end_idx + 1, 1], color=colors[color_idx], linestyle="-")
    if not color_idx in [ l[0] for l in lines ]:
        lines.append([color_idx, line])
    start_idx = cur_cnt
    cur_cnt += 1

if start_idx != end_idx:
    if st in all_status:
        color_idx = all_status.index(st)
    else:
        color_idx = -1
    print(start_idx, end_idx, color_idx)
    line, = plt.plot(coors[start_idx: end_idx + 1, 0], coors[start_idx: end_idx + 1, 1], color=colors[color_idx], linestyle="-")
    if not color_idx in [ l[0] for l in lines ]:
        lines.append([color_idx, line])

print(len(lines))

lines.sort(key=lambda x: x[0])

plt.legend([ l[1] for l in lines ], [ status_table[l[0]] for l in lines ], bbox_to_anchor=(1.01, 0.5), loc=6, prop={'size': 3})

jump_size = len(jump_x)
jump_cnt = 0
while jump_cnt < jump_size:
    plt.plot(jump_x[jump_cnt], jump_y[jump_cnt], "black", linestyle="-")
    print("jump ts = {}".format(jump_ts[jump_cnt]))
    jump_cnt += 1

plt.grid(ls=":")
plt.gca().set_aspect('equal', adjustable='box')
plt.savefig("slam_status_map.png")
plt.show()
