from scapy.all import *
import time

def main():
    loop = 3
    find = input("insert domain name:")
    hoop_max = 30
    time_out = 3

    for time_tl in range(1, hoop_max + 1):
        pkt = IP(dst=find, ttl = time_tl) / ICMP()
        ans = sr1(pkt,timeout = time_out, verbose = 0)

        if ans == None:
            print(f"{time_tl}: the request timed out")
        else:
            print(f"{time_tl}: {ans.src}")
            if ans.type == 0:
                break

if __name__ == "__main__":
    main()