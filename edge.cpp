/**
 * Edge is the simplest structure of the graph
 * All edges are directed
 * Each edge belongs to a vertex
 *
 * @author Bill Zhao
 * @date updated on 2/5/2020
 */

#include "edge.h"

// constructs an edge
Edge::Edge(Vertex *From, Vertex *To, int Weight) {
  this->From = From;
  this->To = To;
  this->Weight = Weight;
}
