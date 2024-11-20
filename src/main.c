#include "play.h"

void start_screen(t_mlx *data)
{
	put_square(&data->image, data->first_p->x, data->first_p->y, COLOR_1);
	put_square(&data->image, data->second_p->x, data->second_p->y, COLOR_2);
	mlx_put_image_to_window(data->ptr, data->window, data->image.img_ptr, 0, 0);
	mlx_string_put(data->ptr, data->window, WIDTH / 2 - 10, HEIGHT / 2, 0xFFFFFF, "Press \'G\' to start a game");
	mlx_string_put(data->ptr, data->window, WIDTH / 2 - 50, HEIGHT / 2 + 30, 0xFFFFFF, "You have 2 seconds of flying time. Use them wisely!");
	mlx_string_put(data->ptr, data->window, START_POS - 100, START_POS + 50, 0xFFFFFF, "Turn left: A | Turn right: D | Fly: W");
	mlx_string_put(data->ptr, data->window, WIDTH - START_POS - 100, HEIGHT - START_POS + 50, 0xFFFFFF, "Turn left: LEFT | Turn right: RIGHT | Fly: UP");
}

int main(void)
{
	t_mlx data;

	init_data(&data);
	start_screen(&data);

	mlx_hook(data.window, 2, 1L << 0, the_game, &data);
    mlx_hook(data.window, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.ptr, render_loop, &data);
	mlx_hook(data.window, 17, 0, press_x, &data);
	mlx_loop(data.ptr);
	mlx_destroy_image(data.ptr, data.image.img_ptr);
	mlx_destroy_window(data.ptr, data.window);
	return (0);
}

/*Notes:

FPS:
It would be good to control the Loop rate (limiting fps, frames per second, meaning to render not all frames)
Why It’s Important
	Limiting the loop rate ensures that your application doesn't consume excessive CPU,
	especially when doing intensive rendering or animations.
Here it's done depending on the wanted speed of players. For MS_PER_PIXEL=5,
it renders a frame every 5 milliseconds, 200 fps. (i don't care for the moment)


Player field:
At every loop, i draw a square for each player and for death, i check
if the head of the square touches another color than black. When the player stops
jumping, the head landing on black and the rest of the field landing on color,
does not make the player lose
I should just draw the head. -> redo some code logic (another time)


Number of players:
I should have made it variable!



Different OS:
The game was developped on linux. It compiles on macOS, but the size of the window is much bigger and the texts are misplaced.

chatgpt:
Les différences que tu observes proviennent des variations entre les implémentations de la MinilibX sur Linux et macOS, ainsi que des différences dans la gestion des graphiques entre ces systèmes. Voici quelques raisons possibles :
    Taille de la fenêtre :
    Sur macOS, la MinilibX utilise des unités logiques qui peuvent être traduites différemment sur un écran Retina (haute densité de pixels). Cela peut donner l'impression que la fenêtre est plus grande. Pour résoudre cela, vérifie la densité de pixels de l'écran (pixel ratio) et ajuste les dimensions en conséquence.
	Positionnement du texte :
    Les fonctions de rendu de texte (comme mlx_string_put) peuvent produire des résultats légèrement différents entre les plateformes. Cela est dû aux variations dans le moteur de rendu utilisé par la MinilibX sur Linux (souvent X11) et sur macOS (Core Graphics).
	Différences dans les polices :
    Les polices utilisées peuvent différer légèrement entre Linux et macOS, ce qui affecte la taille et l'espacement des caractères.

En général,
Les développeurs utilisent souvent des 1) moteurs de jeu multiplateformes comme Unity, Unreal Engine, ou Godot, qui gèrent la compatibilité avec différentes plateformes.
Ces moteurs offrent une abstraction des spécificités des OS, permettant aux développeurs d'écrire du code commun pour le gameplay tout en laissant
le moteur s'occuper des détails comme le rendu graphique ou la gestion des entrées.
...
En résumé, le code principal est souvent commun, mais des outils et bibliothèques aident à gérer les spécificités des systèmes d’exploitation.

Après avoir fini le jeu, j'ai appris qu'il y avait une librairie mlx multi-plateforme! J'aurai dû me poser la question avant de commencer...



Overall, the game has to be remade
*/