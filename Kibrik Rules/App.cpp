#include "App.h"
#include "TextLoader.h"

App::App() {
	TextLoader textLoader("2.txt");
	textLoader.linearDistance(0, 166);

}