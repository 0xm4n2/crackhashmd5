# crackhashmd5
it's a small C project able to use the collision technique to retrieve a password from a given hash

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
   
    ./serveur IP_SERVEUR PORT HASH_LIST
   
    ./client IP_SERVEUR PORT MDP_LIST

## Auteurs

Manu Van Hoofstdt
Chong-Wen Wang
