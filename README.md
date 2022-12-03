# HPSON-Implementation
Final Class Project for Santa Clara University's COEN 317: Distributed Systems

## Overview
This Project is an implementation of the Hybrid Peer to Peer Online Social Network model proposed by Jiwei Wang, Fangai Liu, Xu Li, Haoran Liu, Xiaohui Zhao in their paper "HPOSN: A Novel Online Social Network Model Based on Hybrid P2P". The HPOSN model was designed to address the problem of a centralized server or server cluster architecture of most social networks by adding an auxilary peer to peer network among the user's friends. In the event of a failure by the central server, the HPOSN model switches to a P2P mode in useres attempt to reconstruct a local network from their friends list to continue social network services

## Key Algorithms Used:
1. Gossip Protocol: Used to dissimenate a user's information among their local network in P2P Mode
2. Lamport Timestamps: Everytime a user sends or recieves a message among the network, their time stamp is updated accordingly. Every message along the network is attached with a local time stamp
3. Ricart-Agrawala Algoritm: Using lamport time stamps, this project uses Ricart-Agrawala Algorithm to manage consistency of the shared interests database among the server clusters 

## Usage:
1. Ensure that you have g++ and make installed. 
2. git clone https://github.com/KyleMondinaPortfolio/HPOSN-Implementation
3. in main.cpp insure that server_type is set to 1
4. run ./scc
5. Follow instructions prompted in the console. Supported message types over the network are post
6. messages are sent over the set local network when the central server is down
