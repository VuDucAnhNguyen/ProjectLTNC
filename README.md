# ProjectLTNC
## GAME: MONKEY DAVE
### I. INTRODUCTION:
- Game name: MONKEY DAVE
- Short Description: A platformer game where players control a monkey that jumps between platforms to collect bananas, avoid obstacles, and prevent falling. The game continues until the player loses.
### II. GAMEPLAY:
1. Objective:
- Collect as many bananas as possible to increase your score.
2. How to Play:
- START SCREEN:
  - Play: Opens the map selection menu to choose a map to play.
  - Highscores: Open highscores board showing past scores, Includes a Reset button to reset the high score of a map to 0.
  - Setting: Open setting menu to adjust volume of music and sound effects.
  - Exit: Exit game.
- GAME:  
  - Control monkey press:
    + ← to move left.
    + → to move right.
    + ↑ to jump up.
    + ↓ to jump down.
  - Press ESC to pause game:
    + press Resume to continue playing.
    + press Retry for new game.
    + press Main menu to head back start screen.
    + press Setting to open setting menu to adjust volume of music and sound effects without restarting the gamee.
  - Jump onto platforms to avoid falling off the screen.
  - Avoid obstacles like beehives or other dangerous objects.
  - Game Over: When the monkey falls off the screen or touches an obstacle.
### III. PROJECT STRUCTURE:
- main.cpp: runs the main game loop.
- Initclose.cpp: init SDL, SDL_image, SDL_ttf,... library.
- loadTexture.cpp: load textures from: [MonkeyDave/image_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/image_project).
- loadFont.cpp: load fonts from: [MonkeyDave/font_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/font_project).
- loadAudio.cpp: load sound effects and music from: [MonkeyDave/audio_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/audio_project).
- object.cpp: manage size, speed, color of objects and interact between them.
- textDisplay.cpp: manage size, content, speed, color of texts.
- MonkeyAnimation.cpp: handles monkey movement, animation, and sound.
- mainmenu.cpp: manage UI start menu.
- highscorefile.cpp: load and save highscores from: [MonkeyDave/audio_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/blob/main/MonkeyDave/high_scores.txt).
### IV. TECHNOLOGIES USED:
- C++
- SDL2
- SDL_image
- SDL_ttf
- SDL_mixer
