#ifndef FILE_ALLOC
#define FILEALLOC 1

#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;

typedef int faPTR;

template <typename TNode>
class FileAllocation {
private:
	ofstream wfile;
	ifstream rfile;
	fstream file;
	int position;

	struct header {
		int8_t status = 0;
		char desc[64];
		faPTR startAddr;
		faPTR currAddr;
		faPTR headNode;
		int bytesRead;
		int bytesWrite;
		faPTR freelist;
	};

	struct FreeListNode {
		faPTR next;
	};

public:
	header head;
	
	FileAllocation(const char *FileName, const char *name = "Hello World");
	void printHeader(header h);
	faPTR GetCurrAddr();
	faPTR GetStartAddr();
	bool UpdateHeader();
	TNode GetAtAddr(faPTR addr);
	faPTR GetAddr();
	void PutAtAddr(TNode n, faPTR addr);
	void SetHeadNode(faPTR h);
	faPTR GetHeadNode();
	bool DeleteNode(faPTR addr);
	faPTR _new();
	faPTR _delete(faPTR);
	~FileAllocation();

};

template <typename TNode> FileAllocation<TNode>::FileAllocation(const char *FileName, const char *name = "Hello World") {

	file.open(FileName, file.out | file.app);	// Create file
	file.close();

	file.open(FileName, file.out | file.in | file.binary);

	if (!file.is_open()) {
		cout << "Failed to open file.";
		exit(1);
	}

	file.seekg(0, rfile.beg);
	file.seekp(0, rfile.beg);

	file.read(reinterpret_cast<char*>(&head), sizeof(head));
	file.clear();

	if (head.status == 0) {	// File doesn't exist before
		cout << "First time" << endl;
		head.status = 1;
		strcpy_s(head.desc, name);
		head.startAddr = sizeof(head);
		head.currAddr = sizeof(head);
		head.headNode = 0;
		head.freelist = 0;

		file.seekp(0, file.beg);
		file.write(reinterpret_cast<const char*>(&head), sizeof(head));

	}
	else {
		cout << "Second time" << endl;
	}

	file.clear();
	file.seekp(head.currAddr, file.beg);
	file.seekg(head.currAddr, file.beg);

	printHeader(head);
	cout << endl << endl;
}

template <typename TNode> void FileAllocation<TNode>::printHeader(header h) {
	cout << "Status: " << h.status << endl
		<< "Desc: " << h.desc << endl
		<< "StartAddr: " << h.startAddr << endl
		<< "CurrAddr: " << h.currAddr << endl
		<< "HeadNode: " << h.headNode << endl
		<< "BytesRead: " << h.bytesRead << endl
		<< "BytesWrite: " << h.bytesWrite << endl
		<< "Freelist: " << h.freelist << endl
		;
}

template <typename TNode> faPTR FileAllocation<TNode>::GetCurrAddr(){
	return head.currAddr;
}

template <typename TNode> faPTR FileAllocation<TNode>::GetStartAddr() {
	return head.startAddr;
}

template <typename TNode> bool FileAllocation<TNode>::UpdateHeader() {
	file.clear();
	file.seekp(0, file.beg);
	file.write(reinterpret_cast<const char*>(&head), sizeof(head));

	// Updating head by reading head from file.	It shouldn't be like
	// this but freelist updation in cause issue.

	file.seekg(0, file.beg);
	file.read(reinterpret_cast<char*>(&head), sizeof(head));
	file.clear();

	return true;
}

template <typename TNode> TNode FileAllocation<TNode>::GetAtAddr(faPTR addr) {
	TNode tmp;
	file.clear();
	file.seekg(addr, file.beg);
	file.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
	return tmp;
}

template <typename TNode> faPTR FileAllocation<TNode>::GetAddr() {
	faPTR addr;
	if (head.freelist == 0)	{	// If this is first time
		addr = head.currAddr;
		head.currAddr = head.currAddr + sizeof(TNode);
	}
	else {
		TNode tmpNode = GetAtAddr(head.freelist);
		addr = head.freelist;
		if (tmpNode.next == 0) {
			head.freelist = 0;
		}
		else {
			head.freelist = tmpNode.next;
		}
	}

	UpdateHeader();
	return addr;
}

template <typename TNode> void FileAllocation<TNode>::PutAtAddr(TNode n, faPTR addr) {
	// if (addr >= 0 && addr < sizeof(head)) throw "Failed";
	file.clear();
	file.seekp(addr, file.beg);
	file.write(reinterpret_cast<const char*>(&n), sizeof(n));
}

template <typename TNode> void FileAllocation<TNode>::SetHeadNode(faPTR h) {
	head.headNode = h;
	UpdateHeader();
}

template <typename TNode> faPTR FileAllocation<TNode>::GetHeadNode() {
	return head.headNode;
}

template <typename TNode> bool FileAllocation<TNode>::DeleteNode(faPTR addr) {
	TNode tmpNode = GetAtAddr(addr);
	//FreeListNode tmpNode;
	if (head.freelist == 0) {
		tmpNode.next = 0;
	}
	else {
		tmpNode.next = head.freelist;
	}

	// Put new node in free place for address
	//PutAtAddr(
	//		*reinterpret_cast<TNode*>(&tmpNode),
	//		addr
	//	);
	PutAtAddr(tmpNode, addr);
	head.freelist = addr;
	UpdateHeader();
	return true;
}

template <typename TNode> faPTR FileAllocation<TNode>::_new() {
	return GetAddr();
}

template <typename TNode> faPTR FileAllocation<TNode>::_delete(int addr) {
	return DeleteNode();
}

template <typename TNode> FileAllocation<TNode>::~FileAllocation() {
	file.close();
}

#endif