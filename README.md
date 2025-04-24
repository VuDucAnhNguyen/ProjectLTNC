# ProjectLTNC
## GAME: MONKEY DAVE
### I. INTRODUCTION:
- Game name: MONKEY DAVE
- Short Description: A platformer game where players control a monkey that jumps between platforms to collect bananas, avoid obstacles, and prevent falling. The game continues until the player loses.
### II. GAMEPLAY:
1. Objective:
- Collect as many bananas as possible to increase your score.
2. How to Play:
- Move left/right to control the monkey.
- Jump onto platforms to avoid falling off the screen.
- Avoid obstacles like beehives or other dangerous objects.
- Game Over: When the monkey falls off the screen or touches an obstacle.
### III. PROJECT STRUCTURE:
- main.cpp: Run main program, game program.
- Initclose.cpp: init SDL, SDL_image, SDL_ttf,... library.
- loadTexture.cpp: load textures from: [MonkeyDave/image_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/image_project).
- loadFont.cpp: load fonts from: [MonkeyDave/font_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/font_project).
- loadAudio.cpp: load sound effects and music from: [MonkeyDave/audio_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/tree/main/MonkeyDave/audio_project).
- object.cpp: manage size, speed, color of objects and interact between them.
- textDisplay.cpp: manage size, content, speed, color of texts.
- MonkeyAnimation.cpp: manage control movements, animations and sounds of monkey object.
- mainmenu.cpp: manage UI start menu.
- highscorefile.cpp: load and save highscores from: [MonkeyDave/audio_project](https://github.com/VuDucAnhNguyen/ProjectLTNC/blob/main/MonkeyDave/high_scores.txt).
