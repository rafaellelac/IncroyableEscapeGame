# User Manual
## "Incroyable Escape Game"

### 1. Introduction
Bienvenue au manuel d'utilisation de notre Incroyable escape game! Lorsque vous appuyez sur start, retrouvez vous dans une salle de travaux pratiques (TP) après vous etre endormi. Pour vous échapper, il faudra résoudre plusieurs mini-jeux disponibles sur les ordinateurs de la salle.

### 2. Installation et Setup
#### Que vous faut it pour installer ce jeu?
- Un système d’exploitation compatible (Linux, Windows, ou macOS)
- Les bibliothèques nécessaires (dans notre cas: SFML pour la création de la fenêtre graphique).
- Le code du source du jeu dispoinible sur GitHub

#### Les etapes de l'installation et le lancement
1- Cloner le dépôt git: 
  git clone https://github.com/rafaellelac/IncroyableEscapeGame.git 
2- Compiler le projet avec le Makefile: make
3- Exécuter le jeu: ./escapegame


### 3. Game Controls
- La premiere page ( pour commencer, sortir du jeu, ou acceder les scores ) est controlee par les fleches directionelles du clavier
- Dans la salle, utiliser la souris pour vous deplacer et trouver les elements utiles 
- Pour le reste, les controles a utiliser seront indiques.

### 4. Instructions
#### Objectif du jeu:
Le but du jeu est de trouver ou sont les Mini Jeux, les completer, et utiliser le code obtenu pour deverouiller la porte. A ce moment la, le temps que vous avez pris sera affiche et il faudra entrer votre nom pour ajouter votre temps a la page des scores.

#### Game Flow:
1- Apres avoir appuye sur start, le contexte du jeu s'affichera puis vous vous retrouverez dans la salle de TP
2. Lorsque vous aurez trouve l'ordinateur qui fonctionne, vous pourrez d'abord lancer le labyrinthe, duquel il faudra sortir avec les fleches directionelle. N.B, Lorsque vous arrivez a la sortie alles bien vers la droite de l'ecran pour que le mini jeu soit valide.
3- Nous vous conseillons de prendre les indices en photo ou les noter quelque part, ils vous seront utiles et vous ne pourrez pas revenir a la page ou ils sont donnes.
4. Ensuite, vous lancerez le 15 puzzle,qui est le minijeu le plus "complique". Appuyer avec votre souris sur le nombre que vous voulez bouger jusqu'a ce que vous ayez une configuration croissante
5. Il y aura ensuite le quizz, il faudra utiliser les touches A B et C du clavier pour repondre, vous aurez 15sec par question. Mauvaise reponse ou temps ecoule, le quizz recommence.
6. Finalement, la variante de l'enigme d'einstein qu'il faudra resoudre a l'aide des indices obtenus. Vous pouvez utiliser le drag and drop pour visualiser les indices, mais la reponse finale a la question devra etre entree sur le clavier et validee en appuyant sur le bouton check answer
7- Des parties de code s'afficherons et il faudra retourner a la porte dans la salle pour l'entrer sur le clavier, appuyer sur ENTRER et sortir.

### 5. Cheat "code"
Si besoin de skip un des mini jeux pour passer directement au prochain suivre les etapes suivantes.
Acceder au ficher MEC'JeuEnquestion'.cc  
Dans la fonction ProcessInput(), case sf::Keyboard::Return : dans la commande Add(state), changer le state au nom de la classe du prochain jeu, ou celui auquel vous voulez passer entre les <> sauvegarder et compiler. Ceci marche pour asser a n'importe quelle page du jeu.
