import os

TARGET = "napylov_e_contrast_omp"

os.chdir("../../../build/bin")

os.system(f"{TARGET}.exe")
