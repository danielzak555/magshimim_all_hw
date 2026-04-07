from scapy.all import *
import time

def main():
    loop = 3
    find = input("insert domain name:")
    avg = 0

    dns_pkt = IP(dst="8.8.8.8")/UDP(dport=53)/DNS(qd=DNSQR(qname=find))
    domain_ip = str(sr1(dns_pkt, verbose = 0).summary())[19:]

    for i in range(loop):
        pkt = IP(dst=find) / ICMP()
        start_time = time.time()
        ans = sr1(pkt, verbose = 0)
        end_time = time.time()
        avg += (end_time - start_time) * 1000
        final_time = f"{(end_time - start_time) * 1000 :.0f} ms"

        if ans:
            print(f"Reply from {domain_ip}: time={final_time}")
        else:
            print("req timed out")
    print(f"Summary: Average={avg / loop :.0f} ms")

if __name__ == "__main__":
    main()