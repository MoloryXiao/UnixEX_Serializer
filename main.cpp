#include <iostream>
#include "SerializeTestBase.h"
#include "Serializer.h"
using namespace std;

int main(int argc, char** argv) {
	// level 3: n objects of 2 classes are serialized to data file.
	char filePath[] = "file.dat";
	{
		vector<SerializeTestBase*> v;
		SerializeTestA sta1('a',1,12.23);
		SerializeTestA sta2('b',2,34.56);
		SerializeTestB stb1('c',3);
		SerializeTestB stb2('d',4);
		v.push_back(&sta1);
		v.push_back(&sta2);
		v.push_back(&stb1);
		v.push_back(&stb2);

		Serializer ser;
		ser.Serialize(filePath,v);
		cout<<"Before:"<<endl;
		for(int i=0;i<v.size();i++)
		{
			v[i]->print();
		}
	}
	cout<<"-------------------------"<<endl;
	{
		vector<SerializeTestBase*> v;
		Serializer ser;
		ser.Deserialize(filePath,v);
		cout<<"After:"<<endl;
		for(int i=0;i<v.size();i++)
			v[i]->print();

		// release object(new) in the stack.
		for(int i=0;i<v.size();i++)
			delete(v[i]);
	}
}