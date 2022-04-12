import os
from collections import Counter

def tarantula(p, f):
    return f / (p + f)

path="output/libxml2/pass/"
p_branch = []
p_num = 0 ;
for filename in os.listdir(path):
    p_num = p_num + 1
    with open(os.path.join(path, filename), 'r') as f:
        texts = f.readlines()
        set_text = []
        for v in texts:
            if v not in set_text:
                set_text.append(v)

        for line in set_text:
            new_text = line.replace('\n', "")
            tp_i = int(new_text, base=16)
            p_branch.append(tp_i)

p_branch.sort()
p_count = {}
for i in p_branch:
    try: p_count[i] += 1
    except: p_count[i] = 1
p_set = set(p_branch)
p_set = list(p_set)

path="output/libxml2/fail/"
f_branch = []
f_num = 0 ;
for filename in os.listdir(path):
    f_num = f_num + 1
    with open(os.path.join(path, filename), 'r') as f:
        texts = f.readlines()
        set_text = []
        for v in texts:
            if v not in set_text:
                set_text.append(v)

        for line in set_text:
            new_text = line.replace('\n', "")
            tp_i = int(new_text, base=16)
            f_branch.append(tp_i)

f_branch.sort()
f_count = {}
for i in f_branch:
    try: f_count[i] += 1
    except: f_count[i] = 1
f_set = set(f_branch)
f_set = list(f_set)
file_write = open("temp", 'w')
num = 0
total = []
for i in range(len(p_set)):
    total.append(p_set[i])

for i in range(len(f_set)):
    total.append(f_set[i])

total = set(total)
total = list(total)
num = len(total)

j = 0
k = 0
T_sus = {}
T_con = {}
S_sus = {}
J_sus = {}
O_sus = {}

O = {}
for i in range(num):
    k = total[i]
    O[i] = k
    p = 0
    f = 0
    if (p_count.get(k) != None):
        p = p_count.get(k) / p_num
    
    if (f_count.get(k) != None):
        f = f_count.get(k) / f_num

    if ((f == 0)and(p != 0)):
        T_sus[k] = 0
        T_con[k] = p

    elif ((p == 0)and(f != 0)):
        T_sus[k] = 1
        T_con[k] = f
    else:
        T_sus[k] = f / (f + p)
        if f > p:
            T_con[k] = f
        else:
            T_con[k] = p

t_list = []
for i in range(num):
    k = O[i]
    tp = (k, T_sus[k], T_con[k])
    t_list.append(tp)

t_list.sort(key=lambda x:(-x[1],-x[2]))

result_file = open("tarantula", "a")
for i in range(num): 
    h = hex(t_list[i][0])
    h.replace('0x', "")
    result_file.write("%s %f %f\n" % (h,t_list[i][1],t_list[i][2]))
print(p_num)
print(f_num)


