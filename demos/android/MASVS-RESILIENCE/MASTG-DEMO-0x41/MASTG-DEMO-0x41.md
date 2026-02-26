---
platform: android
title: Native Anti-Debugging Checks with TracerPid and ptrace
id: MASTG-DEMO-0x41
code: [kotlin, cpp]
test: MASTG-TEST-0046-2
tools: [MASTG-TOOL-0110, MASTG-TOOL-0x42]
kind: pass
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

The test passes because the app implements native debugger detection checks, for example `getTracerPidFromProcStatus()` at `MastgTest_reversed.java` line 56, native `TracerPid` JNI checks invoked at lines 79 and 91, and `/proc/self/status` parsing at lines 126 and 133. The output also reports native `ptrace` anti-debugging logic in `tracerpid_ptrace_self.cpp` line 41 (`PTRACE_ATTACH`).
