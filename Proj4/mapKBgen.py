
states = ['WA','NT','SA','Q','NSW','V','T']

colors = ['R','G','B']

file = open("mapcolor.cnf",'w')

# each state is one of three colors
file.write("# each state is one of three colors\n")

for state in states:
    file.write("(or ")
    for color in colors:
        file.write(state+color)
        if color == colors[-1]:
            file.write(")\n")
        else:
            file.write(" ")

# each state can be at most 1 color
file.write("# each state can be at most 1 color\n")
for state in states:
    for color in colors:
        others = []
        if color == 'R':
            others = ['G','B']
        elif color == 'G':
            others = ['R','B']
        elif color == 'B':
            others = ['R','G']

        file.write("(or not(" + state+color + ") not (" + state+others[0] + "))\n")
        file.write("(or not(" + state+color + ") not (" + state+others[1] + "))\n")


neighbors = {"SA": ["WA","NT","Q","NSW","V"], "WA": ["NT"], "NT": ["Q"], "Q": ["NSW"], "NSW":["V"]}

# neighboring states must be different colors
file.write("# neighboring states must be different colors")

for state in states:
    for color in colors:
        if state in neighbors:
            for neighbor in neighbors[state]:
                file.write("\n(or not(" + state+color + ") not (" + neighbor+color + "))")

file.close()