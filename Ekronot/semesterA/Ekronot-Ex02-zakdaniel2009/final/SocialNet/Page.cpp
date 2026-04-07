#include <iostream>
#include "Page.h"

void Page::init() {
	this->status = "";
	this->posts = "";
}
std::string Page::getStatus() const {
	return this->status;
}
std::string Page::getPosts() const {
	return this->posts;
}

void Page::addLineToPosts(const std::string& new_line) {
	this->posts += new_line + "\n";
}
void Page::setStatus(const std::string& status) {
	this->status = status;
}

void Page::clearPage() {
	this->status = "";	
	this->posts = "";
}