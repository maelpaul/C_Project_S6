Projet Flood {#mainpage}
============

## Information

- [Sujet du projet](https://www.labri.fr/perso/renault/working/teaching/projets/2021-22-S6-C-Flood.php)

- [Documentation du projet](https://vlohezic.gitlab.io/documentation_flood/)

## Coding Style 

Loop
```C
for (int i = 0; i < n; ++i) {
    printf("Hello World");
}
```

Function
```C
void display(int x) 
{
    printf("x");
}
```

Condition 
```C
if (x == 1) {
    printf("Hello World");
}
```

Pointer 

```C
int* sum(int* a, int* b);
```

## 🚀 Compilation

To create all the files required for the project and install them :
- `make`
- `make install`

To generate the display :
- `make sdl`

As of right now, there is only a command to create test executables : 
- `make test`

To generate the coverage html :
- `make coverage`

The project is clean with : 
- `make clean`

## Exécution

Exécuter le projet:
- `./server -m [M] -t [T] -c [C] -a [A] -f [F] ./player1.so ./player2.so`

- L'option -m permet de spécifier la largeur du plateau de jeu (ex. -m 10).

- L'option -t permet de spécifier la forme du plateau de jeu (grille carrée c, donut d, hachée h ou torique t ) (ex. -t h).

- L'option -c permet de spécifier le nombre de couleurs utilisé dans la partie. Ce nombre est un entier compris entre 2 et MAX_COLOR = 8 (ex. -c 4 pour une partie à 4 couleurs).

- L'option -a permet de spécifier l'algorithme de coloration utilisé. Les algorithmes de coloration sont numérotés à partir de 0. (ex. -a 1 pour le 2nd algorithme de coloration).

- L'option -f permet de spécifier le nombre de couleurs interdites pour chaque joueur. (ex. -f 1 pour 1 couleur interdite).

- Liste des joueurs:  
    - libAston.so  
    - libHaas.so  
    - libWilliams.so  

Exécuter le projet avec l'afficheur:
- `./server -m [M] -t [T] -c [C] -a [A] -f [F] ./player1.so ./player2.so | ./sdl (-m ou -M)`

- L'option -m de sdl permet d'avoir l'affichage image par image après l'exécution complète. 

- L'option -M de sdl permet d'avoir l'affichage image par image.

Exécuter tous les tests:
- `./alltests`

Afficher le coverage:
- `firefox coverage/index.html &`

## 👥 Authors
- Team number : 15555
- Alexandre Soulié ([asoulie004](https://thor.enseirb-matmeca.fr/ruby/students/asoulie004))
- Victor Lohézic ([vlohezic](https://thor.enseirb-matmeca.fr/ruby/students/vlohezic))
- Louis-Victor Ladagnous ([lvladagnous](https://thor.enseirb-matmeca.fr/ruby/students/lvladagnous))
- Maël Paul ([mpaul005](https://thor.enseirb-matmeca.fr/ruby/students/mpaul005))