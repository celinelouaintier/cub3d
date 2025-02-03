# cub3d

IDEES :
- Voiture retro futuriste premiere personne. (raycasting retroviseur ?)
- Ennemies
- Menu
- Boss

GIT
- Rajoute l'extension Gitlens ça te met les commit et qui a changé quoi directement sur ton IDE et plein d'autres trucs supers
- Pour créer et basculer directement sur une branche :
        'git checkout -b <nom_branche>'
- Pour push sur ta branche :
        'git push origin <nom_branche>'
- Pour basculer d'une branche à l'autre :
        'git checkout main' (pour la branche principale par ex)
- Pour fusionner une branche dans main (donc aller sur la branche main d'abord)
        'git merge <nom_branche>'
- On peut aussi créer des pull request sur GitHub avec le bouton "New Pull Request" pour faire valider par l'autre
- AVANT DE FUSIONNER, SYNCHRONISER AVEC LA BRANCHE MAIN POUR MINIMISER CONFLITS :
        'git pull origin main'

TODO Celine :
- parsing


Nouveaute :

X sur la map pour un ennemie
Clique gauche pour tirer
j'ai laissé move_ennemy mais elle pue smr en gros juste il te suis
Le curseur c'etait surtout pour debug si tu veux l'enlever ou le modifier fais toi plaisir
Le path de la texture des ennemies pour l'instant est en dur dans le load_texture si tu veux la changer
Calcul pas trop les 50 fonctions par fichier ^^