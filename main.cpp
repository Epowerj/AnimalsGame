
#include <iostream>
#include <string>
#include "AnimalTree.h"

using namespace std;

void console(AnimalTree& tree);

int main() {
	cout << "Do you want to load a save file? \n(y/n) > ";
	string input;
	getline(cin, input);

	AnimalTree tree;

	if (input == "y" || input == "Y") { // if user wants to load a save
		cout << "filename > ";

		getline(cin, input);

		tree = AnimalTree(input);
	}

	console(tree);

	// save at the end
	cout << "Saving..." << endl;
	tree.save(input);

	return 0;
}

// console io loop
void console(AnimalTree& tree) {
	cout << "Welcome to the Animal Game!" << endl;

	bool playing = true;

	while (playing) {

		// if the current node is a leaf
		if (tree.getCurrent()->isLeaf()) {
			// do a guess on the animal
			cout << "Is it a(n) " << tree.getCurrent()->getText() << "? \n(y/n) > ";

			string input;
			getline(cin, input);

			if (input == "y" || input == "Y") { // user says that ai was correct
				cout << "Yay, I win! \nType r to play again, or x to exit. \n> ";
				getline(cin, input);

				if (input == "x" || input == "X") {
					playing = false;
				}
				else {
					// set current back to root
					tree.resetCurrent();
				}
			}
			else { // wrong guess; need to learn

				cout << "Oh no! I couldn't guess your animal! \nWhat animal were you thinking of? \n> ";

				string newAnimal;
				getline(cin, newAnimal);

				cout << "Okay, I'll learn this new animal. \nPlease ask a question that is true for " <<
					newAnimal << ", but false for " << tree.getCurrent()->getText() << ". \n> ";

				string newQuestion;
				getline(cin, newQuestion);

				// do learn in another funcion
				tree.learnNewAnimal(newAnimal, newQuestion);

				cout << "I'll remember that animal! \nType r to play again, or x to exit. \n> ";
				getline(cin, input);

				if (input == "x" || input == "X") {
					playing = false;
				}
				else {
					// set current back to root
					tree.resetCurrent();
				}
			}
		}
		else { // if the current node isn't a leaf

			cout << tree.getCurrent()->getText() << "\n(y/n) > ";

			string input;
			getline(cin, input);

			// travel down the tree
			if (input == "y" || input == "Y") {
				tree.currentGoYes();
			}
			else if (input == "n" || input == "N") {
				tree.currentGoNo();
			}
		}
	}
}