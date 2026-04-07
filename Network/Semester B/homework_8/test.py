import subprocess, re
from scapy.all import get_if_list, get_if_hwaddr

# Get Wi-Fi MAC from Windows
output = subprocess.check_output("netsh wlan show interfaces", shell=True).decode()
wifi_mac = re.search(r"Physical address\s+:\s+([0-9A-Fa-f:-]{17})", output).group(1).replace('-', ':').lower()

# Find matching Scapy interface
for iface in get_if_list():
    try:
        if get_if_hwaddr(iface).lower() == wifi_mac:
            print(f"Wi-Fi interface: {iface}")
            break
    except: pass