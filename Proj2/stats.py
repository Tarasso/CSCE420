import os

output = [None] * 46
failed = 0

directory = "./BWCHP/"
flag = True
for filename in os.listdir(directory):
    testNum = int(filename[5:7])
    # print(filename)
    stuff = os.popen(f'make run FILE=\"{directory+filename}\" | grep success!').read().replace('\n','')
    
    if stuff == "":
        stuff = "failed"
        failed = failed + 1
    output[testNum] = stuff

fileOut = open("results.txt",'w')

for i in range(1,46):
    fileOut.write(f"test {i}: {output[i]}\n")

fileOut.write(f"Passed: {45-failed}, Failed: {failed}")

fileOut.close()