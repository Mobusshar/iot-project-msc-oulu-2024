# Project Name: IoT Mini Project 1

## Description

This project focuses on the transmission of sensor data from the IoT testbed server to a cloud-based storage system. The primary objective is to establish a seamless and efficient communication channel that enables the transfer of valuable sensor information from the IoT testbed to the cloud infrastructure. By implementing this connectivity, the project aims to facilitate centralized storage and analysis of sensor data, enhancing accessibility and scalability for future applications and research endeavors within the Internet of Things (IoT) domain.

## Table of Contents
- [Description](#description)
- [Installation](#installation)
- [Usage](#usage)
- [License](#license)
- [Contact](#contact)

## Installation

### First clone the project from this directory

```bash
git clone git@github.com:Mobusshar/iot-project-msc-oulu-2024.git
```

# iot-project
## AWS SETUP
For the last part of the project, we need to setup an AWS  and after that we have a server to get data from the iot-testbed.
so in order to that we need to setup a server and I will explain the steps through it.
## First step, VPC
A virtual private cloud (VPC) is a secure, isolated private cloud hosted within a public cloud. VPC customers can run code, store data, host websites, and do anything else they could do in an ordinary private cloud, but the private cloud is hosted remotely by a public cloud provider.So we need to create VPC after account setup in AWS. For VPC setup we need to take care of the IPv4 CIDR block because we should have enough ipis so we can use 10.0.0.0/24 to get 256 ipis. 
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/dd3e89ac-641d-4688-b35e-652b16c63b41)
## Second step, Subnet
We created two subnets one for public for apps and everything that can be public and one private just in case of the things we do not want to everyone have access in it.
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/e4d0a3b5-ce3a-442c-9292-ca7a6da8ceae)
 Remember in IPv4 CIDR block you can use anything but 10.0.0.0 .
## Third step, Launch Stance
You can TRY but it wont work!
So you need an internet gateway before the instance works.
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/19d9c6f4-0070-42cd-84ef-fae200b4dfb3)
And then you need to attach VPC to Internet gateway but there will be a last step before you set things up and it is :
## Last step, Route table
for each subnet, you need to create a route table and so because we have public and private subnets and in that case we need public and private route table. 
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/259f9927-04ba-4a65-af1a-f45f667b14f7)
## at the end it will look something like this after you launch instance again
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/0a135a0b-aff9-441b-8c09-3d89b010362d)

### Connect and go to the Testbed directory /mini-project-1/ and follow the commands
This is to build a router border

```bash
source /opt/riot.source
```

To build a border router firmware run this

```bash
make ETHOS_BAUDRATE=500000 DEFAULT_CHANNEL=11 BOARD=iotlab-m3 -C RIOT/examples/gnrc_border_router clean all
```

To build a border router firmware run this

```bash
make ETHOS_BAUDRATE=500000 DEFAULT_CHANNEL=11 BOARD=iotlab-m3 -C RIOT/examples/gnrc_border_router clean all
```

To flash the border router firmware

```bash
iotlab-node --flash RIOT/examples/gnrc_border_router/bin/iotlab-m3/gnrc_border_router.elf -l grenoble,m3,100
```

Set up the Border Router Network by picking an IPv6 address (like 2001:660:5307:3100::/64)

```bash
sudo ethos_uhcpd.py m3-<node-id> tap0 2001:660:5307:3100::1/64
```

Now in another terminal ssh into the A8 node

```bash
ssh root@node-a8-103
```

Check the ifconfig of the A8 node

<img width="724" alt="Screenshot 2024-01-31 at 21 47 21" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/02d6995d-085a-44df-bd2d-00221d3edb8c">

Go into this directory A8/mosquitto_bridge

Run the broker

```bash
broker_mqtts config.conf
```

Kill the mosquitto in another terminal and stop the service 
Add your IPV6 instance on the mosquitto.config file
Start the mosquitto service again 

```bash
mosquitto -c mosquitto.conf
```






















## Usage


## License
MIT License

## Contact
Merged Group Number 29 & 40
### Md Mobusshar Islam
Email: mislam23@student.oulu.fi
Student id:2305578

### Mahdi Mehrpour Moghadam
Email:mmehrpou23@student.oulu.fi
Student id:2305003

### Magnus William Lange
Email: mlange23@student.oulu.fi
Student id:2308245
