Number of literals: 57
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%] [120%] [130%] [140%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%] [120%] [130%] [140%]
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
All the ground actions in this problem are compression-safe
Initial heuristic = 17.000
b (16.000 | 100.000)b (15.000 | 200.001)b (14.000 | 300.002)b (13.000 | 400.003)b (12.000 | 500.004)b (11.000 | 600.005)b (10.000 | 700.006)b (9.000 | 800.007)b (8.000 | 900.008)b (7.000 | 1000.009)b (6.000 | 1100.010)b (5.000 | 1200.011)b (4.000 | 1300.012)b (3.000 | 1400.013)b (2.000 | 1500.014)b (1.000 | 1600.015);;;; Solution Found
; States evaluated: 18
; Cost: 1700.016
; Time 0.00
0.000: (goto_hp_to_cp ugv hp column1)  [100.000]
100.001: (goto_area1_cp ugv column1 column2)  [100.000]
200.002: (goto_area1_cp ugv column2 column3)  [100.000]
300.003: (goto_area1_cp ugv column3 column4)  [100.000]
400.004: (goto_area1_cp ugv column4 column5)  [100.000]
500.005: (goto_area1_cp ugv column5 column6)  [100.000]
600.006: (goto_area1_cp ugv column6 column7)  [100.000]
700.007: (goto_area1_cp ugv column7 column8)  [100.000]
800.008: (goto_area1_cp ugv column8 column9)  [100.000]
900.009: (goto_area1_cp ugv column9 column10)  [100.000]
1000.010: (goto_cp_to_area ugv column10 corridor2)  [100.000]
1100.011: (goto_area_to_cp ugv corridor2 column11)  [100.000]
1200.012: (goto_area2_cp ugv column11 column12)  [100.000]
1300.013: (goto_area2_cp ugv column12 column13)  [100.000]
1400.014: (goto_area2_cp ugv column13 column14)  [100.000]
1500.015: (goto_area2_cp ugv column14 column15)  [100.000]
1600.016: (detect ugv column15 kdj_hall)  [100.000]
