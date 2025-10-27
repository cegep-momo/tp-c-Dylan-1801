# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de les copiers dans le repertoire `build` avec l'application `bibliotheque`

# Question 1
Détection intelligente des doublons (titre, auteur, ISBN)
Dans le projet, j’ai ajouté une vérification plus complète lors de l’ajout d’un livre pour éviter les doublons. A la place de comparer seulement l’ISBN, le programme vérifie 3 champs : titre, auteur et ISBN. Cela rend la détection plus réaliste, car 2 livres peuvent parfois partager un titre mais avoir des auteurs différents ou l'inverse. Avant d'ajouter un livre, le programme parcourt la liste des livres existants et compare chaque champ avant de permettre l’insertion. Si un livre identique est déjà présent, il empêche l’ajout et affiche un message d’erreur à l’utilisateur. Avec cette logique, la fiabilité des données est meilleure et elle rend le système plus cohérent.

# Question 2
