# ProjectLTNC
## GAME: MONKEY DAVE
### Student: Nguyễn Vũ Đức Anh, MSV: 24022765
- Ngưỡng điểm mong muốn: 8.5
- Game tự viết có đồ họa đơn giản.
### I. INTRODUCTION:
- Game name: MONKEY DAVE
- Short Description: A platformer game where players control a monkey that jumps between platforms to collect bananas, avoid obstacles, and prevent falling. The game continues until the player loses.
### II. GAMEPLAY:
1. Objective:
- Collect as many bananas as possible to increase your score.
2. How to Play:
- START MENU:
  - Play: Opens the map selection menu to choose a map to play.
  - Highscores: Open highscores board showing past scores, Includes a Reset button to reset the high score of a map to 0.
  - Setting: Open setting menu to adjust volume of music and sound effects.
  - Exit: Exit game.
- GAME:  
  - Control the monkey using the keyboard:
    + ← to move left.
    + → to move right.
    + ↑ to jump up.
    + ↓ to jump down.
  - Press ESC to pause game:
    + Resume to continue playing.
    + Retry for new game.
    + Main menu to head back start menu.
    + Setting to open setting menu to adjust volume of music and sound effects without restarting the game.
  - Jump onto platforms to avoid falling off the screen.
  - Avoid obstacles like beehives or other dangerous objects.
  - Game Over: When the monkey or banana falls off the screen or the monkey touches an obstacle.
### III. PROJECT STRUCTURE:
- main.cpp: Runs the main game loop.
- Initclose.cpp: Initializes SDL, SDL_image, SDL_ttf, and other libraries.
- loadTexture.cpp: Loads textures from: [MonkeyDave/image_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/image_project).
- loadFont.cpp: Loads fonts from: [MonkeyDave/font_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/font_project).
- loadAudio.cpp: Loads sound effects and music from: [MonkeyDave/audio_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/audio_project).
- object.cpp: Manages size, speed, color of objects and interactions between them.
- textDisplay.cpp: Manages size, content, speed, color of texts.
- MonkeyAnimation.cpp: Handles monkey movement, animation, and sound.
- mainmenu.cpp: Manages UI start menu.
- highscorefile.cpp: Loads and saves highscores from: [MonkeyDave/high_scores.txt](https://github.com/VuDucAnhNguyen/ProjectLTNC/blob/main/MonkeyDave/high_scores.txt).
### IV. TECHNOLOGIES USED:
- C++
- SDL2
- SDL_image
- SDL_ttf
- SDL_mixer
