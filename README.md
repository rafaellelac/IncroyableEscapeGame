# User Manual
## "Incroyable Escape Game"

### 1. Introduction
Bienvenue au manuel d'utilisation de notre incroyable escape game ! Lorsque vous appuyez sur "Start", vous vous retrouvez dans une salle de travaux pratiques (TP) après vous être endormi. Pour vous échapper, il faudra résoudre plusieurs mini-jeux disponibles sur les ordinateurs de la salle.
### 2. Installation et Setup
#### De quoi avez-vous besoin pour installer ce jeu ?
- Un système d’exploitation compatible (Linux, Windows, ou macOS)
- Les bibliothèques nécessaires (dans notre cas: SFML pour la création de la fenêtre graphique).
- Le code du source du jeu dispoinible sur GitHub

#### Les étapes de l'installation et le lancement
1. Cloner le dépôt git: 
  git clone https://github.com/rafaellelac/IncroyableEscapeGame.git 
2. Compiler le projet avec le Makefile: make
3. Exécuter le jeu: ./escapegame


### 3. Game Controls
- La première page (pour commencer, sortir du jeu ou accéder aux scores) est contrôlée par les flèches directionnelles du clavier.
- Dans la salle, utilisez la souris pour vous déplacer et trouver les éléments utiles.
- Pour le reste, les contrôles à utiliser seront indiqués.

### 4. Instructions
#### Objectif du jeu:
Le but du jeu est de trouver où sont les mini-jeux, de les compléter et d'utiliser le code obtenu pour déverrouiller la porte. À ce moment-là, le temps que vous avez pris sera affiché, et il faudra entrer votre nom pour ajouter votre temps à la page des scores.

#### Game Flow:
1. Après avoir appuyé sur "Start", le contexte du jeu s'affichera, puis vous vous retrouverez dans la salle de TP.
2. Lorsque vous aurez trouvé l'ordinateur qui fonctionne, vous pourrez d'abord lancer le labyrinthe, duquel il faudra sortir avec les flèches directionnelles. N.B. : Lorsque vous arrivez à la sortie, allez bien vers la droite de l'écran pour que le mini-jeu soit validé.
3. Nous vous conseillons de prendre les indices en photo ou de les noter quelque part. Ils vous seront utiles, et vous ne pourrez pas revenir à la page où ils sont donnés.
4. Ensuite, vous lancerez le 15 puzzle, qui est le mini-jeu le plus "compliqué". Appuyez avec votre souris sur le nombre que vous voulez bouger jusqu'à ce que vous ayez une configuration croissante.
5. Il y aura ensuite le quiz. Il faudra utiliser les touches A, B et C du clavier pour répondre. Vous aurez 15 secondes par question. Mauvaise réponse ou temps écoulé : le quiz recommence.
6. Finalement, la variante de l'énigme d'Einstein qu'il faudra résoudre à l'aide des indices obtenus. Vous pouvez utiliser le drag and drop pour visualiser les indices, mais la réponse finale à la question devra être entrée sur le clavier et validée en appuyant sur le bouton "Check Answer".
7. Des parties de code s'afficheront, et il faudra retourner à la porte dans la salle pour les entrer sur le clavier, appuyer sur "Entrée" et sortir.

### 5. Cheat "code"
Si besoin de passer un des mini-jeux pour accéder directement au prochain, suivez les étapes suivantes :
1. Accédez au fichier MEC'JeuEnquestion'.cc.
2. Dans la fonction ProcessInput(), à la case sf::Keyboard::Return :, dans la commande Add(state), changez le state au nom de la classe du prochain jeu ou de celui auquel vous voulez passer entre les <>.
3. Sauvegardez et compilez.
Cela fonctionne pour accéder à n'importe quelle page du jeu.
