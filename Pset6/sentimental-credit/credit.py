def main():
    # get user input
    number = input("Number: ")

    number_length = len(number)
    # check if the length of credit card number is invalid
    if number_length not in [13, 15, 16]:
        print("INVALID")
    else:
        # if number_length is valid, then calculate checksum
        flag = 1
        checksum = 0
        for digit in number[::-1]:
            if flag == 1:
                checksum += int(digit)
            else:
                checksum += get_sum(int(digit))
            flag = 1 - flag

        # check if checksum is valid
        if checksum % 10 != 0:
            print("INVALID")
        else:
            # determine its type
            if number_length == 15 and number[:2] in ["34", "37"]:
                print("AMEX")
            elif number_length == 16 and number[0] == "5" and 1 <= int(number[1]) <= 5:
                print("MASTERCARD")
            elif number_length in [13, 16] and number[0] == "4":
                print("VISA")
            else:
                print("INVALID")


def get_sum(digit):
    digit *= 2
    sum = 0
    for i in str(digit):
        sum += int(i)
    return sum


if __name__ == '__main__':
    main()