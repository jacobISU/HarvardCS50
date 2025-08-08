def main():

    height = get_int("Height: ")

    while (height > 8 or height < 1):
        height = get_int("Height: ")

    for i in range(height):
        i += 1
        spaces(height - i)
        starAmount(i)
        spaces(2)
        starAmount(i)
        print()

def get_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            continue


def spaces(number_of_spaces):
    for i in range(number_of_spaces):
        print(" ", end="")


def starAmount(number_of_stars):
    for i in range(number_of_stars):
        print("#", end="")


main()
