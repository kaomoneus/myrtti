NUM_VA_ARGS = 64
if __name__ == "__main__":
    for i in range(1, NUM_VA_ARGS+1):
        args = ", " + ", ".join([f"arg{j}" for j in range(1, i+1)])
        pref_arg = "pref arg1"
        if i > 1:
            pref_arg += ", " + ", ".join(f"pref arg{j}" for j in range(2, i+1))
        print(f"#define VAMACRO_PREFIX_{i}(pref{args}) {pref_arg}")
