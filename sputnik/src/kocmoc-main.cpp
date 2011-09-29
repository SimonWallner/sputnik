#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include <kocmoc-core/util/Properties.hpp>
#include <kocmoc-core/util/util.hpp>
#include <kocmoc-core/version.hpp>


#include "Kocmoc.hpp"
#include "version.hpp"


using namespace kocmoc;
namespace po = boost::program_options;

int main(int argc, char *argv[])
{	

	// command line arguments, defaults
	std::string configFile = "kocmoc-config.xml";

	// parse command line args
	try
	{
		po::options_description options("kocmoc program options");
		options.add_options()
			("version,v", "print version string")
			("help,h", "produce help message")
			("config-file,c", po::value(&configFile), "xml config file to parse");
		
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
			std::cout << "\t" << core::version::getVersionString() << std::endl;
			std::cout << "\t" << version::getVersionString() << std::endl;
			std::cout << "\tbuild date: " << __DATE__ << std::endl;
			
			return 1;
		}
		
		// bootstrap kocmoc...
		{
			core::util::Properties props;
			props.add(core::types::symbolize("config-file"), configFile);
			
			Kocmoc kocmoc(&props);
		}
		
	}
    catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
    }
	
}