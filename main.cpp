#include <iostream>
#include <vector>

class HashTable {
private:
    const static int tableSize = 30;

    struct TableElement {
        std::string storage;
        TableElement* next;

        TableElement() {
            next = nullptr;
        }
    };

    TableElement elementsContainer[tableSize];
public:
    static int GetIndex(const std::string &key) {
        int hashCode = 0;
        int index;

        size_t lenOfKey = key.length();
        for (int i = 0; i < lenOfKey; i++) {
            hashCode += int(key[i]);
        }

        index = hashCode % tableSize;

        return index;
    }

    void RemoveElement(const std::string &key, const std::string &byContain) {
        int index = GetIndex(key);
        TableElement *currentElement = &elementsContainer[index];
        TableElement *previousElement = nullptr;

        while (currentElement->next != nullptr && currentElement->storage != byContain) {
            previousElement = currentElement;
            currentElement = currentElement->next;
        }

        if (currentElement->storage != byContain) {
            return;
        }

        if (previousElement == nullptr) {
            if (currentElement->next != nullptr){
                TableElement *nextElement = currentElement->next;

                currentElement->next = nextElement->next;
                currentElement->storage = nextElement->storage;

                delete(nextElement);
            }
            else {
                currentElement->storage.clear();
            }
        }
        else {
            if (currentElement->next != nullptr) {
                previousElement->next = currentElement->next;
                delete(currentElement);
            } else {
                previousElement->next = nullptr;
                delete(currentElement);
            }

        }
    }

    void AddElement(const std::string &key, const std::string &toContain) {
        int index = GetIndex(key);

        if(elementsContainer[index].storage.empty()) {
            elementsContainer[index].storage = toContain;
        } else {
            auto *newElement = new TableElement;
            TableElement *currentElement = &elementsContainer[index];

            while(currentElement->next != nullptr) {
                currentElement = currentElement->next;
            }

            newElement->storage = toContain;

            currentElement->next = newElement;
        }
    }

    std::vector<std::string> GetElement(const std::string &key, int index = -1) {
        if (index == -1) {
            index = GetIndex(key);
        }

        std::vector<std::string> resultElements;

        TableElement currentElement = elementsContainer[index];

        while (!currentElement.storage.empty()) {
            resultElements.push_back(currentElement.storage);

            if (currentElement.next == nullptr)
                break;

            currentElement = *currentElement.next;
        }

        return resultElements;
    }

    void PrintTable() {
        std::vector<std::string> vecOfElements;
        for (int i = 0; i < tableSize; i++) {
            vecOfElements = GetElement("none", i);

            if (!vecOfElements.empty()) {
                std::cout << "index: " + std::to_string(i) + ": \n";
                for (auto const &el: vecOfElements) {
                    std::cout << "  --" << el << std::endl;
                }
            }

        }
    }
};


int main() {
    HashTable hashTable;

    std::string key1 = "key1";

    hashTable.AddElement(key1, "1-> Data for key 1");
    hashTable.AddElement(key1, "2-> Data for key 1");
    hashTable.AddElement(key1, "3-> Data for key 1");

    std::string key2 = "key2";

    hashTable.AddElement(key2, "1-> Data for key 2");
    hashTable.AddElement(key2, "2-> Data for key 2");
    hashTable.AddElement(key2, "3-> Data for key 2");

    std::cout << "\n\n---Print table---\n";
    hashTable.PrintTable();

    std::cout << "\n\n---Add element for key1 with data \'lol\' \n";
    hashTable.AddElement(key1, "lol");
    hashTable.PrintTable();

    std::cout << "\n\n---Remove element for key1 with data \'lol\' \n";
    hashTable.RemoveElement(key1, "lol");
    hashTable.PrintTable();

    std::cout << "\n\n---Remove element for key2 with data \'1-> Data for key 2\' \n";
    hashTable.RemoveElement(key2, "1-> Data for key 2");
    hashTable.PrintTable();

    return 0;
}
