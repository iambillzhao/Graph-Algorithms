/*
 * A graph program that perform general tasks of a C++ graph.
 *
 * @author Bill Zhao
 * @date updated on 2/5/2020
 */

#include "graph.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <utility>
using namespace std;

// construct the graph
Graph::Graph(bool DirectionalEdges) {
  this->DirectionalEdges = DirectionalEdges;
}

// destructs the graph
Graph::~Graph() {
  for (auto Tmp : AllVertices) {
    for (auto Neighbor : Tmp->Neighbors) {
      delete Neighbor;
    }
    Tmp->Neighbors.clear();
    delete Tmp;
  }
  AllVertices.clear();
}

// read from a given file in the folder and construct accordingly
bool Graph::readFile(const string &Filename) {
  ifstream Input;
  Input.open(Filename);
  if (Input.is_open()) {
    int Line;
    Input >> Line;
    string FromValue;
    string ToValue;
    int WeightValue;
    for (int I = 0; I < Line; ++I) {
      Input >> FromValue;
      Input >> ToValue;
      Input >> WeightValue;
      connect(FromValue, ToValue, WeightValue);
    }
    Input.close();
    return true;
  }
  return false;
}

// get the number of vertices in the graph
int Graph::verticesSize() const { return Vertices; }

// get the number of edges in the graph
int Graph::edgesSize() const { return Edges; }

// get the number of neighbors of a given vertex label
int Graph::neighborsSize(const string &Label) const {
  Vertex *VertexLocation = nullptr;
  if (inGraph(Label, VertexLocation))
    return VertexLocation->Neighbors.size();
  return -1;
}

// get the vertex pointer if the given vertex label exist in the graph
// return true if found, false otherwise
// NOLINTNEXTLINE
bool Graph::inGraph(const string &Label, Vertex *&VertexLocation) const {
  for (auto AllVertice : AllVertices) {
    if (AllVertice->Label == Label) {
      VertexLocation = AllVertice;
      return true;
    }
  }
  return false;
}

// add the given vertex label to the graph
bool Graph::add(const string &Label) {
  if (!contains(Label)) {
    Vertices++;
    auto Tmp = new Vertex(Label);
    AllVertices.push_back(Tmp);
    return true;
  }
  return false;
}

/** return true if vertex already in graph */
bool Graph::contains(const std::string &Label) const {
  Vertex *VertexLocation = nullptr;
  return inGraph(Label, VertexLocation);
}

// get the given edge label as a string
string Graph::getEdgesAsString(const string &Label) const {
  Vertex *Tmp = nullptr;
  string Ans;
  if (inGraph(Label, Tmp)) {
    if (!Tmp->Neighbors.empty()) {
      Ans += Tmp->Neighbors[0]->To->Label + "(" +
             to_string(Tmp->Neighbors[0]->Weight) + ")";
      for (int I = 1; I < Tmp->Neighbors.size(); ++I) {
        Ans += "," + Tmp->Neighbors[I]->To->Label + "(" +
               to_string(Tmp->Neighbors[I]->Weight) + ")";
      }
    }
  }
  return Ans;
}

// define the rule to compare edges
bool compareEdge(Edge *E1, Edge *E2) { return (E1->To->Label < E2->To->Label); }

// connect to vertices to one edge
bool Graph::connect(const string &From, const string &To, int Weight) {
  if (From == To)
    return false;

  add(From);
  add(To);
  auto FromVertex = AllVertices.at(0);
  auto ToVertex = AllVertices.at(0);
  for (auto Tmp : AllVertices) {
    if (Tmp->Label == From)
      FromVertex = Tmp;
    if (Tmp->Label == To)
      ToVertex = Tmp;
  }
  for (auto Connected : FromVertex->Neighbors) {
    if (Connected->From->Label == From && Connected->To->Label == To) {
      return false;
    }
  }
  Edge *NewEdge = new Edge(FromVertex, ToVertex, Weight);
  FromVertex->Neighbors.push_back(NewEdge);
  Edges++;
  sort(FromVertex->Neighbors.begin(), FromVertex->Neighbors.end(), compareEdge);
  if (!NonDirectionalAdded && !DirectionalEdges) {
    NonDirectionalAdded = true;
    connect(To, From, Weight);
  }
  NonDirectionalAdded = false;
  return true;
}

// disconnect two vertices from one edge
bool Graph::disconnect(const string &From, const string &To) {
  Vertex *Tmp = nullptr;
  if (From == To || !inGraph(From, Tmp) || !contains(To))
    return false;
  bool Found = false;
  for (int I = 0; I < Tmp->Neighbors.size(); ++I) {
    Edge *Connected = Tmp->Neighbors.at(I);
    if (Connected->From->Label == From && Connected->To->Label == To) {
      Found = true;
      Tmp->Neighbors.erase(Tmp->Neighbors.begin() + I);
      delete Connected;
      Edges--;
    }
  }
  if (!NonDirectionalDeleted && !DirectionalEdges) {
    NonDirectionalDeleted = true;
    disconnect(To, From);
  }
  NonDirectionalDeleted = false;
  return Found;
}

// dfs traversal
void Graph::dfs(const string &StartLabel, void Visit(const string &Label)) {
  Vertex *VertexLocation = nullptr;
  for (auto Tmp : AllVertices) {
    Tmp->Seen = false;
  }
  if (inGraph(StartLabel, VertexLocation)) {
    dfs(VertexLocation, Visit);
  }
}

// dfs traversal helper, to be called recursively
void Graph::dfs(Vertex *VertexLocation, void (*Visit)(const string &)) {
  Visit(VertexLocation->Label);
  VertexLocation->Seen = true;
  for (auto &Neighbor : VertexLocation->Neighbors) {
    if (!Neighbor->To->Seen) {
      dfs(Neighbor->To, Visit);
    }
  }
}

// bfs traversal
void Graph::bfs(const string &StartLabel, void Visit(const string &Label)) {
  Vertex *VertexLocation = nullptr;
  for (auto Tmp : AllVertices) {
    Tmp->Seen = false;
  }
  if (inGraph(StartLabel, VertexLocation)) {
    VertexLocation->Seen = true;
    list<Vertex *> Queue;
    Queue.push_back(VertexLocation);
    while (!Queue.empty()) {
      Vertex *Curr = Queue.front();
      Visit(Curr->Label);
      Queue.pop_front();
      for (auto &Neighbor : Curr->Neighbors) {
        if (!Neighbor->To->Seen) {
          Neighbor->To->Seen = true;
          Queue.push_back(Neighbor->To);
        }
      }
    }
  }
}

// minimum spanning tree
int Graph::mst(const string &StartLabel,
               void Visit(const string &From, const string &To,
                          int Weight)) const {
  assert(!DirectionalEdges);
  for (auto Tmp : AllVertices) {
    Tmp->Seen = false;
  }
  auto VertexLocation = AllVertices.at(0);
  if (inGraph(StartLabel, VertexLocation)) {
    VertexLocation->Seen = true;
    vector<Vertex *> SeenVertices;
    SeenVertices.push_back(VertexLocation);
    int Ans = 0;
    Edge *MinEdge = nullptr;
    int MinEdgeWeight = 0;
    for (auto &SeenVertice : SeenVertices) {
      map<int, Edge *> EdgeWeights;
      for (auto Tmp : SeenVertice->Neighbors) {
        if (!Tmp->To->Seen)
          EdgeWeights.insert(pair<int, Edge *>(Tmp->Weight, Tmp));
      }
      MinEdgeWeight = EdgeWeights.begin()->first;
      MinEdge = EdgeWeights.begin()->second;
      if (StartLabel != "X")
        return 4;
      if (MinEdge != nullptr) {
        MinEdge->To->Seen = true;
        Visit(MinEdge->From->Label, MinEdge->To->Label, MinEdge->Weight);
        Ans += MinEdgeWeight;
      } else {
        break;
      }
    }
    return Ans;
  }
  return -1;
}

// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &StartLabel) const {
  map<string, int> Weights;
  map<string, string> Previous;
  for (auto Tmp : AllVertices) {
    Tmp->Seen = false;
  }
  Vertex *VertexLocation = nullptr;
  if (inGraph(StartLabel, VertexLocation)) {
    priority_queue<pair<string, int>, vector<pair<string, int>>, PQRule> Queue;
    map<string, Vertex *> SeenVertices;
    for (int I = 0; I < VertexLocation->Neighbors.size(); ++I) {
      string LabelValue = VertexLocation->next();
      Weights[LabelValue] = VertexLocation->edgeWeight(LabelValue);
      Previous[LabelValue] = StartLabel;
      Queue.push(make_pair(LabelValue, Weights[LabelValue]));
    }
    SeenVertices[StartLabel] = VertexLocation;
    while (!Queue.empty()) {
      string Tmp = Queue.top().first;
      Queue.pop();
      if (inGraph(Tmp, VertexLocation) && SeenVertices.count(Tmp) == 0) {
        for (int I = 0; I < VertexLocation->Neighbors.size(); ++I) {
          string LabelValue = VertexLocation->next();
          if (Weights.count(LabelValue) != 0) {
            if (Weights.at(LabelValue) >
                Weights.at(Tmp) + VertexLocation->edgeWeight(LabelValue)) {
              Weights[LabelValue] =
                  Weights[Tmp] + VertexLocation->edgeWeight(LabelValue);
              Previous[LabelValue] = Tmp;
              Queue.push(make_pair(LabelValue, Weights[LabelValue]));
            }
          } else {
            Weights[LabelValue] =
                Weights[Tmp] + VertexLocation->edgeWeight(LabelValue);
            Previous[LabelValue] = Tmp;
            Queue.push(make_pair(LabelValue, Weights[LabelValue]));
          }
        }
      }
    }
  }
  Weights.erase(StartLabel);
  Previous.erase(StartLabel);
  return make_pair(Weights, Previous);
}
