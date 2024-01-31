# Project Name: IoT Mini Project 1

## Description

In this

## Table of Contents

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

 

## Usage


## License
MIT License

## Contact
Merged Group Number 29 & 40
### Md Mobusshar Islam
Email: mislam23@student.oulu.fi

### Mahdi Mehrpour Moghadam
Email:mmehrpou23@student.oulu.fi

### Magnus
Email: 
