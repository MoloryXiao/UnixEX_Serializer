#include <iostream>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include "SerializeTestBase.h"
using namespace std;

class Serializer{
private:
	vector<SerializeTestBase*> vec_register;

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
			int r = ::read(fd, &nType, sizeof(nType));
			if((-1 == r) || (0 == r))
				break;

			for(int i=0;i<vec_register.size();i++)
			{
				if(vec_register[i]->GetType() == nType)
				{
					SerializeTestBase* p = vec_register[i]->Deserialize(fd);
					if(p != NULL)
						v.push_back(p);
				}
			}
			
		}

		close(fd);
		return true;
	}

	void Register(SerializeTestBase* p)
	{
		vec_register.push_back(p);
	}
};
