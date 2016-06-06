#include "FbxImport.h"
#include <iostream>
#include <string>

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)



enum Commands
{
	EXPORT,
	EXIT,
	HELP,
	NONE
};

Commands HandleUserInput()
{

	std::string help	= "/Help";
	std::string helpTwo = "/help";

	std::string exit      = "/Exit";
	std::string exitTwo   = "/exit";
	std::string exitThree = "/Quit";
	std::string exitfour  = "/quit";

	std::string exprt	 = "/Export";
	std::string exprtTwo = "/export";
	std::string command;

	std::getline(std::cin, command);

	if (command.compare(help)  == 0 || command.compare(helpTwo) == 0)
		return Commands::HELP;
	if (command.compare(exit)  == 0 || command.compare(exitTwo) == 0 || command.compare(exitThree) == 0|| command.compare(exitfour) == 0)
		return Commands::EXIT;
	if (command.compare(exprt) == 0 || command.compare(exprtTwo) == 0)
		return Commands::EXPORT;
	
	std::cout << "The input is not recognized, Please type /Help for commands \n";
	return NONE;

}

void PrintHelp()
{
	std::cout << "Available Commands:\n";
	std::cout << "	/Help \n";
	std::cout << "	/Export\n";
	std::cout << "	/Exit \n";


}

void PrintStartHeader()
{
	std::cout << "-----------------------------------------------------------------------------------------\n";
	std::cout << "-----------------------------------------------------------------------------------------\n";
	std::cout << "---------------------------------- FBX to BRF Converter ---------------------------------\n";
	std::cout << "-----------------------------------------------------------------------------------------\n";
	std::cout << "-----------------------------------------------------------------------------------------\n";


	std::cout << "For help, write /Help \n";

}

Commands HandleUserInput();
void PrintStartHeader();
void PrintHelp();



void main()
{
	#ifdef _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
	bool exit = false;

	PrintStartHeader();
	Commands cmd = NONE;
	do{

		 cmd = HandleUserInput();

		switch (cmd)
		{
		case Commands::HELP :
			{

			 PrintHelp();
			 break;
			}
		case Commands::EXIT:
			{

			 exit = true;
			 break;
			}

		case Commands::EXPORT:
			{
				const char* fileName;
				const char* outfileName;

				std::cout << "Type the name of input FBX file : ";
				std::string input;
				std::getline(std::cin,input);
				fileName = input.c_str();

				std::cout << "\nType the name of the output BRF file : ";
				std::string outputFile;
				std::getline(std::cin, outputFile);
				outfileName = outputFile.c_str();

				FbxImport* importer = new FbxImport();
				try {

					importer->LoadFbxFile(fileName);			  //Load the fbx file
				}
				catch (...)
				{
					std::cout << "Could not open file: " << fileName << "\n";
					delete importer;
					break;
				}

				BrfExporter* outputClass = new BrfExporter(); //create an output class, 
				importer->ConvertFbxToFile(outputClass);	  //convert information from fbx to our format
															  //information is in the outPutClass.
				outputClass->WriteToBinaryFile(outfileName);

				delete outputClass;
				delete importer;

				std::cout << "---------------------------------- Conversion Complete ----------------------------------\n";
				std::cout << "-----------------------------------------------------------------------------------------\n";
				std::cout << "-----------------------------------------------------------------------------------------\n";

				break;
			}
		}
	}while (exit == false);




	return;

}





