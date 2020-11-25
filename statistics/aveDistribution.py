from functools import total_ordering
import os
import numpy as np
import time
total_timer_start = time.time()
cpu_timer_start = time.process_time()
delta_step = 480 * 2 * 5 * 2 * 5
wi = 0.1
stat_type = 'Voro_vol'
moument_start = 0
moument_number = 500
sample_start = 1
sample_number = 10

dstb_size = (100, 4)
stat_size = (moument_number - moument_start + 1, 6)
dstb_header = 'mid left right distribution'
for istep in range(moument_start, moument_number + 1):
    step = istep * delta_step
    dstb_fname = 'distribution.cut.' + str(step)
    ave_dstb = np.zeros(dstb_size)
    for i in range(sample_start, sample_number + 1):
        dstb_path = '../' + str(i) + '/' + 'Statistics/' + 'wi' + str(
            wi) + '/' + stat_type + '/' + 'distribution.cut/'
        dstb_fullPath = dstb_path + dstb_fname
        #print(ffullPath)
        dstb = np.loadtxt(dstb_fullPath,
                          float,
                          comments='#',
                          delimiter=' ',
                          skiprows=1)
        ave_dstb = dstb + ave_dstb
    ave_dstb /= sample_number
    dstb_ofname = 'ave.distribution.cut.' + str(step)
    dstb_ofPath = '../aveStatistics/' + 'wi' + str(
        wi) + '/' + stat_type + '/' + 'distribution.cut/'
    if not os.path.exists(dstb_ofPath):
        os.makedirs(dstb_ofPath)
    np.savetxt(dstb_ofPath + dstb_ofname,
               ave_dstb,
               header=dstb_header,
               comments='')
    #print(ave_dstb)

stat_header = '# step min max mean var'
ave_stat = np.zeros(stat_size)
for i in range(sample_start, sample_number + 1):
    stat_fullpath = '../' + str(i) + '/' + 'Statistics/' + 'wi' + str(
        wi) + '/' + stat_type + '/' + 'stat.cut.csv'
    statistics = np.loadtxt(stat_fullpath)
    ave_stat += statistics
ave_stat /= sample_number
stat_ofPath = '../aveStatistics/' + 'wi' + str(wi) + '/' + stat_type + '/'
if not (os.path.exists(stat_ofPath)):
    os.makedirs(stat_ofPath)
stat_ofname = 'ave.stat.cut.csv'
np.savetxt(stat_ofPath + stat_ofname,
           ave_stat,
           header=stat_header,
           comments='')

cpu_timer_stop = time.process_time()
total_timer_stop = time.time()
cpu_time = cpu_timer_stop - cpu_timer_start
total_time = total_timer_stop - total_timer_start
print('total time used: ', total_time)
print('cpu time used: ', cpu_time)
