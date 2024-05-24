#include "App.h"
#include "TextLoader.h"
#include "TextProcessor.h"

#include <windows.h>


App::App() {
	TextLoader textLoader("2.txt");
	TextProcessor textProcessor(textLoader);
}
