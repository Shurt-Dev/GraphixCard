import cv2, numpy as np, sys

color_values =  [["0xE0","0xE1","0xE2","0xE3","0xE4","0xE5","0xE6","0xE7"],
                 ["0x08","0x09","0x0A","0x0B","0x0C","0x0D","0x0E","0x0F"],
                 ["0x18","0x19","0x1A","0x1B","0x1C","0x1D","0x1E","0x1F"],
                 ["0x28","0x29","0x2A","0x2B","0x2C","0x2D","0x2E","0x2F"],
                 ["0x38","0x39","0x3A","0x3B","0x3C","0x3D","0x3E","0x3F"],
                 ["0x48","0x49","0x4A","0x4B","0x4C","0x4D","0x4E","0x4F"],
                 ["0x58","0x59","0x5A","0x5B","0x5C","0x5D","0x5E","0x5F"],
                 ["0x68","0x69","0x6A","0x6B","0x6C","0x6D","0x6E","0x6F"],
                 ["0x78","0x79","0x7A","0x7B","0x7C","0x7D","0x7E","0x7F"],
                 ["0x88","0x89","0x8A","0x8B","0x8C","0x8D","0x8E","0x8F"],
                 ["0x98","0x99","0x9A","0x9B","0x9C","0x9D","0x9E","0x9F"],
                 ["0xA8","0xA9","0xAA","0xAB","0xAC","0xAD","0xAE","0xAF"],
                 ["0xB8","0xB9","0xBA","0xBB","0xBC","0xBD","0xBE","0xBF"],
                 ["0xC8","0xC9","0xCA","0xCB","0xCC","0xCD","0xCE","0xCF"],
                 ["0xD8","0xD9","0xDA","0xDB","0xDC","0xDD","0xDE","0xDF"],
                 ["0xE8","0xE9","0xEA","0xEB","0xEC","0xED","0xEE","0xEF"],
                 ["0xF8","0xF9","0xFA","0xFB","0xFC","0xFD","0xFE","0xFF"]]

color_palette = cv2.imread("color_palette.png")
if(len(sys.argv)>1):
    target = cv2.imread(sys.argv[1])
else:
    print("No input file.\nSyntax: python3 image_converter.py <source> [-o destination]")
    quit()
cv2.cvtColor(color_palette,cv2.COLOR_BGR2HSV)
cv2.cvtColor(target,cv2.COLOR_BGR2HSV)
newimage = np.zeros((target.shape[0],target.shape[1],3),np.uint8)

if "-o" in sys.argv:
    output = open(sys.argv[sys.argv.index("-o")+1],"w")
else:
    output = open("output.h","w")
output.write("#include <avr/pgmspace.h>\n\nconst unsigned char image[{x}][{y}] PROGMEM =\n{{".format(x = target.shape[0], y = target.shape[1]))

for column in range(target.shape[0]):
    if column > 0:
            output.write(",")
    output.write("{")
    for row in range(target.shape[1]):
        best_color = [0,0,1000]
        for i in range(8):
            for l in range(17):
                current_score = abs(int(target[column,row,0]) - int(color_palette[l,i,0])) + abs(int(target[column,row,1]) - int(color_palette[l,i,1])) + abs(int(target[column,row,2]) - int(color_palette[l,i,2]))
                if(current_score < best_color[2]):
                    best_color[0], best_color[1], best_color[2] = l, i, current_score
        newimage[column][row] = color_palette[best_color[0]][best_color[1]]
        if row > 0:
            output.write(",")
        output.write(color_values[best_color[0]][best_color[1]])
    output.write("}\n")

output.write("};")
output.close()

cv2.imshow("bob",newimage)
cv2.waitKey(0)
print("end")