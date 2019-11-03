#pragma once

#include "json11.hpp"

using Payload = json11::Json;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

#define IGNORE_UNUSED (x) boost::ignore_unused(x)

