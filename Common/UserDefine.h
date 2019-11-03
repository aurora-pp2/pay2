#pragma once

template <typename T>
using SharedPtr = std::shared_ptr<T>;

#define UNUSED_REFERENCE (x) boost::ignore_unused(x);
