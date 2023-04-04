#include <iostream>
#include <set>
#include <numeric>
#include <vector>
#include <algorithm>
#include <time.h>
#include <cmath>
#include <climits>

using namespace std;

const int kCities = 6;
const int kInfinite = INT_MAX;

void addEdge(int graph[][kCities], int from, int to, int cost)
{
  if(to==from)
    throw runtime_error("Source and destination city must be the same");

  graph[from][to] = graph[to][from] = cost;
}

template<class T>
void printMAtrix(T graph[][kCities])
{
  for (int i = 0; i < kCities; i++)
  {
    for (int j=0; j < kCities; j++)
    {
      cout << graph[i][j] << '\n';
    }
  }
}

int selectNext(int currentNode,
               int graph[][kCities],
               double pherormone[][kCities],
               vector<int> const& travelNodes,
               double alpha,
               double beta
            )
{

  vector<int> possibileNodes;
  vector<double> probabilities;
  for(int  i = 0; i < kCities; i++)
  {
    if(find(travelNodes.begin(), travelNodes.end(), i) == travelNodes.end())

      possibileNodes.push_back(i);
      probabilities.push_back(pow(pherormone[currentNode][i], alpha) * pow(1/(double)graph[currentNode][i], beta));
  }

  double denominator = 0;
  for (double p:probabilities)
  {
    denominator += p;
  }

  // p = {0.1, 0.2, 0.3}
  // r = 0.15
  for (int i = 0; i < probabilities.size(); i++)
  {
    probabilities[i] /= denominator;
    cout << "Probability to go to city " << possibileNodes[i] <<  " = " << probabilities[i] << '\n';
  }

  double r = (double)rand() / RAND_MAX;
  int selectedNode = -1;
  double probabilitySum = 0;

  // possibileNodes = {1,2,3}
  for (int i = 0; i < probabilities.size(); i++)
  {
    double p = probabilities[i];
    if (r >= probabilitySum && r <= probabilitySum + r)
      selectedNode = possibileNodes[i];
      break;

    probabilitySum += p;
  }

  return selectedNode;

}

int main()
{
  srand(time(NULL));
  //---parameters
  const int kAnts = 100;
  const double alpha = 1, beta = 1, vaporization = 0.75;
  const int startNode = 0;

  //---
  int graph[kCities][kCities];
  double pherormone [kCities][kCities];

  for(int i = 0; i<kCities; i++)
  {
    for (int j = 0; j<kCities; j++)
    {
      if(i==j)
        graph[i][j] = 0; //the distance from a city to itself is always 0
      else
        graph[i][j] = kInfinite;
    }

  }

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
addEdge(graph, 3, 5, 24);

addEdge(graph, 4, 5, 24);

cout << "Cities Graph:" << '\n';

printMAtrix<int>(graph);
printMAtrix<double>(pherormone);
vector<int> bestPath;
int bastLenght = INT_MAX;

for (int i  = 0; i < kAnts; i++)
{
  cout << "Ant " << i << '\n';
  vector<int> travelNodes;
  int currentNode = startNode;
  int totalLength = 0;

  while (travelNodes.size() < kCities)
  {
      travelNodes.push_back(currentNode);
      int nextNode = selectNext(currentNode, graph, pherormone, travelNodes, alpha, beta);
      cout << "Going to node" << nextNode << '\n';

      if(-1 == nextNode)
        break;

        totalLength += graph[currentNode][nextNode];

        //update pherormone matrix
        double extraPherormone = 1 / (graph[currentNode][nextNode]);
        for (int iVapor = 0; iVapor < kCities; iVapor++)
        {
          for (int jVapor = 0; jVapor < kCities; jVapor++)
          {
            pherormone[iVapor][jVapor] *= vaporization;
          }
          pherormone[currentNode][nextNode] += extraPherormone;
          pherormone[nextNode][currentNode] += extraPherormone;

          currentNode = nextNode;
        }

        // Print solution found
        cout << "Best path found by the ant: \n" << '\n';
        for (int node : bestPath)
        {
          std::cout << node << ' ';
        }
        cout << '\n';

        cout << "Lenght = " << bastLenght <<'\n';

        if(totalLength < bastLenght)
          bastLenght = totalLength;
          bestPath = travelNodes;
  }
}



}
