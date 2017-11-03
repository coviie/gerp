#include <iostream>
#include <string>
#include "Trie.h" 
using namespace std;

int main() 
{
	Trie hi;
	Key keyh;
	keyh.line = 1;
	keyh.file = 1;
	string word;
	cin >> word;
	while (!cin.eof()) {
		hi.addWord(word, keyh);
		cin >> word;
	}
	
	cout << endl << "Printing: \n";
	
	hi.printTrie();
	
	cout << "Searching: \n";
	cin.clear();
	cin >> word;

	vector<Key> found;
	while (!cin.eof()) {
		found = hi.searchWord(word);
		if (!found.empty()) {
			cout << "Found! ";
		
			for (size_t i = 0; i < found.size(); i++)
				cout << found[i].file << " ";
			cout << endl;
		}
		cin >> word;
	}
}