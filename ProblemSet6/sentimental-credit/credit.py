AMEX_LENGTH = 15
AMEX_FRONT_NUMBERS_1 = 34
AMEX_FRONT_NUMBERS_2 = 37
VISA_LENGTH_1 = 13
VISA_AND_MASTERCARD_LENGTH = 16
VISA_FRONT_NUMBER = 4
MASTERCARD_FRONT_NUMBER_LOWER = 50
MASTERCARD_FRONT_NUMBER_UPPER = 56


def main():
    number = get_int("Number: ")
    validation = is_valid_card(number)

    if validation:
        number_length = get_length(number)
        firstTwo = get_front_numbers(number, 2)
        firstOne = get_front_numbers(number, 1)

        if number_length == AMEX_LENGTH and (firstTwo == AMEX_FRONT_NUMBERS_1 or firstTwo == AMEX_FRONT_NUMBERS_2):
            print("AMEX")
        elif number_length == VISA_LENGTH_1 and firstOne == VISA_FRONT_NUMBER:
            print("VISA")
        elif number_length == VISA_AND_MASTERCARD_LENGTH:
            if firstOne == VISA_FRONT_NUMBER:
                print("VISA")
            elif firstTwo > MASTERCARD_FRONT_NUMBER_LOWER and firstTwo < MASTERCARD_FRONT_NUMBER_UPPER:
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")

    else:
        print("INVALID")

def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            continue
            
def is_valid_card(number):
    sum = 0
    number_string = str(number)

    i = len(number_string) - 2
    while (i >= 0):
        doubled = int(number_string[i]) * 2
        doubled_string = str(doubled)

        if len(doubled_string) == 2:
            sum += int(doubled_string[0])
            sum += int(doubled_string[1])
        else:
            sum += doubled
        sum += int(number_string[i + 1])
        i -= 2

    if len(number_string) % 2 == 1:
        sum += int(number_string[0])

    if (sum % 10 == 0):
        return True
    else:
        return False


def get_length(number):
    return len(str(number))


def get_front_numbers(number, amount):
    if amount == 1:
        first = int(str(number)[0])
        return first
    elif amount == 2:
        first = str(number)[0]
        second = str(number)[1]
        combine = first + second
        return int(combine)
    else:
        return -1


main()