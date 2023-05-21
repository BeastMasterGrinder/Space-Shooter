# Space Shooter

Welcome to the Space Shooter repository! This project is a game developed in C++ using the SFML library, with a focus on Object-Oriented Programming (OOP) concepts. In this game, you control a spaceship and navigate through space while shooting down enemy ships.

## Installation

To run this game, you need to have the following dependencies installed:

- SFML library (version 2.5.1 or later)

Once you have the dependencies installed, follow these steps to run the game:

1. Clone this repository to your local machine using the following command:

```shell
git clone https://github.com/your-username/space-shooter.git
```

2. Navigate to the project directory:

```shell
cd space-shooter
```

3. Compile the source code using a C++ compiler (e.g., g++):

```shell
g++ -o space-shooter main.cpp Game.cpp Player.cpp Enemy.cpp Bullet.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

4. Run the compiled executable:

```shell
./space-shooter
```

## Gameplay

The objective of the game is to survive as long as possible and achieve the highest score by shooting down enemy ships. Here are the controls:

- Use the **arrow keys** to move the player spaceship.
- Press the **spacebar** to shoot bullets at the enemy ships.

Avoid colliding with enemy ships or their bullets, as it will result in the player losing health. If the player's health reaches zero, the game is over.

## Project Structure

The project's file structure is organized as follows:

```
space-shooter/
├── main.cpp
├── Game.cpp
├── Game.h
├── Player.cpp
├── Player.h
├── Enemy.cpp
├── Enemy.h
├── Bullet.cpp
├── Bullet.h
├── assets/
│   ├── player.png
│   ├── enemy.png
│   ├── bullet.png
│   └── ...
└── README.md
```

- `main.cpp`: The entry point of the game that initializes the game window and starts the game loop.
- `Game.cpp` and `Game.h`: The Game class, responsible for managing the game state, handling user input, updating entities, and rendering the game.
- `Player.cpp` and `Player.h`: The Player class, representing the player-controlled spaceship. It handles player movement, shooting, and collision detection.
- `Enemy.cpp` and `Enemy.h`: The Enemy class, representing the enemy spaceships. It handles enemy movement, shooting, and collision detection.
- `Bullet.cpp` and `Bullet.h`: The Bullet class, representing the bullets shot by the player and enemies. It handles bullet movement and collision detection.
- `assets/`: Directory containing game assets such as images, sounds, and fonts.

Feel free to explore the source code and make modifications or improvements as needed. If you encounter any issues or have suggestions, please create an issue in the repository.

## Contributing

Contributions to this project are welcome! If you'd like to contribute, please follow these steps:





1. Fork the repository.
2. Create a new branch for your feature or bug fix: `git checkout -b feature/your-feature-name` or `git checkout -b bugfix/your-bug-fix`.
3. Make your changes and commit them with descriptive commit messages.
4. Push your changes to your forked repository.
5. Submit a pull request explaining your changes and their benefits.

Please ensure that your code follows the project's coding style and conventions.

## License

This project is licensed under the MIT License. For

 more information, please refer to the [LICENSE](LICENSE) file.

Enjoy playing Space Shooter! If you have any questions or need further assistance, feel free to contact the project maintainers.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Here is a video demo for the game!

https://github.com/BeastMasterGrinder/Space-Shooter/assets/86410882/5a81f215-be18-4737-bc95-5ebeb746ce5b

