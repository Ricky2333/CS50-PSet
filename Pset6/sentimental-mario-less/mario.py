# import cs50 module
from cs50 import get_int


def get_height():
    # get user's input of height
    while True:
        height = get_int("Height: ")
        if 1 <= height <= 8:
            return height


def main():
    # main function
    height = get_height()
    for i in range(height):
        print(" " * (height - i - 1), end="")
        print("#" * (i + 1))


if __name__ == '__main__':
    main()

