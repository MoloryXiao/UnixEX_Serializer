#include <iostream>
#include "SerializeTestA.h"
#include "SerializeTestB.h"
#include "SerializeTestBase.h"
#include <vector>
using namespace std;

class Serializer{

public:
	bool Serialize(const char* pFilePath,vector<SerializeTestBase*>& v)
	{
		// Open the file with the mode of append.
		int fd = ::open(pFilePath, O_RDWR | O_CREAT | O_APPEND, 0777);
		if(-1 == fd)
			return false;

		// Serialize every element in vector.
		for(int i = 0; i < v.size(); i++)
		{
			int nType = v[i]->GetType();
			if(write(fd, &nType, sizeof(nType)) == -1)
			{
				close(fd);
				return false;
			}
			v[i]->Serialize(fd);
		}

		if(close(fd) == -1)
			return false;

		return true;
	}

	bool Deserialize(const char* pFilePath,vector<SerializeTestBase*>& v)
	{
		int fd = open(pFilePath, O_RDWR);
		if(-1 == fd)
			return false;

		// Deserialize every element in vector.
		while(true)
		{
			// Get the type of element.
			int nType;
			int r = ::read(fd, &nType, 4);
			if((-1 == r) || (0 == r))
				break;

			if(nType == 1)
			{
				SerializeTestA* sta = new SerializeTestA();
				if(sta->Deserialize(fd) == true)
					v.push_back(sta);
				else
					break;
			}else if(nType == 2)
			{
				SerializeTestB* stb = new SerializeTestB();
				if(stb->Deserialize(fd) == true)
					v.push_back(stb);
				else
					break;
			}
			
		}

		close(fd);
		return true;
	}
};
