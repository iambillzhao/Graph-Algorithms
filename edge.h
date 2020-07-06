/**
 * Edge is the simplest structure of the graph
 * All edges are directed
 * Each edge belongs to a vertex
 *
 * @author Bill Zhao
 * @date updated on 2/5/2020
 */
#ifndef EDGE_H
#define EDGE_H

// forward declaration for class Vertex
class Vertex;

class Edge {
  friend class Vertex;
  friend class Graph;

public:
  // use nolint for simplicity, easier to access
  Vertex *From = nullptr; // NOLINT
  Vertex *To = nullptr;   // NOLINT
  int Weight = 0;   // NOLINT
private:
  /** constructor with label and weight */
  Edge(Vertex *From, Vertex *To, int Weight);
};

#endif
