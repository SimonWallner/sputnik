#include "version.hpp"

std::string kocmoc::version::getVersionString(void)
{
	std::string version = std::string("KOCMOC-MAIN git SHA1 hash: ");
	return version + gitSHA1;
}
