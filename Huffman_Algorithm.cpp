#include "Huffman_Algorithm.h"	// Git

Huffman_Algorithm::Huffman_Algorithm()
{
	for(int i = 0; i < 128; i++)
		code_holder[i] = "";

	Set_Word();
}

void Huffman_Algorithm::Set_Word()
{
	std::cout << "Please enter a base below:\n" << "-";
	std::getline(std::cin, base);

	To_Queue();
}

void Huffman_Algorithm::To_Queue()
{
	int letter_count = 0;							// Counts number of letters in base

	bool* letter_check = new bool[base.length()];	// Checks off used letters
	Huffman_Node* new_node = nullptr;				// Holders for each new node

	for (int i = 0; i < base.length(); i++)
		letter_check[i] = false;

	if (base[0] != '\0')
	{
		for (int i = 0; i < base.length(); i++)
		{
			if (!letter_check[i])
			{
				for (int j = 0; j < base.length(); j++)
				{
					if (base[j] == base[i])
					{
						letter_check[j] = true;
						letter_count++;
					}
				}

				new_node = new Huffman_Node(base[i], letter_count);
				pq.push(new_node);

				std::cout << "\nFrequency:" << new_node->frequency << " & Letter:" << new_node->data;

				letter_count = 0;
			}
		}
	}

	// Next Step
	Build_Tree();
}

void Huffman_Algorithm::Build_Tree()
{
	Huffman_Node* new_node = nullptr;

	// Node Holders
	Huffman_Node* holder_1 = nullptr;
	Huffman_Node* holder_2 = nullptr;

	while (pq.size() > 1)														// Goes until queue has only one node left then sets it as the root
	{
		holder_1 = pq.top();
		pq.pop();
		holder_2 = pq.top();
		pq.pop();

		new_node = new Huffman_Node('\0', holder_1->frequency + holder_2->frequency);
		
		new_node->left = holder_1;
		new_node->right = holder_2;

		pq.push(new_node);
	}

	root = pq.top();
	pq.pop();

	// Next Step
	Build_Map(root, "");
}

void Huffman_Algorithm::Build_Map(Huffman_Node* current_node, std::string code)
{
	if (current_node == nullptr)
		return;

	if (current_node->data != '\0')
	{
		code_holder[static_cast<int>(current_node->data)] = code;				// Turns character into ASCII code to find place in array
	}

	Build_Map(current_node->left, code + "0");
	Build_Map(current_node->right, code + "1");

	if(current_node->data != '\0')
		std::cout << "\nThe Code For Letter (" << current_node->data << ") is: " << code;
}

void Huffman_Algorithm::Encode_Word(std::string word)
{
	std::string code_segment = "";
	std::string full_code = "";
	bool done = false;

	for (int i = 0; i < word.length(); i++)
	{
		code_segment = code_holder[static_cast<int>(word[i])];					// Gets code segment from array using ASCII number
		if (code_segment != "")
		{
			full_code += code_segment;
		}
		else
		{
			data_loss = true;
		}
	}

	if (!data_loss)																// Data lost if character not in list is inputted
	{
		std::cout << "\nThe Code For The Word (" << word << ") is:" << full_code;
	}
	else
	{
		std::cout << "\nThe Code For The Word(" << word << ") is:" << full_code;
		std::cout << "\n-There has been data loss-";
	}
}

void Huffman_Algorithm::Decode_Word(std::string code)
{
	char current_char = ' ';
	Huffman_Node* current_node = root;

	std::cout << "\nDecoded Word: ";

	for (int i = 0; i < code.length(); i++)
	{
		current_char = code[i];

		if (current_char == '0')
		{
			if (current_node->left != nullptr)
			{
				current_node = current_node->left;
			}
			else
			{
				invalid_data = true;
			}
		}
		else if (current_char == '1')
		{
			if (current_node->right != nullptr)
			{
				current_node = current_node->right;
			}
			else
			{
				invalid_data = true;
			}
		}
		else
		{
			invalid_data = true;
		}

		if (current_node->left == nullptr && current_node->right == nullptr) 
		{
			std::cout << current_node->data;
			current_node = root;
		}
	}

	if (invalid_data)
		std::cout << "\n-Invalid Data Detected; Results May By Inaccurate-";
}