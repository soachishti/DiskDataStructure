/*
FileAllocation fs("files/txt002.dat");

int addr2 = fs.GetAddr();
cout << addr2 << endl;

int addr3 = fs.GetAddr();
cout << addr3 << endl;

int addr4 = fs.GetAddr();
cout << addr4 << endl;

fs.DeleteNode(addr4);

int addr5 = fs.GetAddr();
cout << addr5 << endl;


return 0;
*/
/*
int addr = fs.GetAddr();

node n;
n.data = 10;
n.next = 20;

fs.PutAtAddr(n, addr);

node m;

cout << addr << endl;
m = fs.GetAtAddr(addr);
cout << m.data << endl;
cout << m.next << endl;

cout << fs.GetStartAddr() << endl;
cout << fs.GetAddr() << endl;
return 0;
*/

/*
fstream file;
string buffer;
file.open("demo.txt", ios::trunc | ios::in | ios::out);

for (int i = 0; i < 3; i++) {
cout << "Enter Name: ";
cin >> buffer;
file << buffer << endl;
}

file.seekg(0, ios::beg);

while (file.eof() == false) {
getline(file, buffer);
if (buffer.empty() == false) {
cout << buffer << endl;
}
}
*/
/*
file << "Hello World" << endl;
file << "Bilal" << endl;
file << "Bilal" << endl;
file << "Bilal" << endl;
file << "Bilal" << endl;
file << "Bilal" << endl;
file << "Bilal" << endl;
*/

//file.close();