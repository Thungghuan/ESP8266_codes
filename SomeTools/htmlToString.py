file = open("index.html")
print('String s = "' + file.readline().strip('\n') + '";')
for line in file.readlines():
    s = ""
    for char in line:
        if char != " " and char != "\n":
            if char == '"':
                char = '\\"'
            s += char
    if s:
        print('s += "'  +  s + '";')