# cub3d

- regler probleme de pointeur addr :
srcs/utils.c:51:17: error: incompatible pointer types assigning to 'char *' from 'int *' [-Werror,-Wincompatible-pointer-types]
        data->img.addr = (int *)mlx_get_data_addr(data->img.img,

IDEES :
- Voiture retro futuriste premiere personne. (raycasting retroviseur ?)