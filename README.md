# Pacman 
The purpose of the project: to demonstrate intelligent behavior of virtual characters.

As part of the project, I implemented a Pacman game based on searching for a goal in a two-dimensional maze. In the game AI is played against AI, which means there will be no human intervention. 3 ghosts will chase the pacman. Pacman collects coins. Pacman can overcome one ghost but if two or more ghosts attack him at the same time, the ghosts will win. The fight between Pacman and the Ghost takes time to allow more Ghosts to join the fight.

## Pacman's Behavior:

### Searching for Wind:
- Pacman begins by searching for a nearby wind using a Breadth-First Search (BFS) algorithm with a short range.
- If a ghost is found within the search range, Pacman stops searching and proceeds to move towards it.
- If no ghost is found within the search range, Pacman continues to the next step.
- Pacman's decision making is done by implementing the FSM pattern.
  
### Moving and Collecting Coins:

- Pacman moves around the map and collects coins using a custom algorithm called MoveRandom.
After collecting coins or reaching a certain limit, Pacman searchs for a ghost.

### fight with ghosts:

- If Pacman encounters a single ghost while moving, he wins the fight.
- If multiple ghosts converge on Pacman, he loses the fight.

### End of Program:

- The number of coins collected by Pacman is displayed on the console.
- The program closes after a few seconds.


## Ghosts's Behavior:

### Movement towards Pacman:

- Ghosts activate the A* algorithm to navigate towards Pacman's position.
- Each ghost independently calculates its path to Pacman using A*.
  
### Detecting Proximity to Pacman:

- When a ghost detects that it is close to Pacman, it checks if it is alone or if there are other nearby ghosts.
  
### Handling Single vs. Multiple ghosts:

- If a ghost is alone, it stops and waits for another ghost to join before continuing towards Pacman.
- If there are multiple ghosts nearby, they continue to move towards Pacman and engage in fight if they reach him simultaneously.
  
### End of fight:

- If ghosts defeat Pacman, the game ends.

## Additionally:

Right-clicking on the program enables/disables the option to show the path of Pacman's search. This allows users to visualize the search process.
<img src = "https://github.com/YardenCherry/Pacman/assets/155112044/bd494467-1d2e-43c2-b858-ae0a2ff647b7" alt= pacman1 width= "430" height="430">

<img src = "https://github.com/YardenCherry/Pacman/assets/155112044/bd5c6fa2-5deb-475c-b2d2-5d5dcf897c7b" alt= pacman2 width= "430" height="430">

<img src = "https://github.com/YardenCherry/Pacman/assets/155112044/2de18f6b-f266-4075-82d9-7364bd983077" alt= numOfCoins width= "430" height="430">





