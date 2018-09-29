
#include "Node.h"
#include <string>

using namespace std;

Node::Node(string textVal, Node* noNode, Node* yesNode, Node* parentNode){
	parent = parentNode;
	text = textVal;
	no = noNode;
	yes = yesNode;
}

Node::~Node(){
}

// returns true if this node doesn't have children and is therefore an 'answer' node
bool Node::isLeaf() {
	return (getYes() == 0 && getNo() == 0);
}

string Node::getText() {
	return text;
}

Node* Node::getYes() {
	return yes;
}

Node* Node::getNo() {
	return no;
}

Node* Node::getParent() {
	return parent;
}

void Node::setYes(Node* newYes) {
	yes = newYes;
}

void Node::setNo(Node* newNo) {
	no = newNo;
}

void Node::setParent(Node* newParent) {
	parent = newParent;
}
