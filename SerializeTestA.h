#pragma once

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "SerializeTestBase.h"
using namespace std;

class SerializeTestA: public SerializeTestBase{
private:
	char c_param;
	int i_param;
	double d_param;

public:
	SerializeTestA()
	{
		c_param = ' ';
		i_param = 0;
		d_param = 0;
		this->objectType = 1;
	}

	SerializeTestA(char c,int i,double d)
	{
		c_param = c;
		i_param = i;
		d_param = d;
		this->objectType = 1;
	}

	int GetType()
	{
		return this->objectType;
	}

	bool Serialize(const char* pFilePath)
	{
		// get the file description
		int fd = open(pFilePath, O_RDWR | O_CREAT | O_TRUNC, 0);
		if(-1 == fd)
			return false;

		// write char
		if(write(fd, &c_param, sizeof(c_param)) == -1)
		{
			close(fd);
			return false;
		}
		// write int
		if(write(fd, &i_param, sizeof(i_param)) == -1)
		{
			close(fd);
			return false;
		}
		// write double
		if(write(fd, &d_param, sizeof(d_param)) == -1)
		{
			close(fd);
			return false;
		}

		// close the file description
		if(close(fd) == -1)
			return false;

		return true;
	}

	bool Deserialize(const char* pFilePath)
	{
		// get the file description
		int fd = open(pFilePath, O_RDWR);
		if(-1 == fd)
			return false;		

		// read char
		if(read(fd, &c_param, sizeof(c_param)) == -1)
		{
			if(close(fd) == -1)				
				return false;
			return false;
		}
		// read int
		if(read(fd, &i_param, sizeof(i_param)) == -1)
		{
			if(close(fd) == -1)				
				return false;
			return false;
		}
		// read double
		if(read(fd, &d_param, sizeof(d_param)) == -1)
		{
			if(close(fd) == -1)
				return false;
			return false;
		}

		// close the file description
		if(close(fd) == -1)
			return false;

		return true;
	}

	bool Serialize(int fd)
	{
		if(-1 == fd)
			return false;

		if(write(fd, this, sizeof(*this)) == -1)
			return false;

		return true;
	}

	SerializeTestBase* Deserialize(int fd)
	{
		if(-1 == fd)
			return NULL;

		SerializeTestA *sta = new SerializeTestA();
		int r = read(fd, sta, sizeof(*this));

		if((0 == r) || (-1 == r))
		{
			return NULL;
		}

		return sta;
	}

	void print()
	{
		cout<<getCharParam()<<" "<<getIntParam()<<" "<<getDoubleParam()<<endl;
	}

	char getCharParam()
	{
		return c_param;	
	}

	int getIntParam()
	{
		return i_param;
	}

	double getDoubleParam()
	{
		return d_param;
	}
};
