import os
from collections import Counter
import sys
import math

def tarantula(p, f):
    return f / (p + f)

def SBI(p, f):
    return f / (p + f)

def Jcd(p, f, t_f):
    return f / (t_f + p)

def Och(p, f, t_f):
    return f / math.sqrt(t_f * (f + p))

issue=sys.argv[1]
path="output/libxml2/"
path=path+issue
path=path+"/pass/"
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

path="output/libxml2/"
path=path+issue
path=path+"/fail/"
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
    n_p = 0
    n_f = 0

    if (p_count.get(k) != None):
        p = p_count.get(k) / p_num
        n_p = p_count.get(k)
    
    if (f_count.get(k) != None):
        f = f_count.get(k) / f_num
        n_f = f_count.get(k)

    if ((f == 0)and(p != 0)):
        T_sus[k] = 0
        T_con[k] = p

    elif ((p == 0)and(f != 0)):
        T_sus[k] = 1
        T_con[k] = f
    else:
        T_sus[k] = tarantula(p, f)
        if f > p:
            T_con[k] = f
        else:
            T_con[k] = p

    S_sus[k] = SBI(n_p, n_f)
    J_sus[k] = Jcd(n_p, n_f, f_num)
    O_sus[k] = Och(n_p, n_f, f_num)


t_list = []
for i in range(num):
    k = O[i]
    tp = (k, T_sus[k], T_con[k])
    t_list.append(tp)
t_list.sort(key=lambda x:(-x[1],-x[2]))
tarantula_file = open("tarantula", "a")
for i in range(num): 
    h = hex(t_list[i][0])
    h.replace('0x', "")
    tarantula_file.write("%s %f %f\n" % (h,t_list[i][1],t_list[i][2]))
tarantula_file.close()

s_list = []
for i in range(num):
    k = O[i]
    tp = (k, S_sus[k], 0)
    s_list.append(tp)

s_list.sort(key=lambda x:(-x[1],-x[2]))
sbi_file = open("sbi", "a")
for i in range(num): 
    h2 = hex(s_list[i][0])
    h2.replace('0x', "")
    sbi_file.write("%s %f\n" % (h2,s_list[i][1]))
sbi_file.close()

j_list = []
for i in range(num):
    k = O[i]
    tp = (k, J_sus[k], 0)
    j_list.append(tp)

j_list.sort(key=lambda x:(-x[1],-x[2]))
jaccard_file = open("jaccard", "a")
for i in range(num): 
    h3 = hex(j_list[i][0])
    h3.replace('0x', "")
    jaccard_file.write("%s %f\n" % (h3,j_list[i][1]))
jaccard_file.close()

o_list = []
for i in range(num):
    k = O[i]
    tp = (k, O_sus[k], 0)
    o_list.append(tp)

o_list.sort(key=lambda x:(-x[1],-x[2]))
ochiai_file = open("ochiai", "a")
for i in range(num): 
    h4 = hex(o_list[i][0])
    h4.replace('0x', "")
    ochiai_file.write("%s %f\n" % (h4,o_list[i][1]))
ochiai_file.close()
