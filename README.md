# pipex <img src="https://user-images.githubusercontent.com/101518532/236288768-8c66c206-b2f5-48c9-aae1-9ac5fe054204.png" alt="Project note" width="50" height="37">

<div align="center">
<img src="https://i1.sndcdn.com/artworks-000262134179-uv9y7z-t500x500.jpg" alt="Mario Bros in a pipe" width="200" height="150">
</div>

## Table of contents
* [Instructions](#instructions)
* [Project overview](#project-overview)
* [Bonus](#bonus)
* [What I learned](#what-i-learned)

## Instructions
### Compilation
To compile the mandatory part, simply go into the cloned repository and use the <code>make</code> command. Then, you can execute the program like this: <code>./so_long maps/</code> and add the map you want to try after the '/'. I suggest using the laby.ber map or creating your own, but first go check out the [map requirements](#map-requirements)!

Example:
```
./so_long maps/laby.ber
```
As for the bonus part, you can write <code>make bonus</code> into the terminal to compile and then execute as showed below. Note that you will need a map that contains an enemy, or you will get an error message.

Example:
```
./so_long_bonus maps/bonus_maps/bonus_emptier.ber
```

### How to play
<p>The goal of this game is to collect all the collectibles, which are carrots in our case. Once you've collected all the carrots, you need to go and find your bunny friend to share the loot.</p>
<p>In the bonus part, there is a fox looking out for you though. Watch out!</p>

#### Controls
| Key | Action |
|---|---|
| <kbd>W</kbd>, <kbd>↑</kbd>| Move up |
| <kbd>S</kbd>, <kbd>↓</kbd>| Move down |
| <kbd>A</kbd>, <kbd>←</kbd>| Move to the left |
| <kbd>D</kbd>, <kbd>→</kbd>| Move to the right |
| <kbd>ESC</kbd>, `⎋`| Close the game |

## Project overview
<div align="center">
<img src="https://user-images.githubusercontent.com/101518532/235535445-db7cb863-fd05-439b-af49-a259f1343cac.gif" alt="Gameplay screenshot" width="830" height="416">
</div>

This project is a very small 2D game. Its purpose is to make you work with textures, sprites, and some other very basic gameplay elements.

### Minilibx
This project had to be done using a simple graphic library called the MLX, which was provided with the subject. I have included the [library](https://github.com/42Paris/minilibx-linux) here with my code but you can find more info on here: [https://harm-smits.github.io/42docs/libs/minilibx](https://harm-smits.github.io/42docs/libs/minilibx).

### Map requirements
* The map can only be composed of these characters:

| Description | Character|
|--|--|
| Empty space | `0` |
| Wall | `1` |
| Player | `P` |
| Exit | `E` |
| Collectible | `C` |
| Enemy | `F` |

* The map must be rectangular and surrounded by walls.
* The map has to be a .ber file. Not a folder. A file!
* The map must contain exactly one player and one exit, and at least one collectible. For the bonus map, you will also need an enemy.
* There has to be a valid path in the map. If the exit or one of the collectibles is blocked by walls, the map is invalid. The player cannot go through walls!

### Norminette
This project was written in accordance to the Norm, as set of rules every 42 students need to follow for the C-projects. You can find it here: [https://github.com/42School/norminette](https://github.com/42School/norminette).

## Bonus
<div align="center">
<img src="https://user-images.githubusercontent.com/101518532/235703038-8d4188d5-e9d7-4f3b-9892-e8e519673f91.gif" alt="Bonus gameplay screenshot" width="830" height="416">
<p><b>DON'T WORRY! NO BUNNIES WERE HARMED IN THE MAKING OF THIS GAME!</b></p>
</div>

For the bonus part, it was up to our imagination to add some features. Here were some of the suggested additions:

* Make the player lose when they touch an enemy patrol.
* Add some sprite animation.
* Display the movement count directly on screen instead of writing it in the shell.

I also decided to create a GAME OVER screen as well as making it possible to restart the game.

Shout out to DALL-E for the fox sprites!

## What I learned

* How to use a simple graphic interface (MLX).
* How to handle events (hook functions).
* How to use the random number generation function from the math library.
* How to better define my variables and error messages to make my code more readable.
* How to create gifs from screen capture recordings.

I also got better at making my own tests, and at asking for help from fellow students. 

### Problems I faced
* **Animations**: It was quite challenging to get the fox to move in random directions with a speed that made sense. It was mostly alot of trial and error, and in the end I managed to get a respectable result but it is still not as I hoped it would. I might make some changes someday if I have the time, but for now I need to concentrate my efforts on my other projects! :)
* **Infinite loop**: I ran into some trouble when it came the time to stop the enemy loop. I use the mlx_loop_hook function from the MLX and I could not for the life of me stop the loop after the game was over. Then out of nowhere it hit me: I just needed to define a game status, which could be set to default, OVER or WIN and the loop function would check if the status is set to default and stop if it is not the case. 
* **Endless MLX warnings**: This was mostly annoying more than anything else, but everytime the MLX would compile it would print a multitude of warnings. I had to dig deep to find how to silence them as I was not able to do it with the .SILENT makefile variable or the @.

I would say this is my favorite project so far as I could finally see a real result everytime I added something to my code. It was not as challenging for me as the other projects of this circle (URGHHH pipex!!) but I had alot of fun creating this little game! :)

<div align="center">
<img src="https://user-images.githubusercontent.com/101518532/232920368-79a3e996-c0ee-4b94-b4c5-f4529dba9daa.jpg" alt="Bonnie laying down" width="900" height="450">
  
#### Thank you so much for checking out my project! If you have any questions or comments regarding improvements I could make, do not hesitate to contact me (links on my profile).
  
</div>
