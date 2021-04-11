import os

TARGET = "napylov_e_contrast_omp"

os.chdir("../../../build")

os.system(f"cmake --build . --target {TARGET} --config RELEASE")
