# Project Name: IoT Mini Project 1

## Description

This project focuses on the transmission of sensor data from the IoT testbed server to a cloud-based storage system. The primary objective is to establish a seamless and efficient communication channel that enables the transfer of valuable sensor information from the IoT testbed to the cloud infrastructure. By implementing this connectivity, the project aims to facilitate centralized storage and analysis of sensor data, enhancing accessibility and scalability for future applications and research endeavors within the Internet of Things (IoT) domain.

## Table of Contents
- [Description](#description)
- [Installation](#installation)
- [License](#license)
- [Contact](#contact)

## Installation

### First clone the project from this directory

```bash
git clone git@github.com:Mobusshar/iot-project-msc-oulu-2024.git
```

# IoT-project
## AWS SETUP
For the last part of the project, we need to setup an AWS  and after that, we have a server to get data from the IoT testbed.
so in order to do that we need to setup a server and I will explain the steps through it.
## First step, VPC
A virtual private cloud (VPC) is a secure, isolated private cloud hosted within a public cloud. VPC customers can run code, store data, host websites, and do anything else they could do in an ordinary private cloud, but the private cloud is hosted remotely by a public cloud provider. So we need to create VPC after the account setup in AWS. For VPC setup we need to take care of the IPv6 CIDR block.

<img width="1438" alt="Screenshot 2024-02-11 at 7 34 20" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/4254551f-7c4b-42e8-b4e8-92cae0ff37c8">


## Second step, Subnet
We created two subnets one for the public for apps and everything that can be public and one private just in case of things we do not want to everyone have access to it.

<img width="1438" alt="Screenshot 2024-02-11 at 7 36 30" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/cb0d54b4-f8d3-4564-8bb1-1dcc65c40380">

## Third step, Launch Stance
So you need an internet gateway before the instance works.
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/19d9c6f4-0070-42cd-84ef-fae200b4dfb3)
Then you need to attach VPC to the Internet gateway but there will be a last step before you set things up and it is :
## Last step, Route table
for each subnet, you need to create a route table and so because we have public and private subnets, and in that case, we need a public and private route table. 
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/259f9927-04ba-4a65-af1a-f45f667b14f7)
## At the end it will look something like this after you launch the instance again
![image](https://github.com/Damonmehrpour/iot-project/assets/60698413/0a135a0b-aff9-441b-8c09-3d89b010362d)

## After Setting up the EC2 instance on AWS
<img width="852" alt="Screenshot 2024-01-31 at 22 44 03" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/7957fc6c-4b56-4745-a9d2-5d1ff8550be7">

Install docker and install node-red and influxdb on the ec2 instance.

<img width="1440" alt="Screenshot 2024-01-31 at 23 14 04" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/f3527051-1321-4332-a3b0-8b1795747d7a">

## Testbed Preparation
### Connect and build three nodes like this in the picture

<img width="1148" alt="Screenshot 2024-02-11 at 7 11 30" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/d46f274a-f73b-47b1-843d-33ab3961bafe">


and go to the Testbed directory /mini-project-1/main/ and follow the commands below

###This is to build a router border

```bash
source /opt/riot.source
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

Stop the service in another terminal
Add your IPV6 instance on the mosquitto.config file

<img width="380" alt="Screenshot 2024-01-31 at 22 02 48" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/0b6e7856-1e87-4943-9d50-a162096f47dc">

Start the mosquitto service again 

```bash
mosquitto -c mosquitto.config
```

Here we are making ready another m3 node to do the test

```bash
make DEFAULT_CHANNEL=20 SERVER_ADDR=2001:660:5307:3000::67 EMCUTE_ID==station0 BOARD=iotlab-m3 -C . clean all
```

Then flash the node

```bash
iotlab-node --flash ./bin/iotlab-m3/SensorNode.elf -l grenoble,m3,104
```

<img width="419" alt="Screenshot 2024-01-31 at 22 25 21" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/057e40aa-735c-4a39-9cf3-e5d420cc4906">


This is to check the sensor data from the RIOT server

```bash
nc m3-104 20000
```

Consider writing reboot if it says unable to connect

<img width="768" alt="Screenshot 2024-01-31 at 22 34 46" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/a955e497-db78-4141-9e18-eb8d1a158355">



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
