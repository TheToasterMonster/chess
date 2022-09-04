# Chess

Chess client written in C++.

![](resources/screenshots/starting.png)

## Requirements
- C++17
- [SFML 2.5.1](https://www.sfml-dev.org/)
- [Premake v5.0.0-beta1](https://premake.github.io/)
- Visual Studio 2019
- 64-bit CPU and operating system
- Windows 10 (support for other operating systems may or may not come later)

## Setup
1. Clone the repository:
   ```
   git clone https://github.com/TheToasterMonster/chess.git
   ```
2. Open downloaded folder:
   ```
   cd chess
   ```
3. Run Premake:
   ```
   vendor\bin\premake\premake5.exe vs2019
   ```
4. Open generated `.sln` file in Visual Studio and press `F5` to build.

## Credits
Piece icons from [Wikimedia Commons (SVG chess pieces/Maurizio Monge)](https://commons.wikimedia.org/wiki/Category:SVG_chess_pieces/Maurizio_Monge)

## Screenshots
![](resources/screenshots/moves.png)\
![](resources/screenshots/check.png)\
![](resources/screenshots/mate.png)
