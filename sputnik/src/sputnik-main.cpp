#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/util/util.hpp>
#include <kocmoc-core/version.hpp>


#include "Sputnik.hpp"
#include "version.hpp"


using namespace sputnik;
namespace po = boost::program_options;

using kocmoc::core::util::Properties;

int main(int argc, char *argv[])
{	

	// command line arguments, defaults
	std::string configFile = "sputnik-config.xml";
	std::string coreConfigFile = "kocmoc-core-config.xml";

	// parse command line args
	try
	{
		po::options_description options("sputnik program options");
		options.add_options()
			("version,v", "print version string")
			("help,h", "produce help message")
			("config-file,c", po::value(&configFile), "xml config file to parse")
			("core-config-file,k", po::value(&coreConfigFile), "xml kocmoc-core config fileto parse");
		
		po::variables_map vars;        
		po::store(po::parse_command_line(argc, argv, options), vars);
		po::notify(vars);

		if (vars.count("help"))
		{
			std::cout << options << "\n";
			return 1;
		}
		
		if (vars.count("version"))
		{
			std::cout << "kocmoc version: " << std::endl;
			std::cout << "\t" << kocmoc::core::version::getVersionString() << std::endl;
			std::cout << "\t" << version::getVersionString() << std::endl;
			std::cout << "\tbuild date: " << __DATE__ << std::endl;
			
			return 1;
		}
		
		// bootstrap kocmoc...
		{
			Properties* props = new Properties();
			props->add(kocmoc::core::types::symbolize("config-file"), configFile);
			props->add(kocmoc::core::types::symbolize("core-config-file"), coreConfigFile);
			
			Sputnik sputnik(props);
		}
		
	}
    catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
    }
	
}