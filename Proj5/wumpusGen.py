# map size
x = 4
y = 4

filename = "wumpus.cnf"
file = open(filename,'w')

file.write("# rooms adj to wumpus have stench\n")
for i in range(1,x+1):
    for j in range(1,y+1):
        if(i-1 >= 1):
            file.write("(or (not W" + str(i) + str(j) + ") S" + str(i-1) + str(j) + ")\n")
        if(i+1 <= x):
            file.write("(or (not W" + str(i) + str(j) + ") S" + str(i+1) + str(j) + ")\n")
        if(j-1 >= 1):
            file.write("(or (not W" + str(i) + str(j) + ") S" + str(i) + str(j-1) + ")\n")
        if(j+1 <= y):
            file.write("(or (not W" + str(i) + str(j) + ") S" + str(i) + str(j+1) + ")\n")

file.write("# rooms adj to pit have breeze\n")
for i in range(1,x+1):
    for j in range(1,y+1):
        if(i-1 >= 1):
            file.write("(or (not P" + str(i) + str(j) + ") B" + str(i-1) + str(j) + ")\n")
        if(i+1 <= x):
            file.write("(or (not P" + str(i) + str(j) + ") B" + str(i+1) + str(j) + ")\n")
        if(j-1 >= 1):
            file.write("(or (not P" + str(i) + str(j) + ") B" + str(i) + str(j-1) + ")\n")
        if(j+1 <= y):
            file.write("(or (not P" + str(i) + str(j) + ") B" + str(i) + str(j+1) + ")\n")

# file.write("# no breeze means adj rooms dont have pit\n")
# for i in range(1,x+1):
#     for j in range(1,y+1):
#         if(i-1 >= 1):
#             file.write("(or B" + str(i) + str(j) + " (not P" + str(i-1) + str(j) + "))\n")
#         if(i+1 <= x):
#             file.write("(or B" + str(i) + str(j) + " (not P" + str(i+1) + str(j) + "))\n")
#         if(j-1 >= 1):
#             file.write("(or B" + str(i) + str(j) + " (not P" + str(i) + str(j-1) + "))\n")
#         if(j+1 <= y):
#             file.write("(or B" + str(i) + str(j) + " (not P" + str(i) + str(j+1) + "))\n")

# file.write("# no stench means adj rooms dont have wumpus\n")
# for i in range(1,x+1):
#     for j in range(1,y+1):
#         if(i-1 >= 1):
#             file.write("(or S" + str(i) + str(j) + " (not W" + str(i-1) + str(j) + "))\n")
#         if(i+1 <= x):
#             file.write("(or S" + str(i) + str(j) + " (not W" + str(i+1) + str(j) + "))\n")
#         if(j-1 >= 1):
#             file.write("(or S" + str(i) + str(j) + " (not W" + str(i) + str(j-1) + "))\n")
#         if(j+1 <= y):
#             file.write("(or S" + str(i) + str(j) + " (not W" + str(i) + str(j+1) + "))\n")


file.write("# safe if and only if no wumpus and no pit\n")
for i in range(1,x+1):
    for j in range(1,y+1):
        room = str(i) + str(j)
        file.write("(or W" + room + " P" + room + " SAFE" + room + ")\n")
        file.write("(or (not SAFE" + room + ") (not W" + room + "))\n")
        file.write("(or (not SAFE" + room + ") (not P" + room + "))\n")

completed = []

file.write("# at least 1 wumpus\n")
file.write("(or")
for i in range(1,x+1):
    for j in range(1,y+1):
        file.write(" W" + str(i) + str(j))
file.write(")\n")

file.write("# at most 1 wumpus\n")
for i in range(1,x+1):
    for j in range(1,y+1):
        for i2 in range(1,x+1):
            for j2 in range(1,y+1):
                room1 = str(i) + str(j)
                room2 = str(i2) + str(j2)
                if(room1==room2):
                    continue
                if(room1+room2 not in completed and room2+room1 not in completed):
                    file.write("(or (not W" + room1 + ") (not W" + room2 + "))\n")
                    completed.append(room1+room2)
                    completed.append(room2+room1)



file.write("# initial facts\n")
V = ['44','34','24','14','13','12','22','32','42']
B = ['24','13','22','42']
S = ['34','32']

for room in V:
    file.write("(or (not W" + room +"))\n")
    file.write("(or (not P" + room +"))\n")
    # file.write("(or SAFE" + room +")\n")
    if(room in B):
        file.write("(or B" + room + ")\n")
        file.write("(or (not S" + room + "))\n")
    elif(room in S):
        file.write("(or S" + room + ")\n")
        file.write("(or (not B" + room + "))\n")
    else:
        file.write("(or (not B" + room + "))\n")
        file.write("(or (not S" + room + "))\n")

