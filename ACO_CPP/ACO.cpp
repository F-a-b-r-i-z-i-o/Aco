#include <iostream>
#include <set>
#include <numeric>
#include <vector>
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
  cout << "Cities Graph:" << '\n';



}
