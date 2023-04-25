# Python 3 code to rename multiple
# files in a directory or folder
 
# importing os module
import os

for directories in os.listdir(os.getcwd()):

    if os.path.isdir(directories):
        for filename in os.listdir(directories):
            src = f"{directories}/{filename}"
            dst = f"{directories}/{directories}_{filename}"
            os.rename(src, dst)