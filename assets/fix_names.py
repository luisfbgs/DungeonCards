import os
import glob
import sys


path = sys.argv[1] if len(sys.argv) > 1 else ''

files = glob.glob(path)
print("Old files:")
print(*files, sep='\n')

for f in files:
    os.rename(f, f.replace('+', 'and').replace(' ', '_'))

print("New files:")
print(*glob.glob(path), sep='\n')
