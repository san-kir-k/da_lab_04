import sys
import random
import string
import re

def get_random_pattern():
    length = random.randint(20, 30)
    random_list = [ str(random.randint(0, 9)) for _ in range(length) ]
    return " ".join(random_list)

def get_random_text_string(pattern):
    length1 = random.randint(35, 50)
    random_list1 = [ str(random.randint(0, 9)) for _ in range(length1) ]
    length2 = random.randint(35, 50)
    random_list2 = [ str(random.randint(0, 9)) for _ in range(length2) ]
    rand_appearence = [0, 0, 1, 0, 0] 
    result = ""
    if rand_appearence[random.randint(0, 4)] == 1:
        result = " ".join(random_list1) + " " + pattern + " " + " ".join(random_list2)
    else:
        result = " ".join(random_list1) + " " + " ".join(random_list2)
    return result

def find_all(a_str, sub):
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1: return
        yield start
        start += len(sub) # use start += 1 to find overlapping matches

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <test directory>")
        sys.exit(1)

    test_dir = sys.argv[1]

    for test_count in range(3):
        pattern = get_random_pattern()
        test = []

        line_count = [10, 1000, 10000]
        for _ in range(line_count[test_count]):
            rstr = get_random_text_string(pattern)
            test.append(rstr)

        test_name = "{}/test_{}".format(test_dir, test_count + 1)
        with open(f'{test_name}.t', 'w') as ftest:
            ftest.write(f'{pattern}\n')
            for str in test:
                ftest.write(f'{str}\n')

        ans = []
        sn = 0
        for str in test:
            ans_str = []
            new_pattern = pattern.replace(" ", "")
            new_str = str.replace(" ", "")
            idxs = list(find_all(new_str, new_pattern))
            for p in idxs:
                ans_str.append([sn, p])
            ans.append(ans_str)
            sn += 1
        with open(f'{test_name}.a', 'w') as ftest:
            for str in ans:
                for p in str:
                    ftest.write("{0}, {1}\n".format(p[0] + 1, p[1] + 1))
main()
