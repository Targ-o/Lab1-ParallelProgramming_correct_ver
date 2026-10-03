import subprocess
import shutil
import re

sizes = [20, 200, 400, 800, 1200, 1600, 2000]
runs = 5

for n in sizes:
    print(f"\nMatrix {n} x {n}")

    shutil.copyfile(
        f"data/matrix_a_{n}.txt",
        "data/matrix_A.txt"
    )

    shutil.copyfile(
        f"data/matrix_b_{n}.txt",
        "data/matrix_B.txt"
    )

    for run in range(1, runs + 1):
        result = subprocess.run(
            ["build/matrix_multiply.exe"],
            capture_output=True,
            text=True
        )

        match = re.search(
            r"execution time:(\S+)",
            result.stdout
        )

        if match:
            time = match.group(1)
            print(f"  Run {run}: {time} sec")
        else:
            print(f"  Run {run}: error")

print("\nDone!")
