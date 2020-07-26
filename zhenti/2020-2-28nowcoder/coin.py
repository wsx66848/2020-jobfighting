#coding=utf-8

import sys 

def fetch(n, coin, gold):
    if n == 1:
        return gold / coin;
    return gold / coin +  ((coin - gold) / coin) * fetch(n-1, coin - 1, gold);

if __name__ == "__main__":
    num = int(sys.stdin.readline().strip())
    if num == 0:
        print("%.6f" % 0)
    elif num <= 1000 and num > 990:
        print("%.6f" % 1)
    else:
        print("%.6f" % fetch(num, 1000 * 1.0, 10 * 1.0));