# TODO
# Prompt user for height
while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            break
    except:
        continue

# Print the height
for i in range(1, height+1):
    s = height - i
    # Left space
    for j in range(s):
        print(" ", end="")
    # Left blocks
    for j in range(i):
        print("#", end="")
    # Space in-between
    print("  ", end="")
    # Right blocks
    for j in range(i):
        print("#", end="")
    print("")