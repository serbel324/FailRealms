#include <rengine/core/driver.h>
#include "main_frame.h"
#include <memory>

using namespace REngine;

int main() {
    REngine::Driver driver(std::unique_ptr<REngine::Frame>(new MainFrame), {});
    driver.RunFrame();
}
