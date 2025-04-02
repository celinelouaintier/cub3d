# Cub3D

**Cub3D** est notre premier jeu 3D, développé en C à l’école 42. Il repose sur le raycasting pour générer un environnement en vue subjective et utilise la MinilibX pour afficher les graphismes.  
*Réalisé par Céline Louaintier et Naïm Ferrad.*

---

## 📌 Commandes

### 🎮 Déplacement  
- **W** → Avancer  
- **S** → Reculer  
- **D** → Aller à droite  
- **A** → Aller à gauche  

### 🔄 Rotation  
- **Flèche de droite** → Regarder à droite  
- **Flèche de gauche** → Regarder à gauche  

### ⚡ Autres actions  
- **Shift** → Sprint  

---

## 🎯 Partie Bonus  

Cette partie nécessite d’avoir lancé la compilation avec :  
```sh
make bonus
```
(Un make fclean est requis si une compilation a déjà été effectuée auparavant.)

🔹 Interactions supplémentaires  
E → Ouvrir ou fermer une porte

Clic gauche → Tirer

Mouvement de la souris → Bouger la vision

### 🗺️ Map
Symbole	Signification  
1	Mur  
0	Vide  
N/E/S/W	Position et orientation de départ

## 🎯 Partie Bonus  
Cette partie nécessite d’avoir lancé la compilation avec :

```sh
make bonus
```
(Un make fclean est requis si une compilation a déjà été effectuée auparavant.)

Symbole	Signification  
D	Porte (nécessite une texture "D" dans le fichier pour être utilisée)  
X	Ennemi (la partie est gagnée une fois que tous les ennemis sont éliminés)  
