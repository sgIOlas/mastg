---
platform: android
title: Runtime Use of JDWP Debugging Checks
id: MASTG-TEST-0046-1
type: [static, dynamic]
weakness: MASWE-0101
best-practices: [MASTG-BEST-0007]
profiles: [R]
knowledge: [MASTG-KNOW-0007, MASTG-KNOW-0028]
---

## Overview

If the app relies on Java Debug Wire Protocol (JDWP) debugging checks but does not enforce them consistently, an attacker can debug, instrument, or hook the process without detection. This test checks for JDWP debugging indicators in code and verifies that the app changes behavior when a debugger attaches. For background on reverse engineering resilience, see the MASTG resiliency chapter. [MASTG resiliency](../../../Document/0x05j-Testing-Resiliency-Against-Reverse-Engineering.md), [Android manifest](https://developer.android.com/guide/topics/manifest/application-element#debug), [Debug](https://developer.android.com/reference/android/os/Debug).

Threat model: an attacker runs the app on an unlocked, rooted device and can debug, instrument, or hook the process.

## Steps

1. Obtain the AndroidManifest.xml file using @MASTG-TECH-0117.
2. Search for the [`android:debuggable`](https://developer.android.com/privacy-and-security/risks/android-debuggable) flag and verify whether it is set to `true`.
3. Use @MASTG-TECH-0014 to search for calls to debugging-related Android APIs as shown in @MASTG-KNOW-0028, such as:
    1. Checks for `FLAG_DEBUGGABLE` in the app's [`ApplicationInfo`](https://developer.android.com/reference/android/content/pm/ApplicationInfo) flags.
    2. Calls to [`Debug.isDebuggerConnected()`](https://developer.android.com/reference/android/os/Debug#isDebuggerConnected()).
    3. Calls that calculate CPU time deltas, for example, [`Debug.threadCpuTimeNanos()`](https://developer.android.com/reference/android/os/Debug#threadCpuTimeNanos()).
4. If the app is not marked as debuggable (step 2), use @MASTG-TECH-0031 to enable JDWP attach at runtime.
5. Spawn the app and attach a JDWP debugger to its process using @MASTG-TECH-0031.
6. Navigate to the screen you want to analyze.
7. Verify whether the app changes behavior while you debug it.

## Observation

The output should contain evidence of JDWP checks, such as code locations or logs, and show the app response to being debugged through a JDWP-based debugger (warning, restriction, termination, or telemetry).

## Evaluation

The test case fails if the app does not implement JDWP debugging checks or if those checks are not applied correctly at runtime.

The test passes if JDWP debugging checks are observed. However, results from this test should be interpreted as evidence of the presence of the aforementioned check, not as an assessment of its robustness or effectiveness.
