#ifndef CPPWRAPPER_H
#define CPPWRAPPER_H

#include "json.hpp"
#include <iostream>
#include <fstream>




class SourcePirates{

	public:
		SourcePirates(std::string strIoFolder);

	private:
		int numTurn = 0;
		std::string arrPlayer[];
		std::string arrPlayers[];
		std::string arrMap[];
		std::string arrSpecials[];
		std::string strIoFolder;
		std::string arrOutput[];
		std::string arrLocalSession[];


};







#endif // CPPWRAPPER_H



SourcePirates::SourcePirates(std::string strIoFolder)
{
	this->strIoFolder = strIoFolder;
	std::ifstream file(strIoFolder + "/input.json");
	json arrFileContent;
	arrFileContent << file;

	// Fill Attributes
	this->numTurn = arrFileContent["general"]["turn"];
	this->arrPlayer = arrFileContent["player"];
	this->arrPlayers = arrFileContent["players"];
	this->arrMap = arrFileContent["map"];
	this->arrSpecials = arrFileContent["specials"];
	this->arrLocalSession = json_decode(base64_decode($arrFileContent['session']), true);
}
