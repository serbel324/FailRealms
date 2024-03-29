#include <driver/driver.h>
#include "main_frame.h"

using namespace REngine;

int main() {
    Driver::Promote(std::make_unique<SingleFrameDriver>(
            std::make_unique<MainFrame>(),
            SingleFrameDriver::Settings{ .minimumUpdateDelayMs = 0 } ));
    Driver::King()->Initialize();
    Driver::King()->Run();
}
