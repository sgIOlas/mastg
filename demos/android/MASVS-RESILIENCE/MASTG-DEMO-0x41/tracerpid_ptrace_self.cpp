#include <jni.h>

#include <cerrno>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

int write_result(int fd, int value) {
    const ssize_t written = write(fd, &value, sizeof(value));
    return written == static_cast<ssize_t>(sizeof(value)) ? 0 : -1;
}

}  // namespace

extern "C" JNIEXPORT jint JNICALL
Java_org_owasp_mastestapp_MastgTest_ptraceSelfDetectNative(JNIEnv* env, jobject thiz) {
    (void)env;
    (void)thiz;

    int pipe_fds[2];
    if (pipe(pipe_fds) != 0) {
        return errno != 0 ? -errno : -1;
    }

    const pid_t child_pid = fork();
    if (child_pid < 0) {
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return errno != 0 ? -errno : -1;
    }

    if (child_pid == 0) {
        close(pipe_fds[0]);

        int result = 0;
        const pid_t parent_pid = getppid();

        errno = 0;
        if (ptrace(PTRACE_ATTACH, parent_pid, nullptr, nullptr) == 0) {
            int wait_status = 0;
            if (waitpid(parent_pid, &wait_status, 0) < 0) {
                result = errno != 0 ? -errno : -1;
            } else {
                if (ptrace(PTRACE_DETACH, parent_pid, nullptr, nullptr) != 0) {
                    result = errno != 0 ? -errno : -1;
                }
            }
        } else if (errno == EPERM) {
            result = 1;
        } else {
            result = errno != 0 ? -errno : -1;
        }

        (void)write_result(pipe_fds[1], result);
        close(pipe_fds[1]);
        _exit(0);
    }

    close(pipe_fds[1]);
    int result = -1;
    const ssize_t bytes_read = read(pipe_fds[0], &result, sizeof(result));
    close(pipe_fds[0]);

    int child_status = 0;
    (void)waitpid(child_pid, &child_status, 0);

    if (bytes_read != static_cast<ssize_t>(sizeof(result))) {
        return -1;
    }

    return result;
}
