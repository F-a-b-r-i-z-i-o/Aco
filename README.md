# Aco

That proposed is a **easy implementation** of Ant colony optimization algorithms.

<br>

Ant colony algorithms are algorithms inspired by the behavior of ants, or other species forming a superorganism, which are a part of metaheuristic optimization.
The idea arose from observing the exploitation of food resources by ants. In fact, the latter, although limited to the cognitive abilities of a single ant, are collectively able to find the shortest path between a food source and the ant farm.

<hr>

- [Aco](#aco)
  - [Introduction](#introduction)
  - [Compile and Run](#compile-and-run)
    - [Compile](#compile)
    - [Run](#run)
  - [General Description](#general-description)
  - [Formal Description](#formal-description)
  - [Code Description](#code-description)
  - [Conclusion](#conclusion)

<hr>

## Introduction 

The given code appears to be an implementation of the Ant Colony Optimization (ACO) algorithm for the Traveling Salesman Problem (TSP). The TSP is a classic optimization problem where the goal is to find the shortest possible route that visits a given set of cities and returns to the starting city.

## Compile and Run

To compile and run the program you need to have c++11 installed. You can install it here:

[https://isocpp.org/get-started](https://isocpp.org/get-started)

### Compile

For compile you can type:

`make`

In the folder where there are the **Makefile**

### Run

For run you can type:

`./out`

and you will be able to see the **output** of the program.

## General Description

The first ant colony algorithm proposed is the Ant system (literally ant system). It aims to solve the traveling salesman problem, where the goal is to find the shortest way to connect a series of cities.

<br>

The general algorithm is relatively simple and is based on a set of ants, each of which traverses one path from among the possible ones. At each stage, the ant chooses to move from one city to another according to certain rules:

<br>

1. The more distant a city is, the less chance it has of being chosen (the "visibility")
2. The greater the intensity of the pheromone pathway located on the ridge between two cities, the more likely it is to be chosen
3. Once it has completed its path, the ant deposits, on all edges crossed, more pheromone if the path is short
4. Pheromone pathways evaporate with each iteration.

## Formal Description

The displacement rule, called the "random proportional transition rule", is mathematically written as follows:

```math

{\displaystyle p_{ij}^{k}\left(t\right)={\begin{cases}\displaystyle {\frac {\tau _{ij}\left(t\right)^{\alpha }\eta _{ij}^{\beta }}{{\displaystyle \sum _{l\in J_{i}^{k}}}\tau _{il}\left(t\right)^{\alpha }\eta _{il}^{\beta }}},&amp;{\text{con }}j\in J_{i}^{k},\\0,&amp;{\text{con }}j\notin J_{i}^{k},\end{cases}}}

```

where $J_i^k$ Is the list of possible movements of an ant $k$ when it is in a city $i$, $eta_{ij}$ visibility, which is equal to the inverse of distance $d_{i,j}$ between city $i$ and $j$, $\tau_{i,j}(t)$ is the intensity of the track at a given iteration $t$.
The two main parameters that control the algorithm are $\alpha$ and $\beta$ That control the relative importance of the intensity and visibility of an edge.


## Code Description

Here's a brief overview of the main components of the code:

- **Graph Representation:** The distances between cities are represented using a 2D array `graph` of size `kCities x kCities`, where `kCities` is a constant representing the number of cities in the problem. The entry `graph[i][j]` represents the distance from city i to city j.

- **Pheromone Matrix:** The pheromone levels on the edges of the graph are represented using another 2D array `pheromone` of the same size. The entry `pheromone[i][j]` represents the amount of pheromone on the edge between city i and city j.

- **addEdge()** This function is used to add edges to the graph representing the distances between cities. It takes the source city, destination city, and the distance between them as input, and updates the corresponding entries in the `graph` array.

- **printMatrix():** This function is used to print the contents of a 2D matrix, such as the `graph` and `pheromone` arrays, to the console.

- **selectNext():** This function is used by the ants to select the next city to visit based on the pheromone levels and the distances in the `graph` array. It calculates the probabilities of choosing each possible next city using a combination of pheromone levels and distances, and selects a city randomly based on these probabilities.

- **Main Loop:** The main part of the code is the outer loop that iterates over a fixed number of ants (`kAnt`) to perform the ant colony optimization. Inside the loop, each ant selects the next city to visit using the selectNext() function, updates the pheromone levels in the pheromone array, and keeps track of the total length of the tour. After all ants complete their tours, the best tour (i.e., the one with the shortest total length) is printed to the console. The pheromone levels are also updated by evaporating a certain percentage (`vaporization`) of the existing pheromone and adding a small amount of new pheromone to the edges of the best tour.
  
## Conclusion

It's important to note that the given code is just a basic implementation of the ACO algorithm for TSP and may not be optimized for performance. There are many variations and improvements of the ACO algorithm that can be applied depending on the specific requirements of the problem and the desired performance. Additionally, the code does not handle cases where the graph is not fully connected or where there are multiple optimal solutions, as it always assumes a complete graph and looks for a single best solution.

<hr>

*Enjoy 2F*