/**
 * A Graph is made up of Vertex objects that hold data values
 * A vertex is connected to other vertices via Edges
 * A vertex can be visited/unvisited
 * Can connect to another vertex via directed edge with weight
 * The edge can be disconnected
 * A vertex cannot have an edge back to itself
 * getNextNeighbor returns the next neighbor each time it is called
 * when there are no more neighbors, the vertex label is returned
 *
 * @author Bill Zhao
 * @date updated on 2/5/2020
 */

#include "vertex.h"
#include "edge.h"
#include <algorithm>

using namespace std;

// << overload
ostream &operator<<(ostream &Os, const Vertex &V) {
  Os << V.Label;
  return Os;
}
Vertex::Vertex(const string &Label) { this->Label = Label; }

// deconstructs vertex
Vertex::~Vertex() { Neighbors.clear(); }

// get the next neighbor of this vertex
string Vertex::next() {
  if (Index < Neighbors.size()) {
    return Neighbors.at(Index)->To->Label;
    Index++;
  }
  return "";
}

// get the weight of the edge connected to the given vertex on the other side
int Vertex::edgeWeight(const string &To) const {
  for (auto Neighbor : Neighbors) {
    if (Neighbor->To->Label == To) {
      return Neighbor->Weight;
    }
  }
  return 0;
}
