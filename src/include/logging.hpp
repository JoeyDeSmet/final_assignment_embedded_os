#pragma once

#include "mbed.h"
#include "rtos/Thread.h"

extern rtos::Mutex print_mtx;

#define print(...) do {\
  print_mtx.lock();\
  printf(__VA_ARGS__);\
  print_mtx.unlock();\
} while (0)
