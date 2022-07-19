/*

musaab imran
-> 20i-1794

CS-A
Data Structure Project
*/


// list of included libraries
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include<vector>
#include<Windows.h>
using namespace std;

// node class
class hnode
{
public:
	int frequecy;
	char character;
	double comp = 0;//for compression of codes
	hnode* left;
	hnode* right;

	hnode(const hnode& c) {  //copy constructor
		this->character = c.character;
		this->frequecy = c.frequecy;
		this->left = c.left;
		this->right = c.right;
	}

	// constructor
	hnode(char c = NULL, int f = 0)
	{
		frequecy = f;
		character = c;
		left = NULL;
		right = NULL;
	}

	bool operator <(const hnode& rhs) const  //operator overloading for priority_queue of type hnode
	{
		if (frequecy == rhs.frequecy)
			return character > rhs.character;
		return frequecy > rhs.frequecy;
	}
};

// vector overloading
struct compareStuff 
{
	bool operator()(const hnode& rhs, const hnode& lhs)//operator overloading for vector sort of type node
	{
		if (lhs.frequecy == rhs.frequecy)
			return lhs.character > rhs.character;
		return lhs.frequecy > rhs.frequecy;
	}
};

// tree type class
class htree
{
public:
	hnode* root;

	// constructor
	htree()
	{
		root = NULL;
	}

	// insertion of question 01
	void insert_task_one(vector<hnode>& l)
	{
		// first node val
		auto it1 = l.begin();   //extracting first element of vector
		hnode* f1 = new hnode(*it1);
		l.erase(l.begin());//deleteing it
		

		// second node
		auto it = l.begin(); //extracting second element of vector
		hnode* f2 = new hnode(*it);
		l.erase(l.begin()); //deleteing it

		// making of the new node
		hnode* temp1 = new hnode;      //saving in temp node to be inserted as a new root
		temp1->frequecy = f1->frequecy + f2->frequecy;
		temp1->right = f1;
		temp1->left = f2;
		cout << temp1->character;
		root = temp1;


		l.push_back(*root);//insering the new root node in vector 
		std::sort(l.begin(), l.end(), compareStuff());   //sorting once again
	}

	// insertion of second function in priority queue
	void insert(hnode* f1, hnode* f2, priority_queue<hnode>& p)
	{
		if (f1 != NULL)
			if (f2 != NULL)
			{
				hnode* temp = new hnode;
				temp->frequecy = f1->frequecy + f2->frequecy;
				temp->left = f1;
				temp->right = f2;

				root = temp;
				p.push(*temp);
			}
		if (f2 == NULL)
			if (f1 != NULL)
				return;
	}

	// leaf nodes
	int isLeaf(hnode* root) {
		return !(root->left) && !(root->right);
	}

	// printing of codes
	void printcodes(hnode* root, int arr[], int top)
	{
		double count = 0;

		// left traversal
		if (root->left) 
		{
			arr[top] = 0;
			printcodes(root->left, arr, top + 1);
		}

		// right traversal
		if (root->right) {
			arr[top] = 1;
			printcodes(root->right, arr, top + 1);
		}

		// printing of leaf nodes
		if (isLeaf(root)) {
			cout << "\t\t\t\t\t" << root->character << "  | ";
			for (int i = 0; i < top; ++i) {
				count++;
				cout << arr[i];
			}

			// counting optimal number of bits
			root->comp = count * root->frequecy;
			cout << "\n";
		}
	}

	// using priority queue for the second question
	void makeHuff(priority_queue<hnode>* p)
	{
		int count = 0;
		while (!p->empty())
		{

			// popping of nodes
			if (count == 0)  //for initial node
			{
				hnode* min1 = NULL;
				hnode* min2 = NULL;
				min1 = new hnode(p->top().character, p->top().frequecy);
				p->pop();
				min2 = new hnode(p->top().character, p->top().frequecy);
				p->pop();
				insert(min1, min2, *p);
				count++;
				if (p->size() == 1 || p->size() == 0)
					return;
			}

			// using the popped nodes and making the third node
			else if (!p->empty() && count != 0)// for next nodes
			{
				hnode* h1 = new hnode;
				*h1 = p->top();
				p->pop();
				hnode* h2 = new hnode;
				if (!p->empty())
				{
					*h2 = p->top();
					p->pop();
				}
				insert(h1, h2, *p);
				if (p->size() == 1 || p->size() == 0)
					return;
			}
		}
	}

	// compression function
	double showcompression(hnode* root) 
	{
		static double compresion = 0;

		// sending the compression variable
		if (root == NULL)
			return compresion;

		// recursive traversals
		showcompression(root->left);
		if (isLeaf(root))
			compresion += root->comp;
		showcompression(root->right);
	}
};

//temp node for returning with correct frequencies and charcater from a function
class freqarray     
{

// declarations
public:
	string arr;
	int* freq;

	// constructor
	freqarray()
	{
		arr = "";
		freq = NULL;
	}
};


// end of classes