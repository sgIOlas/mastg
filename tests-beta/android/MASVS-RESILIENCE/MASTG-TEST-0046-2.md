---
platform: android
title: Runtime Use of Native Debugging Checks
id: MASTG-TEST-0046-2
type: [static, dynamic]
weakness: MASWE-0101
best-practices: [MASTG-BEST-0007, MASTG-BEST-0029]
profiles: [R]
knowledge: [MASTG-KNOW-0028]
---

## Overview

Native debugging targets code running in compiled native libraries rather than the Java runtime. If the app relies on native debugging checks but does not enforce them consistently, an attacker can attach a native debugger and inspect or alter execution without detection. This test checks for native debugging indicators inside the app and verifies that the app changes behavior when a native debugger attaches.

Threat model: an attacker runs the app on an emulator or rooted device and can attach a native debugger.

## Steps

1. Obtain all native libraries from the app using @MASTG-TECH-0007.
2. Use @MASTG-TECH-0013 and the following techniques to try to statically identify indicators of native debugging checks as shown in @MASTG-KNOW-0028:
   1. Checks implemented in Java/Kotlin code (@MASTG-TECH-0014).
   2. Checks implemented in native libraries using standard calls to Android's libc functions such as `open`, `read`, or `ptrace` (@MASTG-TECH-0018, @MASTG-TECH-0071 and @MASTG-TECH-0140). These could be identified by looking for cross-references to such functions, or by checking the strings inside the native libraries.
   3. Checks implemented in native libraries using [inlined system calls](https://archive.is/0S1uM) (@MASTG-TECH-0018 and @MASTG-TECH-0071).
3. Spawn the app and attach a native debugger to its running process using @MASTG-TECH-0031.
4. Navigate to the screen you want to analyze.
5. Verify whether the app changes behavior while you debug it.

## Observation

The output should contain evidence of native debugging checks (for example, code locations or logs) and show the app response when a native debugger attaches (warning, restriction, termination, or telemetry).

## Evaluation

The test case fails if the app does not implement native debugging checks or if those checks are not applied correctly at runtime.

The test passes if native debugging checks are observed. However, results from this test should be interpreted as evidence of the presence of the aforementioned checks, not as an assessment of their robustness or effectiveness.
