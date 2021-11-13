
#include "config_files.hpp"

using namespace std;

namespace NS2 {
    void  processConfigFile (string fname) {
          processIniConfigFile((char *) fname.c_str());
    }
}
