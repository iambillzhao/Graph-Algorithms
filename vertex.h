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

#ifndef VERTEX_H
#define VERTEX_H

#include "edge.h"
#include <string>
#include <vector>


using namespace std;

class Vertex {
  friend class Graph;
  friend class Edge;
  friend ostream &operator<<(ostream &Os, const Vertex &V);

public:
  /** Creates an unvisited vertex, gives it a label, and clears its
      adjacency list.
      NOTE: A vertex must have a unique label that cannot be changed. */
  explicit Vertex(const string &Label);
  /** Destructor. Delete all edges from this vertex to other vertices */
  ~Vertex();
  // get the next neighbor
  string next();
  // get the weight of the weight connected to the given vertex on the other side
  int edgeWeight(string const& To) const;
  string Label; // NOLINT
  // make it public for simplicity

private:
  bool Seen = false;       // boolean check if this vertex is seen
  int Index = 0;           // integer to track the location of the index
                           // for next neighbor
  vector<Edge*> Neighbors; // all neighbors of this vertex
};

#endif  //  ASS3_GRAPHS_VERTEX_H
