#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(200);
	ofSetCircleResolution(60);
	ofNoFill();
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);

	this->noise_step = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto param = ofGetFrameNum() % 50;
	if (param < 20) { this->noise_step += 0; }
	else if (param < 25) { this->noise_step += ofMap(param, 20, 25, 0, 0.0025); }
	else if (param < 45) { this->noise_step += 0.0025; }
	else { this->noise_step += ofMap(param, 45, 50, 0.0025, 0); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < 32; i++) {

		ofSetLineWidth(ofMap(i, 0, 32, 1, 5));

		ofPushMatrix();
		ofRotateZ(ofMap(ofNoise(noise_seed.z, this->noise_step + i * 0.035), 0, 1, -360, 360));
		ofRotateY(ofMap(ofNoise(noise_seed.y, this->noise_step + i * 0.035), 0, 1, -360, 360));
		ofRotateX(ofMap(ofNoise(noise_seed.x, this->noise_step + i * 0.035), 0, 1, -360, 360));

		ofDrawCircle(glm::vec3(), 250);

		ofPopMatrix();
	}

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}