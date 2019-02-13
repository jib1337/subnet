# Subnet | Jack Nelson, 2019

This is a subnet calculator I created as my first project working with C.
It will take an IPv4 address as input, along with a subnet mask expressed in CIDR form.
From there it will print information about the network, and give you an opportunity to create subnets.

## Usage overview
1. At the prompt, enter your IPv4 address.
2. The address will be checked to ensure it is valid. If it isn't, you will be re-prompted.
3. At the next prompt, enter a CIDR address (value from 1-31)
4. The program will provide the number of hosts, the first and last host address and the network/broadcast addresses.
5. If you want to subnet from this network, provide a required number of networks at the next prompt. An invalid input will exit the program.
6. The information of each created network will be displayed on the screen, and the program will exit.

## Usage example
```
b1337@LAPTOP-HRLBD1LQ:~/programming/exercises/subnet$ ./subnet
Enter IPv4 address now: 172.16.8.155
Verifying: 172.16.8.155... Address verified!
Enter subnet mask in CIDR notation now: 24

172.16.8.155/24 (Class B)

Network address: 172.16.8.0/24
Total hosts: 254
First host address: 172.16.8.1
Last host address: 172.16.8.254
Broadcast address: 172.16.8.255
Enter number of required networks, or q to quit: 3

Total subnets to be created: 4
-------------------------------
Network address: 172.16.8.0/26
Total hosts: 62
First host address: 172.16.8.1
Last host address: 172.16.8.62
Broadcast address: 172.16.8.63

Network address: 172.16.8.64/26
Total hosts: 62
First host address: 172.16.8.65
Last host address: 172.16.8.126
Broadcast address: 172.16.8.127

Network address: 172.16.8.128/26
Total hosts: 62
First host address: 172.16.8.129
Last host address: 172.16.8.190
Broadcast address: 172.16.8.191

Network address: 172.16.8.192/26
Total hosts: 62
First host address: 172.16.8.193
Last host address: 172.16.8.254
Broadcast address: 172.16.8.255
``` 
