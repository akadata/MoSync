#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>

#include <idl-common/idl-common.h>

using namespace std;

struct ExtensionSpec {
	const char* idlFile;
	const char* dllFile;
	Interface* inf;
};

static int generateConfig(const char* output, vector<ExtensionSpec>&);
static void outputConfig(const char* output, const vector<ExtensionSpec>&);

int main(int argc, const char** argv) {
	vector<ExtensionSpec> vext;
	const char* output = NULL;

	// parse arguments
	for(int i=1; i<argc; i++) {
		if(strcmp(argv[i], "-o") == 0) {
			i++;
			if(i >= argc)
				break;
			output = argv[i];
			continue;
		} else {
			ExtensionSpec e;
			e.idlFile = argv[i];
			i++;
			if(i >= argc) {
				output = NULL;
				break;
			}
#ifdef WIN32
			e.dllFile = _fullpath(NULL, argv[i], 0);
#else
			e.dllFile = realpath(argv[i], NULL);
#endif
			vext.push_back(e);
		}
	}

	if(!vext.empty() && output) {
		return generateConfig(output, vext);
	} else {
		printf("Usage: mx-config -o <output directory> (<idl file> <dll file>)+\n");
		printf("Example: mx-config -o build ext1.idl ext1.dll e2.idl e2.dll\n");
		return 1;
	}
}

static int generateConfig(const char* output, vector<ExtensionSpec>& vext) {
	vector<string> dummy;
	try {
		for(size_t i=0; i<vext.size(); i++) {
			vext[i].inf = new Interface(parseInterface(dummy, vext[i].idlFile));
		}
		outputConfig(output, vext);
	} catch(exception& e) {
		printf("Exception: %s\n", e.what());
		return 1;
	}
	return 0;
}

static void outputConfig(const char* output, const vector<ExtensionSpec>& vext) {
	ofstream stream((string(output)+"/mxConfig.txt").c_str());
	size_t functionCount = 0;
	for(size_t i=0; i<vext.size(); i++) {
		functionCount += vext[i].inf->functions.size();
	}
	stream << functionCount << "\n";
	for(size_t i=0; i<vext.size(); i++) {
		const ExtensionSpec& e(vext[i]);
		stream << e.dllFile << "\n";
		stream << setfill('0') << setw(8) << hex << calculateChecksum(*e.inf) << "\n";
	}
	flushStream(stream);
}

void streamInvokePrefix(ostream& stream, const Function& f) {
}
