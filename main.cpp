#include <iostream>
#include "SerializeTestA.h"
using namespace std;

int main(int argc, char** argv) {
	// level 1: A object of classA is serialized to data file.
	{
		SerializeTestA sta('a',10,12.34);
		cout<<"Before: "<<sta.getCharParam()<<endl;	
		cout<<"Before: "<<sta.getIntParam()<<endl;	
		cout<<"Before: "<<sta.getDoubleParam()<<endl;	
		sta.Serialize("file.dat");
	}

	{
		SerializeTestA sta;
		sta.Deserialize("file.dat");
		cout<<"After: "<<sta.getCharParam()<<endl;	
		cout<<"After: "<<sta.getIntParam()<<endl;	
		cout<<"After: "<<sta.getDoubleParam()<<endl;	
	}
}