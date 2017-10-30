#include <vector>
#include <cassert>
#include <string>

class Board;

//////////////////////////////////////////////////////////////////
/*********************
 **   Point Class   **
 *********************/
class Point {
public:
  // constructor
  Point(int x_, int y_);
  // accessors
  int get_x() const { return x; }
  int get_y() const { return y; }
  // operators
  bool operator==(const Point &p) { return ((x == p.get_x()) && (y == p.get_y())); }
private:
  // representation
  int x;
  int y;
};

// helper function for printing Points
std::ostream& operator<<(std::ostream &ostr, const Point &p);

//////////////////////////////////////////////////////////////////
/*********************
 **   Node Class   **
 *********************/
class Node {
public:
	// constructor, copy constructor
	Node(Point &p, int nb);
	// Node(const Node& n);
	// Node& operator=(const Node& n);
	// ~Node();
	// accessors
	Point pt() const { return pt_; }
	int pt_x() const { return pt_.get_x(); }
	int pt_y() const { return pt_.get_y(); }
	int get_bridge_num() const { return num_bridges; }
	int get_num_neighbors() const { return neighbors.size(); }
	Node* get_neighbor(int nn) const { return neighbors[nn]; }
	// modifiers
	void set_neighbors(const std::vector<Node*> &neighbors_) { neighbors = neighbors_; }
	// void add_neighbor(Node* n);
	void remove_neighbor(Node* n);
	// operators
	void inc_bridge_num() { num_bridges += 1; } // for easy board updating
	void dec_bridge_num() { num_bridges -= 1; }
	bool operator==(const Node &n) { return ((pt_ == n.pt()) && (num_bridges == n.get_bridge_num())); }
private:
	Point pt_;
	int num_bridges;
	std::vector<Node*> neighbors;
};

//////////////////////////////////////////////////////////////////
/*********************
 **   Bridge Class   **
 *********************/
class Bridge {
public:
	// constructor, destructor
	Bridge(Node* n_1, Node* n_2);
	// accessors
	Node* n1() const { return n1_; }
	Node* n2() const { return n2_; }
	Point pt1() const { return n1_->pt(); }
	Point pt2() const { return n2_->pt(); }
	// operators
	bool operator==(const Bridge &b) { return ((n1_ == b.n1()) && (n2_ == b.n2())
											|| (n1_ == b.n2()) && (n2_ == b.n1())); 
	// other


private:
	// representation
	Node* n1_;
	Node* n2_;
	Point pt1_;
	Point pt2_;
};

// helper function for printing bridges
std::ostream& operator<<(std::ostream &ostr, Bridge* b);


//////////////////////////////////////////////////////////////////
/*********************
 **   Board Class   **
 *********************/
class Board {
public:
  // constructor
  Board();
  // modifiers
  void addNode(Point &p, int n);
  void removeNode(Node* n);
  void addBridge(Node* a, Node* b);
  void removeBridge(Bridge* b);
  void addNeighborData();
  // void addOriginalNodes();
  // recursive helpers
  void updateBoard(int nn);
  void revertBoard();
  void revertNodes();
  // print helper functions
  void printSolution() const;
  void printBoard() const;
  // accessors
  std::vector<Node*> get_nodes() const { return nodes; }
  int get_node_size() const { std::cout << "IN FUNCTION NODE SIZE = " << nodes.size() << std::endl; }
  int get_max_x() const { return max_x; }
  int get_max_y() const { return max_y; }
  // boolin
  bool threeBridges(Node* n1, Node* n2) const;
  bool isIntersecting(Bridge* nb);
  bool isEmpty() const;
  bool isIllegal() const;
private:
  // representation
  int max_x;
  int max_y;
  std::vector<Node*> nodes;
  // std::vector<Node*> original_nodes;
  // std::vector<int> neighbors; // corresponds to nodes
  std::vector<Bridge*> bridges;
};