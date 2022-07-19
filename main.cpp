/*

musaab imran
-> 20i-1794

CS-A
Data Structure Project
*/


// list of included libraries
#include <iostream>
using namespace std;
#include "DS_project.cpp"

// frequency of character calculation
freqarray* frequecny(string n)
{
	freqarray* a = new freqarray;

	string str = "";
	for (int i = 0; i < n.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < i; j++)
		{
			if (n[i] == n[j])
			{
				flag = true;
				break;
			}
		}
		if (!flag)
			str += n[i];
	}

	// calculating the size of array for compression ratio
	const int var = str.size();
	int* freq = new int[var];

	for (int i = 0; i < var; i++)
		freq[i] = 0;

	for (int i = 0; i < str.size(); i++)
		for (int j = 0; j < n.size(); j++)
			if (str[i] == n[j])
				freq[i]++;

	a->arr = str;
	a->freq = freq;

	// returning object
	return a;
}

// design function
void design1();
void design2();
void design3();
int main()
{
	// desgin functions
	design1();
	design2();

	string fname;
	cout << "\t\t\t\t\tEnter file name: ";
	cin >> fname;
	fstream ifile(fname, ios::in);

	// file reading
	if (!ifile.is_open())
	{
		cout << "\t\t\t\tError opening file 404";
		exit(1);
	}

	// design 3
	design3();

	// reading file
	string character = "", array = "";
	while (getline(ifile, character)) {
		for (int i = 0; i < character.length(); i++)
			array += character[i];
	}

	// if file is empty
	if (array.length() == 0)
	{
		cout << "\n\t\t\t\t\t----------------------EMPTY FILE-----------------------------\n";
		cout << endl;
		exit(1);
	}

	// printing frequecies of characters
	freqarray* fq = frequecny(array);
	string arr = fq->arr;
	int* freq = fq->freq;

	cout << endl;
	cout << "\n\t\t\t\t\t----------------FILE/CHARACTER INFORMATION------------------\n";
	cout << "\t\t\t\t\tOriginal file:           " << array << endl;
	cout << "\t\t\t\t\tRemoved duplicates:      " << arr << endl;
	cout << "\t\t\t\t\tRespective frquencies:   ";
	for (int i = 0; i < arr.size(); i++)
		cout << freq[i];

	// task 01 without priority queue

	cout << endl;
	cout << "\n\t\t\t\t\t----------------------TASK 1-----------------------------\n";
	vector<hnode> v;
	for (int i = 0; i < arr.size(); i++) {
		hnode q;
		q.character = arr[i];
		q.frequecy = freq[i];
		v.push_back(q);
	}

	vector<hnode> s;   //making copy of vector for task 2
	s = v;

	htree ht1;
	sort(v.begin(), v.end(), compareStuff());//sorting the vector

	for (int i = 0; i < arr.length() - 1; i++)//making tree of task1 in this function/ passed the vector by reference
		ht1.insert_task_one(v);

	const int cv = arr.length();
	int* arrr = new int[cv];
	int  top = 0;
	ht1.printcodes(ht1.root, arrr, top);//printing huffman codes
	cout << "\n\t\t\t\t\tRoot  " << ht1.root->frequecy;

	// task 02
	cout << "\n\t\t\t\t\t----------------------TASK 2-----------------------------\n";
	// using of priority queue
	priority_queue<hnode> pq;
	for (auto it = s.cbegin(); it != s.cend(); it++)
		pq.push(*it);

	htree ht;
	ht.makeHuff(&pq);    //making huffman tree for task 2....passing priority queue by reference 

	arrr = new int[cv];
	top = 0;
	ht.printcodes(ht.root, arrr, top);//printing huffman codes
	cout << "\n\t\t\t\t\troot  " << ht.root->frequecy; // root printing



	// calculation of compression ratio
	cout << "\n\t\t\t\t\t-------------------Compression Ratio---------------------\n";
	cout << "\n\t\t\t\t\tOriginal Bits: " << (array.length() * 8);
	float val = ht.showcompression(ht.root);
	cout << "\n\t\t\t\t\tOptimal Bits: " << val;

	// printing the compression ratio
	cout << "\n\t\t\t\t\tCompression ratio: " << (array.length() * 8) / val;
	cout << endl;
}

// main menu
void design1()
{
	cout << "\t\t\t\t------------- ASHAR KHALIL, MUSAAB IMRAN--------------\n";
	cout << "\t\t\t\t------------- 20K - 1724 , 20I-1794    ---------------\n";
	cout << "\t\t\t\t---------------- DATA STRUCTURES(A) ------------------\n";
	cout << "\t\t\t\t------------- HUFFMAN ENCODING PROJECT ---------------\n\n\n";
	cout << "\t\t\t\t\t/--------------------------------------/";
	cout << "\n\t\t\t\t\t| -> Loads data from a file.           |";
	cout << "\n\t\t\t\t\t| -> Compress through encoding.        |";
	cout << "\n\t\t\t\t\t| -> Get Huffman code.                 |";
	cout << "\n\t\t\t\t\t| -> Get Optimaized Huffman code.      |";
	cout << "\n\t\t\t\t\t| -> Get Compression ratio.            |";
	cout << "\n\t\t\t\t\t/--------------------------------------/\n\n\n\n";
}

// file loading display
void design2()
{
	cout << "\t\t\t\t\t/--------------------------------------/";
	cout << "\n\t\t\t\t\t\tFILE LOADED SUCESSFULLY.\n";
	cout << "\t\t\t\t\t/--------------------------------------/\n\n\n\n";
}

// desgin 3 function
void design3()
{
	// encoding message
	string design = "ENCODING YOUR FILES";
	cout << "\t\t\t\t\t/--------------------------------------/";
	cout << "\n\t\t\t\t\t\t";
	for (int i = 0; i < design.length(); i++)
	{
		cout << design[i];
		Sleep(100);
	}
	cout << "\n\t\t\t\t\t/--------------------------------------/\n\n\n\n";
	system("cls");
}