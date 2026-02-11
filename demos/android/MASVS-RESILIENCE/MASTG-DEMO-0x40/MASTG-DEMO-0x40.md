---
platform: android
title: JDWP Debugging Checks in App Code
id: MASTG-DEMO-0x40
code: [kotlin]
test: MASTG-TEST-0046-1
tools: [MASTG-TOOL-0110]
---

## Sample

This sample checks whether the app is debuggable via `ApplicationInfo.FLAG_DEBUGGABLE` and whether a debugger is attached via `Debug.isDebuggerConnected()`.

{{ MastgTest.kt # MastgTest_reversed.java }}

## Steps

Run the static analysis rule and manifest check against the decompiled code and manifest.

{{ ../../../../rules/mastg-android-debugger-checks.yml }}
{{ ../../../../rules/mastg-android-debuggable-flag.yml }}

{{ run.sh }}

## Observation

The output lists code locations where debugger checks are performed and whether the manifest is marked as debuggable.

{{ output.txt }}

## Evaluation

Review each reported location:

- `Debug.isDebuggerConnected()` is reported in `MastgTest_reversed.java` (line 25), which indicates a runtime debugger check.
- The `android:debuggable="true"` manifest flag is reported in `AndroidManifest_reversed.xml` (line 22), which indicates the app build allows debugging.
