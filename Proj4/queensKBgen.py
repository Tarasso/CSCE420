# change queens to any positive int n > 0
queens = 15

filename = str(queens) + "queens.cnf"
file = open(filename,'w')

file.write("# at least one in each row\n")
for i in range(1,queens+1):
    file.write("(or")
    for j in range(1,queens+1):
        queen = " Q" + str(j) + str(i)
        file.write(queen)
    file.write(")\n")

file.write("# at least one in each col\n")
for i in range(1,queens+1):
    file.write("(or")
    for j in range(1,queens+1):
        queen = " Q" + str(i) + str(j)
        file.write(queen)
    file.write(")\n")

file.write("# no two in same row\n")
for i in range(1,queens+1):
    for j in range(1,queens+1):
        queen1 = "Q" + str(j) + str(i)
        for k in range(j+1,queens+1):
            queen2 = "Q" + str(k) + str(i)
            file.write("(or not(" + queen1 + ") not(" + queen2 + "))\n")

file.write("# no two in same col\n")
for i in range(1,queens+1): # col
    for j in range(1,queens+1):  # row
        queen1 = "Q" + str(i) + str(j)
        for k in range(j+1,queens+1):
            queen2 = "Q" + str(i) + str(k)
            file.write("(or not(" + queen1 + ") not(" + queen2 + "))\n")

completed = []

file.write("# no two in same diag\n")
for i in range(1,queens+1): # col
    for j in range(1,queens+1):  # row
        queen1 = "Q" + str(i) + str(j)
        # file.write(queen1+"\n")
        for i1 in range(1,queens+1): # col
            for j1 in range(1,queens+1):  # row
                queen2 = "Q" + str(i1) + str(j1)
                if(abs(i-i1) == abs(j-j1) and queen1 != queen2):
                    if(queen1+queen2 not in completed and queen2+queen1 not in completed):
                        file.write("(or not(" + queen1 + ") not(" + queen2 + "))\n")
                        completed.append(queen1+queen2)
                        completed.append(queen2+queen1)

file.close()