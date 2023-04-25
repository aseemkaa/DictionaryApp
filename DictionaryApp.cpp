#include <iostream>
#include <string>

using namespace std;

class Word
{
public:
	Word() {
		m_word = "";
		m_translation = "";
	}

	Word(string word, string translation) {
		m_word = word;
		m_translation = translation;
	}

	Word(const Word& word)
	{
		m_word = word.m_word;
		m_translation = word.m_translation;
	}

	string getWord() {
		return m_word;
	}

	void setWord(string word) {
		m_word = word;
	}

	string getTranslation() {
		return m_translation;
	}

	void setTranslation(string translation) {
		m_translation = translation;
	}

	friend ostream& operator<<(ostream& os, const Word& word) {
		os << word.m_word << " - " << word.m_translation;
		return os;
	}

	bool operator == (const Word& value) const
	{
		return m_word == value.m_word && m_translation == value.m_translation;
	}

private:
	string m_word;
	string m_translation;
};

class Dictionary {
private:
	Word* arr = nullptr;
	int size = 0;
public:
	void Add(Word value) {
		if (arr == nullptr) {
			size++;
			arr = new Word[size];
			arr[size - 1] = value;
		}
		else {
			size++;
			Word* mas = new Word[size];
			for (int i = 0; i < size - 1; i++) {
				mas[i] = arr[i];
			}
			mas[size - 1] = value;
			delete[] arr;
			arr = mas;
		}
	}

	bool Delete() {
		if (arr == nullptr)
			return false;
		else
		{
			size--;
			Word* mas = new Word[size];
			for (int i = 0; i < size; i++) {
				mas[i] = arr[i];
			}
			delete[] arr;
			arr = mas;
			return true;
		}
	}

	void DeleteByKey(string key) {
		if (arr == nullptr)
			return;
		else
		{
			int index = 0;
			for (int i = 0; i < size; i++)
			{
				if (arr[i].getWord() == key)
					index = i;
			}

			DeleteAt(index);
		}
	}

	void DeleteAt(int pos) {
		size--;
		Word* mas = new Word[size];
		for (int i = 0; i < pos; i++) {
			mas[i] = arr[i];
		}
		for (int i = pos + 1; i <= size; i++) {
			mas[i - 1] = arr[i];
		}
		delete[] arr;
		arr = mas;
	}

	void Show() {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << endl;
		}
	}

	void ShowAllKeys() {
		for (int i = 0; i < size; i++) {
			cout << arr[i].getWord() << endl;
		}
	}

	Word& Find(string word) {
		if (arr == nullptr) {
			throw "Word not found";
		}
		else {
			for (int i = 0; i < size; i++) {
				if (arr[i].getWord() == word) {
					return arr[i];
				}
			}
			throw "Word not found";
		}
	}

	void Sort() {
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (arr[j].getWord() > arr[j + 1].getWord()) {
					Word tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
				}
			}
		}
	}

	int countLetters(string word) {
		int count = 0;
		for (int i = 0; i < word.length(); i++) {
			if (isalpha(word[i])) {
				count++;
			}
		}
		return count;
	}
};

int main()
{
	Dictionary arr;
	Word doit;
	arr.Add(Word("computer", "kompyuter"));
	arr.Add(Word("mouse", "mysh"));
	arr.Add(Word("cable", "kabel"));
	arr.Add(Word("speaker", "kolonka"));
	arr.Add(Word("keyboard", "klaviatura"));

	string word, translation;
	int choice;

	while (true)
	{
		cout << "Select the menu:" << endl;
		cout << "1)search for the word" << endl;
		cout << "2)add the word" << endl;
		cout << "3)delete the word" << endl;
		cout << "4)show of all keys" << endl;
		cout << "5)show of the entire dictionary" << endl;
		cout << "6)count of letters in the word" << endl;
		cout << "7)sort alphabetically" << endl;
		cout << "8)exit" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Enter the word you want to find: " << endl;
			cin >> word;
			doit = arr.Find(word);
			cout << doit << endl;
			break;
		case 2:
			cout << "Enter the word you want to add: " << endl;
			cin >> word;
			cout << "Enter the value of the word you want to add: " << endl;
			cin >> translation;
			arr.Add(Word(word, translation));
			cout << "Added!" << endl;
			arr.Show();
			break;
		case 3:
			cout << "Enter the word you want to delete: " << endl;
			cin >> word;
			arr.DeleteByKey(word);
			cout << "Deleted!" << endl;
			arr.Show();
			break;
		case 4:
			cout << "All dictionary keys: " << endl;
			arr.ShowAllKeys();
			break;
		case 5:
			arr.Show();
			break;
		case 6:
			cout << "Enter the word to count: ";
			cin >> word;
			int count;
			count = arr.countLetters(word);
			cout << "Number of letters: " << arr.countLetters(word) << endl;
			break;
		case 7:
			cout << "Alphabetically sorted dictionary: " << endl;
			arr.Sort();
			arr.Show();
			break;
		case 8:
			exit(0);
		default:
			cout << "Incorrect choice!" << endl;
			break;
		}
		cout << endl << " *********************** " << endl;
	}
}