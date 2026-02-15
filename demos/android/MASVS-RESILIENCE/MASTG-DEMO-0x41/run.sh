#!/usr/bin/env bash
set -euo pipefail

NO_COLOR=true semgrep -c ../../../../rules/mastg-android-native-debugger-checks.yml ./MastgTest_reversed.java --text > output.txt
NO_COLOR=true semgrep -c ../../../../rules/mastg-android-native-debugger-checks.yml ./tracerpid_check.cpp --text >> output.txt
NO_COLOR=true semgrep -c ../../../../rules/mastg-android-native-debugger-checks.yml ./tracerpid_ptrace_self.cpp --text >> output.txt
NO_COLOR=true semgrep -c ../../../../rules/mastg-android-native-debugger-checks.yml ./tracerpid_inline_syscall.cpp --text >> output.txt
