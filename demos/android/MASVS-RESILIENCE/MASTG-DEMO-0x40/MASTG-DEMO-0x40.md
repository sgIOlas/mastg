---
platform: android
title: JDWP Debugging Checks in App Code
id: MASTG-DEMO-0x40
code: [kotlin]
test: MASTG-TEST-0046-1
tools: [MASTG-TOOL-0110]
kind: pass
---

## Sample

This sample detects an attached JDWP debugger at runtime by calling `Debug.isDebuggerConnected()`.

{{ MastgTest.kt # MastgTest_reversed.java }}

## Steps

Run the static analysis rule against the decompiled code.

{{ ../../../../rules/mastg-android-debugger-checks.yml }}

{{ run.sh }}

## Observation

The output lists code locations where runtime debugger checks are performed.

{{ output.txt }}

## Evaluation

Review each reported location:

- `Debug.isDebuggerConnected()` is reported in `MastgTest_reversed.java` (line 23), which indicates a runtime JDWP debugger check.
