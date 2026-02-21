---
title: lldb
platform: android
source: https://lldb.llvm.org/
host: [windows, linux, macOS]
---

## Overview

lldb is the LLVM debugger. On Android, you can use it to debug native code in apps and attach to processes for native-layer analysis.

## Capabilities and Use Cases

- Debug native libraries (JNI) and system calls.
- Attach to running processes to inspect memory and registers.
- Set breakpoints and step through native code paths.

## Installation

Use the lldb version bundled with Android Studio or the Android NDK (@MASTG-TOOL-0005). Refer to the official Android Studio and NDK debugging documentation for setup and host-specific steps.

The lldb server binary for the device is located under `$LLDB_ROOT/toolchains/llvm/prebuilt/$HOST_ARCH/lib/clang/$CLANG_VERSION/lib/linux/$ANDROID_ARCH/lldb-server`. You can upload it to `/data/local/tmp` and mark it executable.

## Usage

Use lldb to attach to a running process or launch the app under the debugger. Refer to the official Android debugging guides for more information on the required device-side components and commands.

### Debugging Example

Below are example steps to attach lldb to a running process inside a rooted Android device. Do note that `lldb-server` subcommands and flags may differ between NDK releases. Use the Android Studio/NDK docs to confirm the exact invocation for your version.:

1. Spawn a root ADB shell using commands `adb shell` and `su`.
2. Run lldb with `lldb-server p --server --listen 0.0.0.0:1234`. This will start the lldb server, listening for connections from all addresses on port `1234`. Using any other accessible port is also correct.
3. Use ADB to forward connections to the `1234` port by running `adb forward tcp:1234 tcp:1234`.
4. From the host, connect to the lldb server by starting lldb and running the following commands inside, where `$TARGET_PID` is the pid of the process to debug:

```bash
(lldb) platform select remote-android
(lldb) platform connect connect://localhost:1234
(lldb) process attach -p $TARGET_PID
```

## Caveats and Limitations

- Requires having either a debuggable application or a rooted device.
- Apps can detect debugging or root and change behavior.

## References

- [lldb](https://lldb.llvm.org/)
- [Android Debugging Docs](https://developer.android.com/studio/debug)
