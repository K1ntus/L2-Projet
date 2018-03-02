# Projet Licence 2 Informatique - Université Bordeaux I
 **Undead** est un jeu se jouant sur une grille à deux dimensions. Initialement inventé par David Millar sous le nom de "Haunted Mirror Maze", une démonstration du jeu est actuellement disponible sur la Collection Portable de Puzzle de Simon Tatham (Simon Tatham's Portable Puzzle Collection).
Initialement, le jeu avait une grille de dimension 4*4. Cependant, nous devons faire son équivalent, avec une taille variable.

# Principe du jeu

**But du jeu**
Chaque cellule du jeu est initialement: 

 - un type de mirroir (il y a les miroirs verticaux, horizontaux, "normaux" et son contraire) respectivement représenté par les symboles "|", "_", "/", "\".
 - une cellule vide

Pour chaque position de chaque côté(Nord, Sud, Est et Ouest), il y a un nombre visible, représentant les monstres qui doivent être vu.
Afin de résoudre ce jeu, il y a 4 types de monstres mis à disposition:

 - Zombie: Toujours visible
 - Fantôme: Visible seulement après avoir été réfléchi dans un miroir
 - Vampire: Visible uniquement avant avoir été réfléchi dans un miroir
 - Spirit: Jamais visible

Plus de détail [ici](https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/undead.html)

**Spécificité technique**
La position de départ se trouve dans le coin en bas à gauche (coordonnée: 0,0)

  If you have finished with me, you can just create new files by opening the **file explorer** on the left corner of the navigation bar.


# Installer le programme

**Méthode n°1**
Copiez le répertoire du jeu où vous voulez l'installer. Puis lancez l'installation en faisant "sh install.sh"
Les executables se trouveront alors dans le dossier "executable"

**Méthode n°2**
Créez un nouveau dossier qui permettra de compiler le projet à la racine de ce dernier.
(ex. $GAME_PATH/build)
> **Note:** $GAME_PATH étant la racine du jeu et "build" un nom de répertoire au choix de l'utilisateur.
> 
Depuis ce dossier, faites cmake . . . puis make. Les exécutables se trouveront alors dans ce même dossier.

# Lancer le jeu

The file explorer is accessible using the button in left corner of the navigation bar. You can create a new file by clicking the **New file** button in the file explorer. You can also create folders by clicking the **New folder** button.

## Paramètres de lancement d'undead_text

Vous pouvez créer une nouvelle partie en lançant l'executable undead_text sans paramètres
Pour charger une sauvegarde: ./undead_text $PATH/nom_de_la_sauvegarde

## Paramètres de lancement du solver automatique

Il y a 3 modes de lancement pour le solver:

 - FIND_ONE: Créer un fichier contenant une solution à une grille passée en paramètres
 - FIND_ALL: Génère autant de fichiers que de solution à une grille passée en paramètres
 - NB_SOL: Retourne le nombre de grille possible qui termine la partie

> **Note:** Usage: ./undead_solve <-MODE-> <-Nom du fichier contenant la grille à résoudre-> <-Nom du fichier à générer contenant la sortie du solver->

