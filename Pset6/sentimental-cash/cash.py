# import cs50 module
from cs50 import get_float


def main():
    # get user input
    num = get_num()

    # greedy algorithm
    cnt_25 = num // 25
    num -= cnt_25 * 25
    cnt_10 = num // 10
    num -= cnt_10 * 10
    cnt_5 = num // 5
    num -= cnt_5 * 5
    cnt_1 = num
    cnt_sum = cnt_25 + cnt_10 + cnt_5 + cnt_1
    print(cnt_sum)


def get_num():
    while True:
        num = get_float("Change owed: ")
        if num >= 0:
            return int(num * 100)


if __name__ == '__main__':
    main()
