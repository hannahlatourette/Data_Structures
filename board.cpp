#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include "board.h"

//////////////////////// POINTS //////////////////////////////

Point::Point(int x_, int y_) : x(x_),y(y_) {
  // assert positive coordinates
  assert (x_ >= 0);
  assert (y_ >= 0);
}

// helper function for printing Points
std::ostream& operator<<(std::ostream &ostr, const Point &p) {
  ostr << "(" << p.get_x() << "," << p.get_y() << ")";
  return ostr;
}

///////////////////////// NODES //////////////////////////////

Node::Node(Point &p, int nb) : pt_(p), num_bridges(nb) {
	// assert island has at least one bridge but no more than
	// two bridges per side
	assert (nb >= 1 && nb <= 8);
}

// Node::Node(const Node &n) {
// 	this->num_bridges = n.get_bridge_num();
// 	this->pt_ = n.pt();
// }

// Node& Node::operator=(const Node& n) {
// 	pt_ = n.pt();
// 	num_bridges = n.get_bridge_num();
// 	neighbors.clear();
// 	for(int i=0; i<n.get_num_neighbors(); i++)
// 		neighbors.push_back(n.get_neighbor(i));
// }

// Node::~Node() {
// 	for(int i=0; i<neighbors.size(); i++) {
// 		delete neighbors[i];
// 	}
// 	neighbors.clear();
// }

void Node::remove_neighbor(Node* neighbor) {
	int pos = -1;
	for(int i=0; i<neighbors.size(); i++) {
		if(*neighbors[i] == *neighbor) {
			std::cout << "removing neighbor  ";
			std::cout << "n = " << neighbor->pt_x() << " " << neighbor->pt_y() << std::endl;
			// std::cout << "n = " << nodes[i]->pt_x() << " " << nodes[i]->pt_y() << std::endl;
			std::cout << "from node " << this->pt_x() << " " << this->pt_y() << std::endl;
			pos = i;
		}
	}
	assert (pos >= 0); // make sure node* was found in nodes
	neighbors.erase(neighbors.begin()+pos);
	std::cout << "(neighbor erase complete)" << std::endl;
}


//////////////////////// BRIDGES /////////////////////////////

Bridge::Bridge(Node* n1_, Node* n2_) : n1_(n1_), n2_(n2_), pt1_(n1_->pt()), pt2_(n2_->pt()) {
	// bridges must be horizontal or vertical
	assert ((pt1_.get_x() == pt2_.get_x() && pt1_.get_y() != pt2_.get_y()) ||
        	(pt1_.get_x() != pt2_.get_x() && pt1_.get_y() == pt2_.get_y()));
}

std::ostream& operator<<(std::ostream &ostr, Bridge* b) {
  ostr << b->pt1() << "," << b->pt2();
  return ostr;
}

///////////////////////// BOARD /////////////////////////////

Board::Board() {
	// We track the maximum dimensions of the board.
	max_x = 0;
	max_y = 0;
}

void Board::addNode(Point &p, int n) {
  // Incrementally track the maximum dimensions of the board.
	max_x = std::max(p.get_x(),max_x);
	max_y = std::max(p.get_y(),max_y);
	Node* tmp = new Node(p,n);
	// std::cout << "IN ADD NODE: Px AND Py: " << p.get_x() << "  " << p.get_y() << std::endl;
	// std::cout << "IN ADD NODE: TEMP NODE: " << tmp->pt_x() << "  " << tmp->pt_y() << std::endl;
	this->nodes.push_back(tmp);
}

void Board::removeNode(Node* n) {
	std::cout << "*************************begin removing node " << n->pt_x() << " " << n->pt_y() << std::endl;
	std::cout << nodes.size() << std::endl;
	int pos = -1;
	for(int i=0; i<nodes.size(); i++) {
		std::cout << "in for loop" << nodes[i]->pt_x() << " " << nodes[i]->pt_y() << std::endl;
		if(n->pt_y() == 5) {
			std::cout << "here we go ~ " << nodes[i]->pt_x() << " " << nodes[i]->pt_y() << std::endl;
		}
		if(*nodes[i] == *n) {
			std::cout << "removing node ";
			std::cout << n->pt_x() << " " << n->pt_y() << std::endl;
			// std::cout << "n = " << nodes[i]->pt_x() << " " << nodes[i]->pt_y() << std::endl;
			pos = i;
		}
	}
	// int pos = std::find(nodes.begin(), nodes.end(), n) - nodes.begin(); // get index of node* to remove
	// assert (pos <= nodes.size()); // make sure the node* was found 
	assert (pos >= 0); // make sure node* was found in nodes
	nodes.erase(nodes.begin()+pos);
	std::cout << "done removing node " << n->pt_x() << "  " << n->pt_y() << std::endl;
}

void Board::addBridge(Node* a, Node* b) {
	// std::cout << "MAX X AND Y: " << max_x << "  " << max_y << std::endl;
	// std::cout << "Ax AND Bx: " << a->pt_x() << "  " << a->pt_x() << std::endl;
	assert (a->pt_x() <= max_x);
	assert (a->pt_y() <= max_y);
	assert (b->pt_x() <= max_x);
	assert (b->pt_y() <= max_y);
	Bridge* tmp = new Bridge(a,b);
	bridges.push_back(tmp);
}

void Board::removeBridge(Bridge* b) {
	int pos = -1;
	for(int i=0; i<bridges.size(); i++) {
		if(*bridges[i] == *b)
			pos = i;
	}
	assert (pos > 0); // make sure bridge* was found in bridges
	// int pos = std::find(bridges.begin(), bridges.end(); n) - bridges.begin(); // get index of node* to remove
	// assert (pos <= bridges.size()); // make sure the node* was found 
	bridges.erase(bridges.begin()+pos);
	delete b;	
}

void Board::addNeighborData() {
	std::vector<Node*> neighbors_tmp;
	for(int i=0; i<nodes.size(); i++) { // for each node in nodes
		neighbors_tmp.clear();
		for(int j=0; j<nodes.size(); j++) { // compare to each node in nodes
			if(i != j) {
				if((nodes[j]->pt_x() == (nodes[i])->pt_x()) && (nodes[j]->pt_y() > (nodes[i])->pt_y())) {
					neighbors_tmp.push_back(nodes[j]);
				} else if((nodes[j]->pt_x() == (nodes[i])->pt_x()) && (nodes[j]->pt_y() < (nodes[i])->pt_y())) {
					neighbors_tmp.push_back(nodes[j]);
				} else if((nodes[j]->pt_y() == (nodes[i])->pt_y()) && (nodes[j]->pt_x() > (nodes[i])->pt_x())) {
					neighbors_tmp.push_back(nodes[j]);
				} else if((nodes[j]->pt_y() == (nodes[i])->pt_y()) && (nodes[j]->pt_x() < (nodes[i])->pt_x())) {
					neighbors_tmp.push_back(nodes[j]);
				}
			}
		}
		nodes[i]->set_neighbors(neighbors_tmp); // set neighbors vec of node to vec of all neighbors found
	}
}

// void Board::addOriginalNodes() {
// 	Node* tmp;
// 	for(int i=0; i<nodes.size(); i++) {
// 		Node tmp_node = *nodes[i];
// 		tmp = new Node(tmp_node);
// 		original_nodes.push_back(tmp);
// 	}
// }

void Board::updateBoard(int nn) {
	Node* n1 = nodes[0];
	Node* n2 = nodes[0]->get_neighbor(nn);
	std::cout << "numbers: " << n1->get_bridge_num() << "  " << n2->get_bridge_num() <<  std::endl;
	n1->dec_bridge_num();
	std::cout << "node  = " << n1->pt_x() << "  " << n1->pt_y() << std::endl;
	std::cout << "neighbor  = " << n2->pt_x() << "  " << n2->pt_y() << std::endl;
	// std::cout << "after decrement. neiighbor = " << n1->pt_x() << "  " << n1->pt_y() << std::endl;
	n2->dec_bridge_num();
	std::cout << "post dec numbers: " << n1->get_bridge_num() << "  " << n2->get_bridge_num() <<  std::endl;

	addBridge(n1,n2);
		Node* tmp1; // create temporary pointers
		tmp1 = n1;	// in case both n1 and n2
		Node* tmp2; // are removed
		tmp2 = n2;
	
	if((n1->get_bridge_num() == 0) && (n2->get_bridge_num() ==0)) {
		n1->remove_neighbor(tmp2);
		n2->remove_neighbor(tmp1);
		removeNode(n1);
		removeNode(n2);
	} else if(n1->get_bridge_num() == 0) {
		removeNode(n1);
		n2->remove_neighbor(tmp1);
	} else if(n2->get_bridge_num() == 0) {
		removeNode(n2);
		n1->remove_neighbor(tmp2);
	}
	addNeighborData();
}

void Board::revertBoard() {
	Bridge* newest_bridge;
	newest_bridge = bridges[bridges.size()-1];
	Node* n1 = newest_bridge->n1();
	Node* n2 = newest_bridge->n2();
	n1->inc_bridge_num();
	n2->inc_bridge_num();
	this->removeBridge(newest_bridge);
	Point p1 = n1->pt();
	Point p2 = n2->pt();
	// bring back nodes deleted in last update
	if(n1->get_bridge_num() == 1) {
		addNode(p1,1);
	}
	if(n2->get_bridge_num() == 1) {
		addNode(p2,1);
	}
}

void Board::revertNodes() {
	std::cout << ")(@)@()#( reverting nodes" << std::endl;
	Bridge* newest_bridge;
	newest_bridge = bridges[bridges.size()-1];
	Node* n1 = newest_bridge->n1();
	Node* n2 = newest_bridge->n2();
	n1->inc_bridge_num();
	n2->inc_bridge_num();
	std::cout << "node 1 = " << n1->pt_x() << " " << n1->pt_y() << "s = " << n1->get_bridge_num() << std::endl;
	std::cout << "node 2 = " << n2->pt_x() << " " << n2->pt_y() << "s = " << n2->get_bridge_num() << std::endl;
	Point p1 = n1->pt();
	Point p2 = n2->pt();

	if(n1->get_bridge_num() == 1) {
		addNode(p1,1);
	}
	if(n2->get_bridge_num() == 1) {
		addNode(p2,1);
	}
}

void Board::printSolution() const {
  std::cout << "Solution:" << std::endl;
  for (int i = 0; i < bridges.size(); i++) {
    std::cout << bridges[i] << std::endl;
  }
}

void Board::printBoard() const {
	std::cout << "nodes size = " << nodes.size() << "edges size = " << bridges.size() << std::endl;
  // a graph should have at least one node/island
  assert (nodes.size() > 1);
  // the dimensions of the board should be positive
  assert (max_x >= 0);
  assert (max_y >= 0);

  // allocate an empty/blank board, twice as big in each dimension so
  // we can draw lines between the nodes/islands.
  std::vector<std::string> board(2*max_y+1,std::string(2*max_x+1,' '));
  // mark all of the islands with their bridge count
  for (int i = 0; i < nodes.size(); i++) {
    const Point &pt = nodes[i]->pt(); 
    std::string value = std::to_string(nodes[i]->get_bridge_num());
    board[2*pt.get_y()][2*pt.get_x()] = value[0];
  }

  // loop over all of the edges/bridges
  for (int i = 0; i < bridges.size(); i++) {
    Point a = bridges[i]->pt1();
    Point b = bridges[i]->pt1();
    // determine the edge/edge direction
    int diff_x = b.get_x()-a.get_x();
    int diff_y = b.get_y()-a.get_y();
    if (diff_x > 0) diff_x = 1;
    if (diff_x < 0) diff_x = -1;
    if (diff_y > 0) diff_y = 1;
    if (diff_y < 0) diff_y = -1;

    // walk between the islands to draw the bridge
    int x = a.get_x()*2+diff_x;
    int y = a.get_y()*2+diff_y;
    while (x != b.get_x()*2 || y != b.get_y()*2) {
      if (diff_x == 0) {
        // vertical bridge
        assert (diff_y != 0);
        if (board[y][x] == '|') {
          // if we already have a bridge, draw a double vertical bridge
          board[y][x] = '#';
        } else {
          assert (board[y][x] == ' ');
          // otherwise draw a single vertical bridge
          board[y][x] = '|';        
        }
      } else {
        assert (diff_y == 0);
        // horizontal bridge
        if (board[y][x] == '-') {
          // if we already have a brige, draw a double horizontal bridge
          board[y][x] = '=';        
        } else {
          assert (board[y][x] == ' ');
          // otherwise draw a single horizontal bridge
          board[y][x] = '-';        
        }
      }
      x+=diff_x;
      y+=diff_y;
    }
  }

  // surround the board with a border of spaces
  char border = ' ';
  std::cout << std::string(board[0].size()+2,border) << std::endl;
  for(int i = board.size()-1; i >= 0; i--) {
    std::cout << border << board[i] << border << std::endl;
  }
  std::cout << std::string(board[0].size()+2,border) << std::endl;
}

bool Board::threeBridges(Node* n1_, Node* n2_) const {
	int count = 0;
	for(int i=0; i<bridges.size(); i++) {
		if(((bridges[i]->n1() == n1_) && (bridges[i]->n2() == n2_)) ||
		   ((bridges[i]->n1() == n2_) && (bridges[i]->n2() == n1_)))
			count++;
	}
	assert (count < 4);
	return (count > 2);
}

bool Board::isEmpty() const {
	return (nodes.size() == 0);
}

bool Board::isIllegal() const {
	bool illegal = false;
	if(bridges.size() > 0) {
		Bridge* newest_bridge;
		newest_bridge = bridges[bridges.size()-1];
		Node* n1 = newest_bridge->n1();
		Node* n2 = newest_bridge->n2();
		if((n1->get_bridge_num() < 0) || (n2->get_bridge_num() < 0)) {
			illegal = true;
		} else if(this->threeBridges(n1,n2)) {
			illegal = true;
		} else if(this->isIntersecting(newest_bridge)) {
			illegal = true;
		} else if(nodes.size() == 1) {
			illegal = true;
		} else if(nodes.size() == 2) {
			// if only 2 islands remain, island 2 must be a 
			// neighbor of island 1
			bool neighbor_found = false;
			n1 = nodes[0];
			n2 = nodes[1];
			for(int i=0; i<n1->get_num_neighbors(); i++) {
				if(n1->get_neighbor(i) == n2)
					neighbor_found = true;
			}
			illegal = !neighbor_found;
		}
	}
	return illegal;
}