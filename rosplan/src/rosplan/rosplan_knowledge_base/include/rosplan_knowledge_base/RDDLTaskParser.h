#ifndef KCL_RDDL_domainparser
#define KCL_RDDL_domainparser

#include <ros/ros.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "RDDLParser.h" // From the RDDL_parser_library

/**
 * Domain storage and parsing. Uses VAL parser and storage.
 */
namespace KCL_rosplan {

	/*--------*/
	/* parser */
	/*--------*/

	class RDDLTaskParser {
	private:

	public:
		RDDLTaskParser() : rddlTask(nullptr), domain_parsed(false), domain_name(""), problem_name("") {};
		~RDDLTaskParser() = default;

		/* RDDL task pointers */
		RDDLTask* rddlTask;

		/* domain information */
		bool domain_parsed;
		std::string domain_name;
		std::string problem_name;


		/* domain parsing */
		RDDLTask* parseTask(const std::string& domainPath, const std::string& instancePath);
	};
}
#endif
