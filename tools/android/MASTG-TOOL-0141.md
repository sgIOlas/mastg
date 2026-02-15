---
title: debugmepLS
platform: android
source: https://github.com/Olasergiolas/debugmepLS
host: [android]
---

## Overview

debugmepLS is a module based on the @MASTG-TOOL-0027 hooking framework that forces selected Android apps to appear debuggable at runtime by hooking framework services in `system_server`. It lets you toggle `FLAG_DEBUGGABLE` per package without patching or re-signing APKs.

## Capabilities and Use Cases

- Enable or disable debugging per app with search and a system-app toggle.
- Apply hooks only for selected packages to minimize side effects.
- Make non-debuggable apps attachable via JDWP for testing.

## Requirements

- Android 13 (API level 33) or later.
- LSPosed (libxposed API).
- Rooted device with LSPosed installed and running.

## Installation

Build and install the debug build:

```bash
./gradlew installDebug
```

You can also install a release from the project's Releases page.

## Usage

1. Install the app and enable it as an LSPosed module.
2. Ensure that you select "System Framework" for the module's scope.
3. Reboot the device.
4. Open the app and wait for the status to show **LSPosed connected**.
5. Toggle the packages you want to be debuggable.
6. Relaunch the target app or process.

## How It Works

The module hooks `system_server` and modifies `ApplicationInfo` and process start flags so selected packages report `FLAG_DEBUGGABLE`.

## Caveats and Limitations

- Changes apply only after the target process restarts.
- Apps can still detect rooting or hooking frameworks.
- Requires Android 13 or later and LSPosed.

## References

- [debugmepLS](https://github.com/Olasergiolas/debugmepLS)
- [LSPosed Module Example](https://github.com/libxposed/example)
