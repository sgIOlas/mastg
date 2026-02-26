---
platform: android
title: Runtime Use of JDWP Debugging Checks
id: MASTG-TEST-0046-1
type: [static, dynamic]
weakness: MASWE-0101
best-practices: [MASTG-BEST-0007, MASTG-BEST-0029, MASTG-BEST-0x32]
profiles: [R]
knowledge: [MASTG-KNOW-0007, MASTG-KNOW-0028]
---

## Overview

This test verifies whether the app detects a JDWP debugger attached to it.

Note that an attacker can attach a debugger after the application has completed its initial debugger check. Therefore, the application should continuously verify its debugging state rather than performing a one-time check.

For further information about anti-debugging, please refer to @MASTG-KNOW-0028 and [MASTG resiliency](../../../Document/0x05j-Testing-Resiliency-Against-Reverse-Engineering.md).

## Steps

1. Use @MASTG-TECH-0014 to search for calls to JDWP-related Android APIs as shown in @MASTG-KNOW-0028, such as:
    1. Calls to [`Debug.isDebuggerConnected()`](https://developer.android.com/reference/android/os/Debug#isDebuggerConnected()).
    2. Calls that calculate CPU time deltas, for example, [`Debug.threadCpuTimeNanos()`](https://developer.android.com/reference/android/os/Debug#threadCpuTimeNanos()).
2. If needed, use @MASTG-TECH-0031 to enable JDWP attach at runtime.
3. Spawn the app and attach a JDWP debugger to its process using @MASTG-TECH-0031.
4. Navigate to the screen you want to analyze.
5. Verify whether the app changes behavior while you debug it.

## Observation

The output should contain evidence of JDWP checks, such as code locations or logs, and show the app response to being debugged through a JDWP-based debugger (warning, restriction, termination, or telemetry).

## Evaluation

The test case fails if the app does not implement JDWP debugging checks or if those checks are not applied correctly at runtime.

The test passes if JDWP debugging checks are observed. However, results from this test should be interpreted as evidence of the presence of the aforementioned check, not as an assessment of its robustness or effectiveness.
