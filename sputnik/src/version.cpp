#include "version.hpp"

std::string sputnik::version::getVersionString(void)
{
	std::string version = std::string("SPUTNIK git SHA1 hash: ");
	return version + gitSHA1;
}
