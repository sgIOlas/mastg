#!/usr/bin/env bash
set -euo pipefail

NO_COLOR=true semgrep -c ../../../../rules/mastg-android-debugger-checks.yml ./MastgTest_reversed.java --text > output.txt
NO_COLOR=true semgrep -c ../../../../rules/mastg-android-debuggable-flag.yml ./AndroidManifest_reversed.xml --text >> output.txt
