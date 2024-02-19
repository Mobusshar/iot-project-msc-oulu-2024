# Project Name: IoT Mini Project 1

![GitHub commit activity](https://img.shields.io/github/commit-activity/t/mobusshar/iot-project-msc-oulu-2024)
![GitHub last commit](https://img.shields.io/github/last-commit/mobusshar/iot-project-msc-oulu-2024)
![GitHub top language](https://img.shields.io/github/languages/top/mobusshar/iot-project-msc-oulu-2024)
![GitHub language count](https://img.shields.io/github/languages/count/mobusshar/iot-project-msc-oulu-2024)
![GitHub License](https://img.shields.io/github/license/mobusshar/iot-project-msc-oulu-2024)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/mobusshar/iot-project-msc-oulu-2024)
![GitHub repo size](https://img.shields.io/github/repo-size/mobusshar/iot-project-msc-oulu-2024)



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

### Clone the RIOT server as well using this command

```bash
git clone https://github.com/RIOT-OS/RIOT.git
```

Go to the directory
```bash
cd RIOT/
```

Checkout to a previous version branch to avoid any unexpected error by using this command

```bash
git checkout 2022.01
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

<img width="1438" alt="Screenshot 2024-02-11 at 7 38 24" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/0791d83b-7e69-42e4-9be1-0e407fe545c6">

Then you need to attach VPC to the Internet gateway but there will be a last step before you set things up and it is :
## Last step, Route table
for each subnet, you need to create a route table. 

<img width="1438" alt="Screenshot 2024-02-11 at 7 44 43" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/9577d4f1-d034-4422-9f9c-a21a8c75b5f9">

## At the end you can ssh into your VPC by following these instructions

<img width="1438" alt="Screenshot 2024-02-11 at 7 42 09" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/c2e2f1f2-b13b-43eb-9945-3806ca5fa444">


## After Setting up the EC2 instance on AWS

Now you can get access to the EC2 instance and it is ready

<img width="705" alt="Screenshot 2024-02-11 at 7 48 52" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/f42c4724-5bcd-4271-a4c8-64ed8a7b3552">

## Install docker by following these commands

```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

Test the docker container by this command

```bash
sudo docker run hello-world
```

Install node-red container in the EC2 instance by using this command 

```bash
docker run -it -p 1880:1880 -v node_red_data:/data --name mynodered nodered/node-red
```

Install influxdb container on the ec2 instance

```bash
docker run --detach --name influxdb -p 8086:8086 influxdb:2.2.0
```


<img width="1440" alt="Screenshot 2024-01-31 at 23 14 04" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/f3527051-1321-4332-a3b0-8b1795747d7a">

## Testbed Preparation
### Connect and build three nodes from this

<img width="1439" alt="Screenshot 2024-02-11 at 8 17 42" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/2a25ab20-1309-47e0-a202-532a845bd42f">

Create 3 nodes. 1 A8 nodes and 2 m3 nodes

<img width="1439" alt="Screenshot 2024-02-11 at 8 20 48" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/c93e947d-12a2-452b-964b-3a9abd18dd29">

In the end your experiment will look something like this

<img width="1148" alt="Screenshot 2024-02-11 at 7 11 30" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/d46f274a-f73b-47b1-843d-33ab3961bafe">

## These three node ids will be used later in the commands so please replace <node-id> with your created node ID from the IoT-test server

## Go to the Testbed directory /mini-project-1/main/ and follow the commands below

### To build a router border follow this

```bash
source /opt/riot.source
```

To build a border router firmware run this

```bash
make ETHOS_BAUDRATE=500000 DEFAULT_CHANNEL=<channel> BOARD=iotlab-m3 -C RIOT/examples/gnrc_border_router clean all
```

To flash the border router firmware

```bash
iotlab-node --flash RIOT/examples/gnrc_border_router/bin/iotlab-m3/gnrc_border_router.elf -l grenoble,m3,<node-id>
```

Set up the Border Router Network by picking an IPv6 address (like 2001:660:5307:3100::/64)

```bash
sudo ethos_uhcpd.py m3-<node-id> tap0 2001:660:5307:3100::1/64
```

Now in another terminal ssh into the A8 node

```bash
ssh root@node-a8-<node-id>
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
make DEFAULT_CHANNEL=<channel> SERVER_ADDR=2001:660:5307:3000::67 EMCUTE_ID==station0 BOARD=iotlab-m3 -C . clean all
```

Then flash the other m3 node

```bash
iotlab-node --flash ./bin/iotlab-m3/SensorNode.elf -l grenoble,m3,<node-id>
```

<img width="419" alt="Screenshot 2024-01-31 at 22 25 21" src="https://github.com/Mobusshar/iot-project-msc-oulu-2024/assets/41119987/057e40aa-735c-4a39-9cf3-e5d420cc4906">


This is to check the sensor data from the RIOT server

```bash
nc m3-<node-id> 20000
```

Consider writing reboot if it says unable to connect





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
