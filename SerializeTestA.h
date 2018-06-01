#pragma once

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

class SerializeTestA{
private:
	char c_param;
	int i_param;
	double d_param;

public:
	SerializeTestA(){}

	SerializeTestA(char c,int i,double d)
	{
		c_param = c;
		i_param = i;
		d_param = d;
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

	bool Deserialize(int fd)
	{
		if(-1 == fd)
			return false;

		int r = read(fd, this, sizeof(*this));
		if((0 == r) || (-1 == r))
		{
			return false;
		}

		return true;
	}

	void print()
	{
		cout<<getCharParam()<<endl;
		cout<<getIntParam()<<endl;
		cout<<getDoubleParam()<<endl;
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
