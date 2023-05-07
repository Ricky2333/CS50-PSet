# import cs50 module
from cs50 import get_int


def main():
    # get user's input
    height = get_height()

    for i in range(height):
        # print the left part
        print(" " * (height - i - 1), end="")
        print("#" * (i + 1), end="  ")

        # print the right part
        print("#" * (i + 1))

        # combine lines above into 1 line
        # print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
        # print(" " * (height - i - 1), "#" * (i + 1), "  ", "#" * (i + 1), sep="")


def get_height():
    # do-while loop in Python
    while True:
        height = get_int("Height: ")
        if 1 <= height <= 8:
            return height


if __name__ == '__main__':
    main()