# crackhashmd5
<img src="https://img.shields.io/github/languages/top/0xb4b0u/hashbreaker?style&color=5D6D7E" alt="GitHub top language" />
<img src="https://img.shields.io/github/languages/code-size/0xb4b0u/hashbreaker?style&color=5D6D7E" alt="GitHub code size in bytes" />
<img src="https://img.shields.io/github/commit-activity/m/0xb4b0u/hashbreaker?style&color=5D6D7E" alt="GitHub commit activity" />
<img src="https://img.shields.io/github/license/0xb4b0u/hashbreaker?style&color=5D6D7E" alt="GitHub license" />

## Objectif du Projet

Le but de ce projet est de créer un programme permettant à un serveur et à un client de se connecter via des sockets. Le serveur enverra un par un les hashs qu'il possède au client, qui agira en tant que hashbreaker, renvoyant au serveur le hash et le mot de passe correspondant.

## Prérequis

Avant d'exécuter le programme, assurez-vous d'avoir les outils suivants installés sur vos machines :

- **GCC** : Compilateur généralement présent par défaut sur Linux.
- **OpenSSL** : Bibliothèque nécessaire au bon fonctionnement des programmes (libssl-dev).
- **Make** : Outil permettant de générer des programmes exécutables.

## Instructions d'exécution

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/Zerodays-0/crackhashmd5.git
   cd crackhashmd5

2. Compilé :
    make all

3. Exécution des 2 fichiers:
   
    ./serveur [IP_SERVEUR] [PORT] [HASH_LIST]
   
    ./client [IP_SERVEUR] [PORT] [MDP_LIST]

## Auteurs

* Manu Van Hoofstdt - [Zerodays-0](https://github.com/Zerodays-0)
* Chong-Wen Wang - [Chong-wen](https://github.com/Chong-wen)
* Contribueurs au projet [contributeurs](https://github.com/Zerodays-0/crackhashmd5/graphs/contributors)
