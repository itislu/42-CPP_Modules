#pragma once

template <unsigned long DummyOperations>
void busy_wait()
{
	if (DummyOperations > 0) {
		for (volatile unsigned long i = 0; i < DummyOperations / 2; ++i) {
		}
	}
}
