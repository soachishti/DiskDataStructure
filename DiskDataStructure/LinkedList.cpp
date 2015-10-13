#include <iostream>
#include <cstdint>
#include <string.h>
#include <string>
#include "FileAllocLinkedList.cpp"

using namespace std;

struct node {
	int data;
	int next;
};

class LinkedList {

	int head, lastNode;
public:
	FileAllocation<node> *fs;
	LinkedList(const char* FileName) {
		fs = new FileAllocation<node>(FileName);

		head = fs->GetHeadNode();
	
	}

	void insert(int data) {
		node tmp;
		tmp.data = data;
		int addr = fs->GetAddr();

		if (head == 0) {
			tmp.next = 0;
		}
		else {
			tmp.next = head;
		}
		head = addr;
		cout << "Added: " << tmp.data << " at " << addr << " next " << tmp.next << endl;
		fs->PutAtAddr(tmp, addr);
		fs->SetHeadNode(head);
	}

	void print() {
		int addr = head;
		node n;
		cout << endl << "Print()" << endl;
		cout << "START: " << fs->GetStartAddr() << endl;
		cout << "HEAD: " << addr << endl;

		while (addr != 0) {
			n = fs->GetAtAddr(addr);
			cout << "Reading: " << n.data << " at " << addr << " next " << n.next << endl;
			addr = n.next;
		}
	}

	bool remove(int d) {
		int headAddr = fs->GetHeadNode();
		node tmpNode = fs->GetAtAddr(headAddr);
		int tmpAddr = headAddr;

		node history;
		int historyAddr;

		while (tmpAddr != 0) {
			if (tmpNode.data == d) {
				if (tmpAddr == headAddr) {
					// It is first
					fs->head.headNode = tmpNode.next;
					fs->UpdateHeader();
					head = tmpNode.next;
					fs->DeleteNode(tmpAddr);
				}
				else {
					// In middle of last element
					history.next = tmpNode.next;
					fs->DeleteNode(tmpAddr);
					fs->PutAtAddr(history, historyAddr);
				}
				return true;
			}
			else {
				// Save previous element
				history = tmpNode;
				historyAddr = tmpAddr;

				tmpAddr = tmpNode.next;
				tmpNode = fs->GetAtAddr(tmpNode.next);
			}
		}
		cout << "Data Not Found" << endl;
		return false;
	}
};

int main() {
	LinkedList ll("files/txt002.dat");
	int debug = 0;
	//ll.print();
	//return 0;

	if (debug == 0) {
		ll.insert(1);
		ll.insert(2);
		ll.insert(3);
		ll.insert(4);
		ll.insert(5);
		ll.insert(6);
		ll.insert(7);

		ll.print();
	}

	if (debug == 1) {
		ll.remove(1);
		//ll.remove(5);
		//ll.remove(6);

		cout << endl << endl;

		ll.print();
	}

	return 0;
}
