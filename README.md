# MultithreadingExample

C/C++ program written for Linux to simulate a colonization type game. There are two teams: Team A and Team B and they play against each other. The goal is to conquer a rectangular map from the opposing team.

## Rules

1) A certain number (T1 and T2) of team members from both teams should be positioned on the rectangular map (size MxN) using random coordinates (i,j), where 0<=i<M and 0<=j<N. The rest of the map is considered unoccupied territory.

2) A team member cannot occupy the location (i,j) on the map of some other player from the same team or opponent who already occupied that spot

3) Each team member is allowed to fire a missile to a random location (k,l) on the map. If location (k,l) is not occupied yet or the opposite team conquered that location, the location (k,l) will be controlled by the team who fired the missile. If the location was occupied by the same team the location is going to be released by the team. After one missile is fired and handled, each player can fire a new missile and repeat the operation as many times possible till the end of the game. An infinite number of missiles are available for each player. Between two consecutive missile firing, introduce a random 1, 2 or 3 seconds delay simulating the preparation time between missile strike.

4) If the majority around the location (k,l) including the (k,l) once it has changed ownership (see rule 3)) is occupied by the team who sent the missile to that location, all locations in the vicinity (direct neighbors (maximum 8) accessible directly from location (k,l)) will be conquered by the team who sent the missile. 

5) None of the original T1 or T2 locations (see rule 1)) can be destroyed or conquered using rule 3) and 4).

6) The game simulation continues until all the locations are conquered by a team or another. The winner is who has occupied all spots or there is a draw, -meaning that each team owns the same number of locations. No spot on the map should be unoccupied.

## Notes

### Compile
```
g++ main.cpp board.h -pthread
```
### Executable

The executable works like this: `./a.out 10 20 2 3` which means team A will have two (T1=2) players, team B will have 3 (T2=3) players and the map has 10 rows (M) and 20 columns (N).
