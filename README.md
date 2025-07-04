# DX Tennis
DXT, short for DX Tennis, is a simple 2-player single-device game. The idea was to fuse the two simple, yet vastly popular computer games: DX-Ball &amp; Ping Pong. It was created as our project submission for Structured Programming - 2 lab of the 2nd semester of the CSE-'27 batch of IUT by the team of [Mubtasim Sajid Ahmed](https://github.com/MubtasimSajid), [AKM Ishmam Tahmid](https://github.com/ishmam259), [Mahmudul Hasan Sakib](https://github.com/beiged231) &amp; [Obaidullah](https://github.com/Obaidullah-star). The language used was C & the graphics were rendered using the iGraphics library, which enables developing GUI in C/C++. Sprites drawn with pixel art were sprinkled all around to give the game a playful aesthetic identity.

## Gameplay
Two players control two paddles, one using the keyboard and the other using the mouse. W & S are pressed to move the left bat up or down, respectively & the left & right mouse down do the same for the player to the right. Each player is given a set of bricks to protect. The player to first destroy their opponent's wall fully wins.
A demo video to demonstrate a full play-through for a round is uploaded on Facebook: [DX Tennis Gameplay](https://www.facebook.com/share/v/16D2NfVD7j/)

## Features
1. The game has three difficulty levels to allow the players to tune the game's pacing.
2. There are four types of power-ups (invisibility, board elongation, brick regeneration & fireball) which will spawn at random positions & times during the playthrough. The player to last hit the ball gets to enjoy the power-ups' special advantages (invisibility is rather disadvantageous & fireball has the same effect for both players).
3. Bricks are of three types: the regular brown ones hold up for a single shot, the red ones can endure up to 2 hits & the iron bricks take 3.

We hope that you will find DX Tennis enjoyable & entertaining. Please note that you must have iGraphics properly installed on your machine to compile the files. Cheers! 

## Pre-requisites
1. iGraphics
2. MinGW installed on C:\ drive (for Windows)

## Project Structure
/.vscode - Our VS Code build settings, which we used to run it.

/Images -  The background photos, pixel art sprites & other image elements used in different aspects of the game.

/Sounds - Hosts the sound effects used throughout the gameplay & various menus.

/ - All the .cpp codes, necessary header files for iGraphics to work & everything else needed to build the project reside here.

## 📜 License

This project is licensed under the **GNU General Public License v3.0 (GPLv3)**.

You are free to:

- Use, study, and modify the source code.
- Distribute original or modified versions, **provided they are also licensed under GPLv3**.

> This ensures that all derivative works remain free and open-source under the same license.

For full license details, see the [LICENSE](./LICENSE) file or visit the official GNU website:  
[https://www.gnu.org/licenses/gpl-3.0.html](https://www.gnu.org/licenses/gpl-3.0.html)
