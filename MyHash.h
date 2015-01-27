#ifndef _MYHASH_H
#define _MYHASH_H
#include <string>

using namespace std;

class MyHash
{
	public:
		
		// Implementation of the popular djb2 hashing algorithm for strings
		unsigned long operator() (string s) const
		{
			unsigned long hashedNumber = 5381;

			for (int i = 0; i < s.length(); i++)
				hashedNumber = ((hashedNumber << 5) + hashedNumber) + s[i];

			return hashedNumber;
		}
};

#endif