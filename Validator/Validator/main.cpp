#pragma once
#include <Windows.h>
#include "../pugixml/pugixml.hpp"
#include <iostream>
#include <string>
#include <exception>
#include "FormulaComputability.h"




/*class XmlLoadException : public exception
{
public:
    XmlLoadException( const char* errInfo ) : errorMsg( errInfo ) {};

    const char* what() const noexcept
    {
        return errorMsg.c_str();
    }
private:
    string errorMsg;
};


int main(int argc, char** argv) {
    try {
		char* pathToFile = argv[1];
        string flag;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(pathToFile);
        if ( !result ) {
            throw XmlLoadException(result.description());
        }

        if (argc==3){
			flag = argv[2];
            if (flag=="-quad"){
                FormulaComputability::solveQudraticEquation(doc);
            }
            else if (flag=="-sum"){
                FormulaComputability::calculateLimits(doc, "sum");
            }
            else if (flag=="-prod"){
                FormulaComputability::calculateLimits(doc, "prod");
            }
            else if (flag=="-sys"){
                // FormulaComputability::calculateSum(doc);
            }
            else
                throw invalid_argument("Wrong arguments");
		}
        else{
            if ( FormulaComputability::checkComputability(doc) ) {
                cout << "Given formula is computable" << endl;
            }
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}*/

bool __stdcall DllMain( HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved )
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
