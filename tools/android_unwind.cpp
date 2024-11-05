/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <elf.h>
#include <errno.h>
#include <inttypes.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>

#include <unwindstack/DexFiles.h>
#include <unwindstack/Elf.h>
#include <unwindstack/JitDebug.h>
#include <unwindstack/Maps.h>
#include <unwindstack/Memory.h>
#include <unwindstack/Regs.h>
#include <unwindstack/AndroidUnwinder.h>

void Unwind(size_t max_frames) {
  [[clang::no_destroy]] static unwindstack::AndroidLocalUnwinder unwinder(
      std::vector<std::string>{"libc_malloc_debug.so"});
  unwindstack::AndroidUnwinderData data(max_frames);
  unwinder.Unwind(data);

  std::vector<unwindstack::FrameData> frame_info;
  frame_info = std::move(data.frames);

  // Print the frames.
  for (size_t i = 0; i < frame_info.size(); i++) {
    printf("%s\n", unwinder.FormatFrame(frame_info[i]).c_str());
  }
}

int main(int argc, char** argv) {
  Unwind(10);
  return 0;
}
