#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <fstream>
using namespace std;

// C++ program for Huffman Coding 

// A Huffman tree node 
struct MinHeapNode {

	// One of the input characters 
	char data;

	// Frequency of the character 
	unsigned freq;

	// Left and right child 
	MinHeapNode *left, *right;

	MinHeapNode(char data, unsigned freq)

	{

		left = right = nullptr;
		this->data = data;
		this->freq = freq;
	}
};

// For comparison of 
// two heap nodes (needed in min heap) 
struct compare {

	bool operator()(MinHeapNode* l, MinHeapNode* r)

	{
		return (l->freq > r->freq);
	}
};

// Prints huffman codes from 
// the root of Huffman Tree. 
void printCodes(struct MinHeapNode* root, string str)
{

	if (!root)
		return;

	if (root->data != '$')
		cout << root->data << ": " << str << "\n";

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and 
// print codes by traversing the built Huffman Tree 
void HuffmanCodes(vector<char> data, vector<int> freq, int size)
{
	struct MinHeapNode *left, *right, *top;

	// Create a min heap & inserts all characters of data[] 
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(data[i], freq[i]));

	// Iterate while size of heap doesn't become 1 
	while (minHeap.size() != 1) {

		// Extract the two minimum 
		// freq items from min heap 
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		top = new MinHeapNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		minHeap.push(top);
	}

	// Print Huffman codes using 
	// the Huffman tree built above 
	printCodes(minHeap.top(), "");
}

void _freq(const string& s, vector<char> &arr, vector<int> &freq) {
	std::vector<char> ascii{};
	for (auto i = 0; i <= 127; ++i) {
		ascii.push_back(char(i));
	}

	std::set<char> arrChar{};
	for (size_t i = 0; i < s.length(); ++i) {
		for (size_t j = 0; j < ascii.size(); ++j) {
			if (s[i] == ascii[j]) {
				arrChar.insert(s[i]);
				break;
			}
		}
	}

	int count = 0;
	std::vector<int> freqNum{};
	for (auto it = arrChar.begin(); it != arrChar.end(); ++it) {
		for (size_t i = 0; i < s.length(); ++i) {
			if (*it == s[i]) {
				++count;
			}
		}
		freqNum.push_back(count);
		count = 0;
	}
	int i = 0;
	for (auto it = arrChar.begin(); it != arrChar.end(); ++it) {
		cout << *it << ": " << freqNum[i] << '\n';
		arr.push_back(*it);
		freq.push_back(freqNum[i]);
		++i;
	}
}

int main()
{
	std::string s{};
	std::cout << "Nhap thong tin ma hoa(Huffman): " << '\n';
	getline(cin, s);
	vector<char> arr{};
	vector<int> freq{};
	cout << "Tan suat xuat hien: " << '\n';
	_freq(s, arr, freq);
	size_t size = arr.size();
	cout << "Sau khi ma hoa: " << '\n';
	HuffmanCodes(arr, freq, size);
	return 0;
}
