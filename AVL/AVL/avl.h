#ifndef AVL_H
#define AVL_H
//--------------------------------------------------------------------
// An AVL tree class
// Compiled under MS Visual C++.Net 2010
// by Binary Tree Friends
// June, 2012
//--------------------------------------------------------------------
#include "bst.h"
using namespace std;

namespace BTF_BST
{
//--------------------------------------------------------------------
// AVL Tree
//   Class: avl<T>: public bst<T>
//   REQUIRES Type T be able convert from int & have < & == defined
//
//   File: avl.h
//   Title: avl template Class -- inherits from bst<T>
//   Description: This file contains the class definition for avl
//
//   Programmer:  Binary Tree Friends
// 
//   Date:  June 2012
//   Version: 1.0
// 
//   Environment: Hardware: IBM Pentium 
//   Software: Windows 7 or .Net Framework for execution;
//
//   Compiles under Microsoft Visual C++.Net 2010
// 
//   class avl<T>:
//
//
//     Methods:
// 
//       inline: 
//			avl() -- default constructor
//			avl(const avl<T>& t) -- copy constructor (deep copy)
//			avl<T>& operator+=(const T d) -- adds an element to the tree
//			avl<T> operator+(const T d) -- adds an element to the tree
//			void insert(T d) -- adds an element to the tree
//			~avl() -- destructor	
//
//       non-inline:
//			avl<T>& operator=(const avl<T>& t) -- deep copy
//			avl<T>& operator+=(const avl<T>& t) -- adds an element to the tree
//			void insert(T d, node<T>* &cur) -- adds an element to the tree
//			T popnode(node<T>* &cur) -- returns element in node deleted
//			T poplow(node<T>* &cur) -- returns element in leftmost node (deleted)
//			T popfirst(const T& d, node<T>* np)
//				-- returns element in first node matching d (deleted)
//		protected:
//			node<T>* rotateRight(node<T> *nodeN) -- balances tree	
//			node<T>* rotateLeft(node<T> *nodeN) -- balances tree
//			node<T>* rotateRightLeft(node<T> *nodeN) -- balances tree
//			node<T>* rotateLeftRight(node<T> *nodeN) -- balances tree
//			node<T>* rebalance(node<T> *&nodeN) -- balances tree
//			int getHeightDifference(const node<T> *const nodeN)const
//				-- returns the height difference between the left & right subtrees 
//
//
//   History Log: 
//     6/7/12 BTF Completed Version 1.0
//------------------------------------------------------------------- 
	template<class T>
	class avl: public bst<T>
	{    
	public:
		avl() : bst(){}
		avl(const avl<T>& t) : bst(t){}
		avl<T>& operator=(const avl<T>& t);
		avl<T>& operator+=(const avl<T>& t);
		avl<T>& operator+=(const T d){insert(d); return *this;}
		avl<T> operator+(const T d)
		{avl<T> temp = *this; temp.insert(d); return temp;}
		void insert(T d) {insert(d, root);}
		void insert(T d, node<T>* &cur);
		T popnode(node<T>* &cur);
		T poplow(node<T>* &cur);
		T popfirst(const T& d, node<T>* np);
		~avl() {deltree();}
	protected:
		node<T>* rotateRight(node<T> *nodeN);	
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);
		int getHeightDifference(const node<T> *const nodeN)const;
		//void findfirst(const T& d, node<T>* &np, node<T>* &match);
		//T m_contents;
	};
//-----------------------------------------------------------------------------
//	method:			avl<T>& avl<T>::operator=(const avl<T>& t) -- copy operator
//	description:	does a deep copy of one tree into another
//	Calls:			
//	Called By:		main()
//	Parameters:		const avl<T>& t -- the tree that is to be copied
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------
	template <class T>
	avl<T>& avl<T>::operator=(const avl<T>& t)
	{
		if(this != &t)
		{
			if(!isempty())
				deltree();
			if(!t.isempty())
				root = new node<T>(*(t.root));
		}
		return *this;
	}
//-----------------------------------------------------------------------------
//	method:			avl<T>& avl<T>::operator+=(const avl<T>& t)
//	description:	adds tree t to existing tree
//	Calls:			bst::addtree()
//	Called By:		main()
//	Parameters:		const avl<T>& t -- the tree that is to be added
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template <class T>
	avl<T>& avl<T>::operator+=(const avl<T>& t)
	{
		addtree(t.root);
		return *this;
	}
//-----------------------------------------------------------------------------
//	method:			void avl<T>::insert(T d, node<T>* &cur)
//	description:	inserts an element into the tree
//	Calls:			bst::insert(), rebalance(), setHeight()
//	Called By:		main()
//	Parameters:		T d -- element to be inserted
//					node<T>* &cur -- the current node
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template <class T>
	void avl<T>::insert(T d, node<T>* &cur)
	{
		if(cur == nullptr)
		{                       
			cur = new node<T>(d);
			if(isempty())
				root = cur;
		}
		else
		{
			if(d < cur->value())
				insert(d, cur->left);
			else
				insert(d, cur->right);
			if(root != nullptr)
				root->setHeight();
		}
		if(cur != NULL)
			cur = rebalance(cur);
		if(root != NULL)
			root->setHeight();
	}
//-----------------------------------------------------------------------------
//	method:			T avl<T>::popnode(node<T>* &cur)
//	description:	removes chosen node
//	Calls:			value(), pophigh(), setHeight(), rebalance()
//	Called By:		main()
//	Parameters:		node<T>* &cur -- the current node
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template<class T>
	T avl<T>::popnode(node<T>* &cur)
	{
		if(cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		T contents = cur->value();
		if(cur->left == nullptr && cur->right == nullptr)
		{ // no children
			delete cur;
			cur = nullptr;
		}
		else if(cur->left == nullptr)
		{ // only right child
			node<T>* temp = cur->right;
			delete cur;
			cur = temp;
		}
		else if(cur->right == nullptr)
		{ // only left child
			node<T>* temp = cur->left;
			delete cur;
			cur = temp;
		}
		else
		{ // two children
			cur->setdata(pophigh(cur->left));
			// pops rightmost node of left child and
			// places that value into the current node
		}
		if(root != nullptr)
			root->setHeight();

		if (cur != NULL)
		{
			cur = rebalance(cur);
			cur->setHeight();
		}
		return contents;
	}
//-----------------------------------------------------------------------------
//	method:			T avl<T>::poplow(node<T>* &cur)
//	description:	removes lowest node
//	Calls:			setHeight(), rebalance()
//	Called By:		main()
//	Parameters:		node<T>* &cur -- the current node
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template <class T>
	T avl<T>::poplow(node<T>* &cur)
	{
		if(cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if(cur->left == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->right;
			delete cur;
			cur = temptr;
			if(root != nullptr)
			{
				root->setHeight();
				rebalance(root);
			}
			return temp;
		}
		return poplow(cur->left);
	}
//-----------------------------------------------------------------------------
//	method:			T avl<T>::popfirst(const T& d, node<T>* np)
//	description:	removes first node
//	Calls:			popnode(), setHeight(), bst::findfirst(), value
//	Called By:		main()
//	Parameters:		const T& d -- the element at the first
//					node<T>* np -- the current node
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template <class T>
	T avl<T>::popfirst(const T& d, node<T>* np)
	{
		node<T>* matchptr = nullptr;
		findfirst(d, root, matchptr);
		if(*parentptr != nullptr)
		{
			if((*parentptr)->value() == d)
				return popnode((*parentptr));
		}
		if(root != nullptr)
			root->setHeight();

		return 0;
	}
//-----------------------------------------------------------------------------
//	method:			node<T>* avl<T>::rotateRight(node<T> *nodeN)
//	description:	rotates the node to the right
//	Calls:			getHeight()
//	Called By:		main()
//	Parameters:		node<T> *nodeN -- the node to be rotated
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template<class T>
	node<T>* avl<T>::rotateRight(node<T> *nodeN)
	{
		node<T>* leftRight = nodeN->left->right;
		node<T>* newNode = nodeN->left;

		newNode->right = nodeN;
		newNode->right->left = leftRight;

		nodeN->getHeight();
		newNode->getHeight();
		return newNode;
	}
//-----------------------------------------------------------------------------
//	method:			node<T>* avl<T>::rotateLeft(node<T> *nodeN)
//	description:	rotates the node to the left
//	Calls:			getHeight()
//	Called By:		main()
//	Parameters:		node<T> *nodeN -- the node to be rotated
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template<class T>
	node<T>* avl<T>::rotateLeft(node<T> *nodeN)
	{
		node<T>* rightLeft = nodeN->right->left;
		node<T>* newNode = nodeN->right;

		newNode->left = nodeN;
		newNode->left->right = rightLeft;

		nodeN->getHeight();
		newNode->getHeight();
		return newNode;
	}
//-----------------------------------------------------------------------------
//	method:			node<T>* avl<T>::rotateRightLeft(node<T> *nodeN)
//	description:	rotates the node to the right left
//	Calls:			getHeight()
//	Called By:		main()
//	Parameters:		node<T> *nodeN -- the first node to be rotated
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template<class T>
	node<T>* avl<T>::rotateRightLeft(node<T> *nodeN)	
	{
		node<T>* temp = nodeN->right;
		node<T>* newNode = temp->left;

		nodeN->right = newNode->left;
		newNode->left = nodeN;
		temp->left = newNode->right;
		newNode->right = temp;

		nodeN->setHeight();
		newNode->setHeight();
		temp->setHeight();
		return newNode;
	}
//-----------------------------------------------------------------------------
//	method:			node<T>* avl<T>::rotateLeftRight(node<T> *nodeN)
//	description:	rotates the node to the left right
//	Calls:			getHeight()
//	Called By:		main()
//	Parameters:		node<T> *nodeN -- the first node to be rotated
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template<class T>
	node<T>* avl<T>::rotateLeftRight(node<T> *nodeN)
	{
		node<T>* temp = nodeN->left;
		node<T>* newNode = temp->right;

		nodeN->left = newNode->right;
		newNode->right = nodeN;
		temp->right = newNode->left;
		newNode->left = temp;

		nodeN->setHeight();
		newNode->setHeight();
		temp->setHeight();
		return newNode;
	}
//-----------------------------------------------------------------------------
//	method:			node<T>* avl<T>::rebalance(node<T> *&nodeN)
//	description:	rebalances the tree
//	Calls:			rotateRight(), rotateLeftRight(), getHeightDifference,
//						rotateLeft(), RotateRightLeft(), setHeight()
//	Called By:		main()
//	Parameters:		node<T> *&nodeN -- the starting node of the rebalance
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template<class T>
	node<T>* avl<T>::rebalance(node<T> *&nodeN)
	{
		int balance = getHeightDifference(nodeN);
		if (balance < -1)
		{
			if (getHeightDifference(nodeN->left) < 0)
				nodeN = rotateRight(nodeN);
			else
				nodeN = rotateLeftRight(nodeN);
		}
		else if (balance > 1)
		{
			if (getHeightDifference(nodeN->right) > 0)
				nodeN = rotateLeft(nodeN);
			else
				nodeN = rotateRightLeft(nodeN);
		}
		nodeN->setHeight();
		return nodeN;
	}
//-----------------------------------------------------------------------------
//	method:			int avl<T>::getHeightDifference(const node<T> *const nodeN) const
//	description:	gets the height difference for each node
//	Calls:			rotateRight(), rotateLeftRight(),
//						rotateLeft(), RotateRightLeft(), setHeight()
//	Called By:		main()
//	Parameters:		const node<T> *const nodeN -- the node being checked
//	History Log:	6/7/2012  BTF  completed version 1.0
// ----------------------------------------------------------------------------	
	template<class T>
	int avl<T>::getHeightDifference(const node<T> *const nodeN) const
	{
		int left = 0;
		int right = 0;

		if (nodeN->left != NULL)
			left = nodeN->left->getHeight();
		if (nodeN->right != NULL)
			right = nodeN->right->getHeight();

		return (right - left);
	}
}
#endif
