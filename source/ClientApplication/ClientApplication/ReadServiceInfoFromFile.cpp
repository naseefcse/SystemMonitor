#include "ReadServiceInfoFromFile.h"
using namespace std;


ReadServiceInfoFromFile::ReadServiceInfoFromFile()
{
}


ReadServiceInfoFromFile::~ReadServiceInfoFromFile()
{
}

std::vector<std::string> ReadServiceInfoFromFile::getAuthentiactionInfo(FILE* pFile)
{
	char x[1024];
	/* assumes no word exceeds length of 1023 */

	std::string pass = "", userName = "", serviceLink = "", port = "";

	int count = 0;

	std::vector<std::string> data;

	data.resize(3);

	while (fscanf(pFile, " %1023s", x) == 1) {
		puts(x);

		if (0 == count)
			userName = x;
		else if (count == 1)
			pass = x;
		else if (count == 2) serviceLink = x;
		else port = x;
		count++;

		if (count == 4)
			break;
	}

	data.push_back(userName);
	data.push_back(pass);
	data.push_back(serviceLink);
	data.push_back(port);

	return data;
}
