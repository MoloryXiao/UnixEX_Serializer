#include <iostream>
#include "SerializeTestA.h"
#include "Serializer.h"
using namespace std;

int main(int argc, char** argv) {
	// level 2: two or more objects of classA are serialized to data file.
		char filePath[] = "file.dat";
	{
		SerializeTestA a1('a',10,12.23),a2('b',11,23.34),a3('c',12,34.45);
		vector<SerializeTestA> v;
		v.push_back(a1);
		v.push_back(a2);
		v.push_back(a3);
		for(int i=0;i<v.size();i++)
		{
			cout<<"Before: "<<v[i].getCharParam()<<endl;	
			cout<<"Before: "<<v[i].getIntParam()<<endl;	
			cout<<"Before: "<<v[i].getDoubleParam()<<endl;
		}
		Serializer ss;
		ss.Serialize(filePath,v);
	}
	cout<<"-------------------------"<<endl;
	{
		Serializer ss;
		vector<SerializeTestA> v;
		ss.Deserialize(filePath,v);
		for(int i=0;i<v.size();i++)
		{
			cout<<"After: "<<v[i].getCharParam()<<endl;	
			cout<<"After: "<<v[i].getIntParam()<<endl;	
			cout<<"After: "<<v[i].getDoubleParam()<<endl;
		}
	}
}