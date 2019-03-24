#include <iostream>
#include <fstream>
#include <string>
#include "Log.h"

using namespace std;

ofstream Log::logFile = ofstream("log.txt");
string Log::lastUse = "";