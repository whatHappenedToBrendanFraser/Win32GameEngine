#include <unordered_set>
#include "InputStream.h"

using namespace std;

unordered_set<char> InputStream::filters = unordered_set<char> ();
unordered_set<char> InputStream::pressed = unordered_set<char> ();