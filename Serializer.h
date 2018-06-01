#include <iostream>
#include "SerializeTestA.h"
#include <vector>
using namespace std;

class Serializer{

public:
	bool Serialize(const char* pFilePath,vector<SerializeTestA>& v)
	{
		// Open the file with the mode of append.
		int fd = ::open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0777);
		if(-1 == fd)
			return false;

		// Serialize every element in vector.
		for(int i = 0; i < v.size(); i++)
			v[i].Serialize(fd);

		if(close(fd) == -1)
			return false;

		return true;
	}

	bool Deserialize(const char* pFilePath,vector<SerializeTestA>& v)
	{
		int fd = open(pFilePath, O_RDWR);
		if(-1 == fd)
			return false;

		// Deserialize every element in vector.
		while(true)
		{
			SerializeTestA sta;
			if(sta.Deserialize(fd) == true)
				v.push_back(sta);
			else
				break;
		}

		close(fd);
		return true;
	}
};
