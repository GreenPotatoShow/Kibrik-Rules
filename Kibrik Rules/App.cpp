#include "App.h"
#include "TextLoader.h"
#include "TextProcessor.h"
#include "macros.h"

#include <string>
#include <filesystem>
#include <windows.h>


App::App() {
    for (const auto& file : std::filesystem::directory_iterator(INPUT_DIRECTORY)) {
        TextLoader textLoader(file.path().filename().string());
        if (!textLoader.getRSTNodes().empty()) {
            TextProcessor textProcessor(textLoader);
        }
    }
	
}
