file = open("index.html")
print('String s = "' + file.readline().strip('\n') + '";')
for line in file.readlines():
    for char in line:
        if char == '"':
            char = '\"'
    if line is not "\n":
        print('s += "'  +  line.strip('\n').lstrip() + '";')
