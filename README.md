# cub3d


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

TODO

- parsing : normalement c'est bon mais j'ai peut-etre oublie des trucs...
- Animations (ennemis, arme, portes)

- Finir Ennemies 
- Arme
- Mort
- Map : retirer les bords noirs + ajouter le sens sur le joueur (OU render que ce qu'il y a autour du joueur)

On verra :
- Menu

ERREURS

- Segfault quand tu es contre un mur et que l'ennemie t'arrive dessus