from scapy.all import *

def main():
    find = input("insert domain name:")

    pkt = IP(dst="8.8.8.8")/UDP(dport=53)/DNS(qd=DNSQR(qname=find))
    print(str(sr1(pkt, verbose = 0).summary())[19:])

if __name__ == "__main__":
    main()