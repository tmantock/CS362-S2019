import sys


def print_gcov_function_result(gcov, function):
    lines = gcov.split('\n\n')
    found = list(filter(lambda line: line.find(function) > -1, lines))

    if len(found) > 0:
        print(found[-1] + "\n")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Improper arguments passed")
        exit()

    function = sys.argv[1]
    gcov = sys.stdin.read()

    print_gcov_function_result(gcov, function)
