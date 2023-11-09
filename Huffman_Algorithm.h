#ifndef HUFFMAN_ALGORITHM_H	// Git
#define HUFFMAN_ALGORITHM_H

#include <iostream>
#include <string>
#include <queue>

struct Huffman_Node
{
	char data = ' ';
	int frequency = -1;

	Huffman_Node* left = nullptr;
	Huffman_Node* right = nullptr;

	Huffman_Node(int a_data, int a_frequency) : data(a_data), frequency(a_frequency), left(nullptr), right(nullptr) {}
};

struct Comparison_Function										// Compares input a against b
{
	bool operator() (Huffman_Node* a, Huffman_Node* b) const
	{ return a->frequency > b->frequency; }
};

class Huffman_Algorithm
{
	public:
		Huffman_Algorithm();

		// Functions
		void Set_Word();										// Retrieves base to break down
		void To_Queue();										// Inserts base to the queue
		void Build_Tree();
		void Build_Map(Huffman_Node*, std::string);				// Uses ASCII code to assign character codes to slots
		void Encode_Word(std::string);							// Provides user with code using system
		void Decode_Word(std::string);							// Decode binary-like code back into a word

	private:
		std::string base = "";
		std::string code_holder[128];

		bool data_loss = false;
		bool invalid_data = false;

		std::priority_queue<Huffman_Node*, std::vector<Huffman_Node*>, Comparison_Function> pq;

		Huffman_Node* root = nullptr;

};

#endif // !HUFFMAN_ALGORITHM_H
