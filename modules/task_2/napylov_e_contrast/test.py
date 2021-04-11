import os
import time

TARGET = "napylov_e_contrast_omp"
REPEAT = 10000
err_list = list()

os.chdir("../../../build/bin")

os.system(f"{TARGET}.exe")

for i in range(0, REPEAT):
    print(f"{i+1} / {REPEAT}")
    final_code = os.system(f"{TARGET}.exe")
    if final_code != 0:
        err_list.append(i)
        print('ERROR! (sleep 3 sec)')
        time.sleep(3)

print('Fails: ', err_list)
