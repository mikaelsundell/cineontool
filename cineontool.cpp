// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2025 - present Mikael Sundell.

#include <iostream>
#include <rawtoaces/rawtoaces_util.h>

RAWTOACES_USING_NAMESPACE

int main(int argc, const char *argv[]) {
  std::cout << "RawToAces: " << RAWTOACES_VERSION << std::endl;
  ImageConverter converter;
  return 0;
}
