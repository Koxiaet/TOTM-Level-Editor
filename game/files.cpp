#include "files.hpp"
#include "stage.hpp"
#include "../tinyfd.h"

#include <iostream>
#include <cstdio>
#include <cstdint>

std::string getName(const char* fn_c_str) {
	std::string fn(fn_c_str);
	if (fn.find_last_of("/") != std::string::npos) {
		fn = fn.substr(fn.find_last_of("/") + 1);
	}
	return fn;
}

std::string getName(std::string fn) {
	if (fn.find_last_of("/") != std::string::npos) {
		fn = fn.substr(fn.find_last_of("/") + 1);
	}
	return fn;
}

std::string getExtension(const char* fn_c_str) {
	std::string fn = getName(fn_c_str);
	if (fn.find_last_of(".") != std::string::npos) {
		fn = fn.substr(fn.find_last_of(".") + 1);
	}
	return fn;
}

std::string getExtension(std::string fn) {
	if (fn.find_last_of(".") != std::string::npos) {
		fn = fn.substr(fn.find_last_of(".") + 1);
	}
	return fn;
}

int stage::loadFromHex(const std::string filename)
{
	FILE* file;
	file = fopen(filename.c_str(), "rb");
	if (file == NULL) {
		std::cout << "Error opening file." << std::endl;
		return 1;
	}

	dealloc(); //dealloc must be before I change the width and height
	fread(&width,  sizeof(size_t), 1, file); //read width and height of stage
	fread(&height, sizeof(size_t), 1, file);

	fseek(file, 0, SEEK_END);
	const size_t size = ftell(file);

	const size_t expectedSize = width*height + 2*sizeof(size_t);

	if (size != expectedSize) {
		std::cout << "Incorrect size." << std::endl;
		std::cout << "Width: " << width << " Height: " << height << std::endl;
		std::cout << "Expected: " << expectedSize << ", got: " << size << std::endl;
		fclose(file);
		return 1;
	}
	
	fseek(file, sizeof(size_t)*2, SEEK_SET);
	alloc();
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			fread(&(tiles[j][i].type), 1, 1, file);
			//std::cout << (uint)tiles[j][i].type << std::endl;
		}
	}

	fclose(file);
	return 0;
}

int stage::saveToHex(const std::string filename) //edit mode
{
	if (tiles == NULL) {
		return 0;
	}
	FILE* file;
	file = fopen(filename.c_str(), "wb");
	if (file == NULL) {
		std::cout << "Error opening file." << std::endl;
		return 1;
	}

	fwrite(&width,  sizeof(size_t), 1, file); //write width and height of stage
	fwrite(&height, sizeof(size_t), 1, file);

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			fwrite(&(tiles[j][i].type), 1, 1, file);
		}
	}

	fclose(file);
	return 0;
}

void stage::newStage() //edit mode
{
	if (warnUnsavedChanges() == tinyfd_cancel) {
		return;
	}
	width   = 0;
	height  = 0;
	scrollx = -400;
	scrolly = -300;
	dealloc();
	openFileName = "Untitled";
	unsavedChanges = false;
}

int stage::open() //edit mode
{
	if (warnUnsavedChanges() == tinyfd_cancel) {
		return 0;
	}
	char const * path = tinyfd_openFileDialog(
		"Open the Gamefile",
		NULL, 0, NULL, NULL, 0
	);
	if (path != NULL) {
		int r;
		r = loadFromHex(std::string(path));
		if (!r) { //if functions succeeded
			openFileName = path;
			unsavedChanges = false;
			//std::cout << openFileName << std::endl;
		} else {
			return 1;
		}
	} else {
		return 1;
	}
	return 0;
}

void stage::save() //edit mode
{
	if (openFileName == "Untitled") { //same as save as
		saveAs();
	} else {
		if (saveToHex(std::string(openFileName)) == 0) {
			unsavedChanges = false;
		}
	}
}

void stage::saveAs() //edit mode
{
	char const * path = tinyfd_saveFileDialog(
		"Save the Gamefile",
		NULL, 0, NULL, NULL
	);
	if (path != NULL) {
		int r;
		r = saveToHex(std::string(path));
		if (!r) { //if functions succeeded
			openFileName = path;
			unsavedChanges = false;
		}
	}
}

int stage::warnUnsavedChanges()
{
	if (unsavedChanges) {
		int r = tinyfd_messageBox(
			"Warning",
			"You have unsaved changes. Would you like to save?",
			"yesnocancel",
			"warning",
			1
		);
		if (r == tinyfd_yes) {
			save();
		}
		return r;
	}
	return tinyfd_no; //no changes to save; same as pressing 'no' on the dialog box
}