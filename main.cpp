#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "board.h"

bool recursive_bridge(Board &b, int nn) {
  std::vector<Node*> nodes = b.get_nodes();
  if(b.isIllegal()) {
    std::cout << "ILLEGAL. REVERTING.." << std::endl;
    b.revertBoard();
    return false;
  }
  if(b.isEmpty()) {
    std::cout << "EMPTY. RETURNING TRUE..." << std::endl;
    return true;
  }
  else {
    std::cout << "ELSE. UPDATING..." << std::endl;
    b.updateBoard(nn);
    for(int i=0; i<nodes[0]->get_num_neighbors(); i++) {
      std::cout << "FOR LOOP. i = " << nn << std::endl;
      recursive_bridge(b,i);
      std::cout << "~~ after recursion. nodes: " << nodes.size() << std::endl;
      // b.revertNodes();
    }
  }
    std::cout << "~~~~ after recursive for loop. nodes.size() = " << nodes.size() << std::endl;
}


int main(int argc, char* argv[] ) {

  
  // Parse the arguments
  if (argc < 2) {
    std::cout << "ERROR!  Must specify input file" << std::endl;
    exit(1);
  }
  std::ifstream istr(argv[1]);
  if (!istr.good()) {
    std::cout << "ERROR!  Could not open input file '" << argv[1] << "'" << std::endl;
    exit(1);
  }
  bool find_all_solutions = false;
  bool connected = false;
  for (int i = 2; i < argc; i++) {
    if (argv[i] == std::string("--find_all_solutions")) {
      find_all_solutions = true;
    } else if (argv[i] == std::string("--connected")) {
      connected = true;
    } else {
      std::cout << "ERROR!  Unknown argument '" << argv[i] << "'" << std::endl;
      exit(1);
    }
  }



  // Create an empty board object
  Board b;
  // Read in the puzzle from the input file
  int x,y,n;
  std::vector<Point> pts;
  while (istr >> x >> y >> n) {
    Point tmp = Point(x,y);
    std::cout << " TMP X AND Y: " << tmp.get_x() << "  " << tmp.get_y() << std::endl;
    pts.push_back(tmp);
    b.addNode(tmp,n);
  }

  b.get_node_size();
  b.printBoard();
  // b.addOriginalNodes();
  b.addNeighborData();
  recursive_bridge(b,0);
  b.get_node_size();
  b.printSolution();
  b.printBoard();

  // // The statements below hardcode the solution to puzzle1.txt.
  // // You should remove this code and replace it with a general solver.
  // if (argv[1] == std::string("puzzle1.txt")) {
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[0],pts[1]);
  //   g.addEdge(pts[1],pts[2]);
  //   g.addEdge(pts[1],pts[2]);
  //   g.addEdge(pts[2],pts[3]);

  //   // print the edges (any order is ok)
  //   g.printSolution();
  // }

  // // print a visualization of the (solved or unsolved) puzzle
  // g.printGraph();

}
