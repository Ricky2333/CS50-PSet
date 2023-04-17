#include <cs50.h>
#include <stdio.h>

typedef long long LL;

// function prototype
LL get_number();
int get_len(LL number);
int cal_checksum(LL number);
string check_type(LL number, int len);

// main function
int main(void)
{
    LL number;
    // get user's credit card number
    number = get_number();

    // get length of this number
    int len = get_len(number);

    // Valid number length should be 13 or 15 or 16
    string res;
    if (!(len == 13 || len == 15 || len == 16))
    {
        res = "INVALID";
    }
    else
    {
        // calculate the checksum of this number
        int checksum;
        checksum = cal_checksum(number);

        // check if the last digit of checksum is 0
        if (checksum % 10 == 0)
        {
            // if this number is valid, return its type
            res = check_type(number, len);
        }
        else
        {
            res = "INVALID";
        }
    }

    // print the result
    printf("%s\n", res);
}

// get user's credit card number
LL get_number()
{
    LL number;
    do
    {
        number = get_long("Number: ");

    }
    while (number < 0);
    return number;
}

// get length of this number
int get_len(LL number)
{
    int len = 0;
    while (number > 0)
    {
        number /= 10;
        len++;
    }
    return len;
}

// calculate the checksum of this credit card number
int cal_checksum(LL number)
{
    // Rules for each digit
    // Rule1: Add this digit to checksum directly
    // Rule2: Multiply this digit by 2, add each digit of this product to checksum
    // When flag is 0, current_digit should abide by Rule1
    // When flag is 1, current_digit should abide by Rule2
    int flag = 0;

    // checksum is stored in sum
    int sum = 0;

    // seperate this credit card number from last digit
    while (number > 0)
    {
        // get current digit(last digit)
        int current_digit = number % 10;
        if (flag)
        {
            // seperate this digit and do addition
            current_digit *= 2;
            while (current_digit > 0)
            {
                sum += current_digit % 10;
                current_digit /= 10;
            }
        }
        else
        {
            sum += current_digit;
        }
        // change flag
        flag = 1 - flag;
        number /= 10;
    }
    return sum;
}

// check credit card type
string check_type(LL num, int len)
{
    // get the first and second digits of this credit card number
    while (num > 100)
    {
        num /= 10;
    }

    // check its type
    if (num >= 51 && num <= 55 && len == 16)
    {
        return "MASTERCARD";
    }
    else if ((num == 34 || num == 37) && len == 15)
    {
        return "AMEX";
    }
    else if (num >= 40 && num <= 49 && (len == 13 || len == 16))
    {
        return "VISA";
    }
    return "INVALID";
}
