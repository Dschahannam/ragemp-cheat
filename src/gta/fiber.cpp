#include "gta/fiber.hpp"
#include "gta/tick.hpp"
#include "hacks/replayinterface.hpp"
#include <memory.h>

void on_native_thread() {
	Replayinterface::Instance().Tick();
	tick::pnative.on_tick();

	Fiber::Instance().s_game_fiber->wait(0);
}

void Fiber::Call()
{
	Log::Warning(_xor_("[+] Fiber >> Initializing fiber..."));

	this->s_game_fiber = std::make_unique<fiber::fiber_task>(nullptr, on_native_thread);
}
