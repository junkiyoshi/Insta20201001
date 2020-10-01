#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	for (int radius = 50; radius <= 250; radius += 50) {
	
		this->setRingToMesh(this->face, this->frame, glm::vec3(), radius, 3, 25, 0, 360);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setRingToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius, float width, float height, int deg_start, int deg_end) {

	
	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	int deg_span = 1;
	for (int i = 0; i < 15; i++) {

		auto angle_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.005 + i * 0.003), 0, 1, -PI, PI);
		auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));

		auto angle_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.005 + i * 0.003), 0, 1, -PI, PI);
		auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

		auto next_angle_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.005 + (i + 1) * 0.003), 0, 1, -PI, PI);
		auto next_rotation_x = glm::rotate(glm::mat4(), next_angle_x, glm::vec3(1, 0, 0));

		auto next_angle_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.005 + (i + 1) * 0.003), 0, 1, -PI, PI);
		auto next_rotation_y = glm::rotate(glm::mat4(), next_angle_y, glm::vec3(0, 1, 0));


		for (int deg = deg_start; deg < deg_end; deg += deg_span) {

			auto face_index = face_target.getNumVertices();

			vector<glm::vec3> vertices;
			vertices.push_back(location + glm::vec4(radius * cos(deg * DEG_TO_RAD) , radius * sin(deg * DEG_TO_RAD), 0, 0) * rotation_y * rotation_x);
			vertices.push_back(location + glm::vec4(radius * cos((deg + deg_span) * DEG_TO_RAD), radius * sin((deg + deg_span) * DEG_TO_RAD), 0, 0) * rotation_y * rotation_x);
			
			vertices.push_back(location + glm::vec4(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0, 0) * next_rotation_y * next_rotation_x);
			vertices.push_back(location + glm::vec4(radius * cos((deg + deg_span) * DEG_TO_RAD), radius * sin((deg + deg_span) * DEG_TO_RAD), 0, 0) * next_rotation_y * next_rotation_x);

			face_target.addVertices(vertices);

			face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
			face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);

			face_target.addColor(ofColor(39, ofMap(i, 0, 15, 128, 255)));
			face_target.addColor(ofColor(39, ofMap(i, 0, 15, 128, 255)));
			face_target.addColor(ofColor(39, ofMap(i + 1, 0, 15, 128, 255)));
			face_target.addColor(ofColor(39, ofMap(i + 1, 0, 15, 128, 255)));
			
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}