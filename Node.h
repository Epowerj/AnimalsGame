#pragma once

#include <string>

using namespace std;

class Node{

public:
	Node(string textVal, Node* noNode, Node* yesNode, Node* parentNode);
	virtual ~Node();

	virtual bool isLeaf();
	virtual string getText();
	virtual Node* getYes();
	virtual Node* getNo();
	virtual Node* getParent();

	virtual void setYes(Node* newYes);
	virtual void setNo(Node* newNo);
	virtual void setParent(Node* newParent);

private:
	string text;
	Node* yes;
	Node* no;
	Node* parent;
};

