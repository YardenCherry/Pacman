# Pacman 
The purpose of the project: to demonstrate intelligent behavior of virtual characters.

As part of the project, I implemented a Pacman game based on searching for a goal in a two-dimensional maze. In the game AI is played against AI, which means there will be no human intervention. 3 ghosts will chase the pacman. Pacman collects coins. Pacman can overcome one ghost but if two or more ghosts attack him at the same time, the ghosts will win. The fight between Pacman and the Ghost takes time to allow more Ghosts to join the fight.

The ghosts will calculate the direction of the pursuit according to algorithm *A. For Pacman *A is not suitable because his goal is to be as far away from the ghosts as possible and keep collecting the coins.

Pacman's decision making is done by implementing the FSM pattern.

For Pacman, a depth-limited BFS algorithm has been implemented to locate the wind closest to it. If the wind is closer than a predetermined distance Pacman should move in the opposite direction to the direction of the wind.
