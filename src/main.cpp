#include <iostream>

#include <ofMain.h>

#include "ofApp.h"

using std::cout;
using std::endl;

int main() {
    cout << "* Études audiovisuel *" << endl;

	ofSetupOpenGL(1024,768, OF_WINDOW);
    ofRunApp(new ofApp());
        
    return 0;
}
