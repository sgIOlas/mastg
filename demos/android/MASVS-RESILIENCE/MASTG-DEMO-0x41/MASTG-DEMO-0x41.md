---
platform: android
title: Native Anti-Debugging Checks with TracerPid and ptrace
id: MASTG-DEMO-0x41
code: [kotlin, cpp]
test: MASTG-TEST-0046-2
tools: [MASTG-TOOL-0110, MASTG-TOOL-0142]
---

## Sample

This sample demonstrates native anti-debugging checks that inspect `TracerPid` in `/proc/self/status` and use a `ptrace` self-check flow.

{{ MastgTest.kt # MastgTest_reversed.java }}
{{ tracerpid_check.cpp # tracerpid_ptrace_self.cpp }}
{{ tracerpid_inline_syscall.cpp # CMakeLists.txt }}

## Steps

Run the native anti-debugging semgrep rule against the decompiled Java file and native C++ source files.

{{ ../../../../rules/mastg-android-native-debugger-checks.yml }}
{{ run.sh }}

## Observation

The output should contain detections for native anti-debugging indicators such as `TracerPid`, `/proc/self/status`, `ptrace(...)`, and `PTRACE_ATTACH`.

{{ output.txt }}

## Evaluation

Review each reported location:

- Detections in `MastgTest_reversed.java` show app logic that checks debugging state.
- Detections in `tracerpid_check.cpp` and `tracerpid_inline_syscall.cpp` show native checks for `TracerPid`.
- Detections in `tracerpid_ptrace_self.cpp` show native `ptrace`-based anti-debugging logic.
