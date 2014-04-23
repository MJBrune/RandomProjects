#include <iostream>
#include <cstdlib>
#include "bst.h"
#include "avl.h"
using namespace std;
const size_t BUFFER_SIZE = 256;
//----------------------------------------------------------------------------
// Test Driver for AVL and node classes
// Compiled under MS Visual C++.Net 2003
// by Binary Tree Friends
// June, 2012
//----------------------------------------------------------------------------
int main(void)
{
	using BTF_BST::bst;
	using BTF_BST::avl;
	using BTF_BST::node;

	avl<char> test;
	test.insert('a');
	test.insert('b');
	test.insert('c');
	test.printXlevel(cout);
	cout << "popped: " << test.popfirst('b', test.getroot()) << endl;
	test.printXlevel(cout);
	avl<char> test2 = test;
	test2 += test;
	test2.printXlevel(cout);
	node<char>* findmatch = NULL;
	test.findfirst('c', test.getroot(), findmatch);
	if (findmatch != NULL)
		cout << "found" << endl;
	cout << test << " : " << test.getNumberOfNodes()
			<< "nodes" << endl;
	test.poplow(test.getroot());
	test.printXlevel(cout);
	test.popnode(test.getroot());
	if(test.isempty())
		cout << "test is empty" << endl;
	test = test + 'd';
	test.printXlevel(cout);
	test.deltree();
	if(test.isempty())
		cout << "test is empty"<< endl;
	test2.printXlevel(cout);
	cout << test2.getHeight()<< endl;
	test2.pophigh(test2.getroot());
	test2.printXlevel(cout);
	cin.get();
	try
	{
		avl<char> tree;
		node<char>* marker = NULL;
		char c;
		cout << "enter some characters, followed by <Enter>.\n" ;
		do
		{ 
			cin.get(c);
			if(c == '\n')
				break;
			if(!isspace(c))
				tree.insert(c); 
		}
		while(1);
		avl<char> tree2 = tree; // test overloaded =
		tree2 += tree; // test overloaded +
		cout << "tree 1:" << endl;		
		cout << tree << " : " << tree.getNumberOfNodes()
			<< "nodes" << endl;  // test overloaded << and print()
		tree.printXlevel(cout);
		cout  << endl << "tree 2:" << tree2 
			<< tree.getNumberOfNodes() << "nodes" << endl;
		tree2.printXlevel(cout);
		cout << endl << endl << "Enter character to match: ";
		cin >> c;
		tree.findfirst(c, tree.getroot(), marker);
 
		// set marker to first match of c
		if(marker != NULL)
			cout << marker->value();
		else
			cout << "not found";
		cout << endl << endl;
		tree.printXlevel(cout);
		cout << "\n Enter character to delete : ";
		cin >> c;
		cin.ignore(BUFFER_SIZE, '\n');
		c = tree.popfirst(c, tree.getroot());
  
		// test popfirst(), popnode(), poplow()	
		cout << "<" << c << ">  " << tree << endl;
		tree.printXlevel(cout);
		cout << endl;
		tree.deltree();  //delete first tree
		tree2 += 'Z';     // add in another element , test +=
		tree2 = tree2 + 'Y';  // test +		
		cout << tree2 << endl;
		cout << "tree 1:" << endl;		
		cout << tree << " : " << tree.getNumberOfNodes()
			<< "nodes" << endl;  // test overloaded << and print()
		tree.printXlevel(cout);
		cout  << endl << "tree 2:" << tree2 
			<< tree.getNumberOfNodes() << "nodes" << endl;
		tree2.printXlevel(cout);
		cout << endl;
		tree.deltree();  //delete second tree  
	}
	catch(invalid_argument e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(exception e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	cout << "press \"Enter\" to continue" << endl;
	cin.get(); // keep window open
	return EXIT_SUCCESS;
} 