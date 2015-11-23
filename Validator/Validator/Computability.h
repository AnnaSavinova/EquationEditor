#pragma once
#ifdef COMPUTABILITY_AI_EXPORTS
#define COMPUTABILITY_AI_API __declspec(dllexport) 
#else
#define COMPUTABILITY_AI_API __declspec(dllimport) 
#endif

#include "FormulaComputability.h"

extern "C" COMPUTABILITY_AI_API bool checkComputability( const CNode& rootNode ) {
	return FormulaComputability::checkComputability( rootNode );
}
extern "C" COMPUTABILITY_AI_API bool solveQudraticEquation( const CNode& rootNode ) {
	return FormulaComputability::solveQudraticEquation( rootNode );
}
extern "C" COMPUTABILITY_AI_API bool calculateLimits( const CNode& rootNode, string) {
	return FormulaComputability::calculateLimits( rootNode, string );
}
