#include <iostream>
#include <set>
#include <numeric>
#include <vector>
#include <algorithm>
#include <time.h>
#include <cmath>
#include <limits.h>
using namespace std;

// Define constans
const int kCities = 6;
const int kInfinite = INT_MAX;

// Adds an edge to the graph with the given cost
void addEdge(int graph[][kCities], int from, int to, int cost)
{
    // Throw an error if the source and destination city are the same
    if (to == from)
    {
        throw runtime_error("Source and destination city must be the same");
    }
    // Add the edge with the given cost to the graph
    graph[from][to] = graph[to][from] = cost;
}

// Prints the given matrix to the console
template<class T>
void printMatrix(T graph[][kCities])
{
    for (int i = 0; i < kCities; i++)
    {
        for (int j = 0; j < kCities; j++)
        {
            cout << graph[i][j] << '\t';
        }
        cout << '\n';
    }
}

// Selects the next node to visit based on the current node, the graph, the pheromone levels, and the alpha and beta values
int selectNext(int currentNode,
    int graph[][kCities],
    double pheromone[][kCities],
    vector<int> const& travelledNodes,
    double alpha,
    double beta)
{
    cout << "Current node = " << currentNode << '\n';
    vector<int> possibleNodes;
    vector<double> probabilities;
    for (int i = 0; i < kCities; i++)
    {
        // Check if we've already visited this node
        if (find(travelledNodes.begin(), travelledNodes.end(), i) == travelledNodes.end())
        {
            double distance = graph[currentNode][i];
            // Add this node and its probability to the list of possible next nodes
            possibleNodes.push_back(i);
            probabilities.push_back(pow(pheromone[currentNode][i], alpha) * pow(1/(double)graph[currentNode][i], beta));
        }
    }

    double denominator = 0;
    for (double p : probabilities)
    {
        denominator += p;
    } 

    for (int i = 0; i < probabilities.size(); i++)
    {
        // Normalize the probabilities so they add up to 1
        probabilities[i] /= denominator;
        cout << "Probability to go to city " << i << " = " << probabilities[i] << '\n';
    }

    double r = (double)rand() / RAND_MAX;
    int selectedNode = -1;

    double probabilitySum = 0;

    for (int i=0; i<probabilities.size(); i++)
    {
        double p = probabilities[i];
        if (r >= probabilitySum && r <= probabilitySum + p)
        {
            // Select the next node with a probability proportional to its pheromone level and its distance from the current node
            selectedNode = possibleNodes[i];
            break;
        }
        probabilitySum += p;
    }
    return selectedNode;
}

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    //----parameters
    const int kAnts = 10;
    const double alpha = 1, beta = 1, vaporization = 0.75;
    const int startNode = 0;
    //----

    // Initialize the graph and pheromone matrices
    int graph[kCities][kCities];
    double pheromone[kCities][kCities];

    for (int i = 0; i < kCities; i++)
        for (int j = 0; j < kCities; j++)
        {
            if(i==j)
                graph[i][j] = 0; //the distance from a city to itself is always 0
            else
                graph[i][j] = kInfinite; //initialize all other distances to infinity
        }


    // Crete graph
    addEdge(graph, 0, 1, 14);
    addEdge(graph, 0, 2, 32);
    addEdge(graph, 0, 3, 17);
    addEdge(graph, 0, 4, 52);
    addEdge(graph, 0, 5, 42);

    addEdge(graph, 1, 2, 36);
    addEdge(graph, 1, 3, 14);
    addEdge(graph, 1, 4, 25);
    addEdge(graph, 1, 5, 43);

    addEdge(graph, 2, 3, 40);
    addEdge(graph, 2, 4, 20);
    addEdge(graph, 2, 5, 23);

    addEdge(graph, 3, 4, 25);
    addEdge(graph, 3, 5, 14);

    addEdge(graph, 4, 5, 24);

    cout << "Cities graph:\n";
    
    // Print graph creation 
    printMatrix<int>(graph);

    vector<int> bestPath;
    int bestLength = INT_MAX;

    for (int i = 0; i < kAnts; i++)
    {
        cout << "Ant " << i << '\n';

        // Initialize variables for current ant
        vector<int> travelledNodes;
        int currentNode = startNode;
        int totalLength = 0;

        // While the ant hasn't visited all cities
        while (travelledNodes.size() < kCities)
        {
            // Add current node to list of visited nodes
            travelledNodes.push_back(currentNode);
            // Select next node using ant colony optimization algorithm
            int nextNode = selectNext(currentNode, graph, pheromone, travelledNodes, alpha, beta);
            cout << "Going to node " << nextNode << '\n';
            // If no next node was selected, terminate loop
            if (-1 == nextNode)
            {
                break;
            }
            
            // Add distance from current node to next node to total length
            totalLength += graph[currentNode][nextNode];

            // Update pheromone matrix
            double extraPheromone = 1 / (graph[currentNode][nextNode]); // calculate amount of pheromone to deposit
            
            for (int iVapor = 0; iVapor < kCities; iVapor++)
            {
                for (int jVapor = 0; jVapor < kCities; jVapor++)
                {
                    pheromone[iVapor][jVapor] *= vaporization; // evaporate existing pheromone
                }
                pheromone[currentNode][nextNode] += extraPheromone; // deposit pheromone on edge from current node to next node
                pheromone[nextNode][currentNode] += extraPheromone; // deposit pheromone on edge from next node to current node
            }
            // Move to next node
            currentNode = nextNode;
        }

        cout << "Path found by the ant:\n";
        for (int node : travelledNodes)
        {
            cout << node << ' ';
        }
        
        cout << " length = " << totalLength << '\n';
        // If the path found by the current ant is the best so far, update best path and length
        if (totalLength < bestLength)
        {
            bestLength = totalLength;
            bestPath = travelledNodes;
        }
        
        cout << "Pheromone\n";
        printMatrix<double>(pheromone);
    }

    cout << "Best path found by the ants:\n";
    
    for (int node : bestPath)
    {
        cout << node << ' ';
    }
    
    cout << " length = " << bestLength << '\n';
}
