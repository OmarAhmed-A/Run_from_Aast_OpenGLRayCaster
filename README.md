
# OpenGL-raycaster

![gif illustrating the game][GIF]

## About

This game was made as a project for CC-212 (Applied programming course) at AAST university by Omar Ahmed (20107196), semester 3.

## Other features not shown in gif

- saving score of winning players.
- sorting scores by best time.
- showing the top five scores when game is started.
- very easy to edit map or create new level in source.

## Controls

to move around use WASD and open doors by pressing E
(Don't let the monster touch you...)

## **Running the executable on windows:**

to run the program locally just clone the repo and run the included executable.
the glut dynamic library (glut.dll) is required to run the executable and is already available within the repo.

## **Building from source:**

to build from source just make sure to link glut which is a deprecated opengl library or freeglut which is the currently maintained version which is also open source.
[freeglut install guide](http://freeglut.sourceforge.net/docs/install.php)

VScode build files included could be run to build from source if you have glut library in your compiler's include folder.

[GIF]: [https://media.giphy.com/media/zmTNhRsSOmhQtvD6xs/giphy-downsized-large.gif](https://media.giphy.com/media/zmTNhRsSOmhQtvD6xs/giphy.gif)
